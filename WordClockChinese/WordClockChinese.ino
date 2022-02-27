#include <WiFiUdp.h>
#include <NTPClient.h>

#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>

#include "config.h"
#include "ESP8266AutoConfig.h"
#include "ChineseWordMatrix.h"
#include "Animation.h"

#define RECONFIG_PIN 2

#define DATA_PIN 4

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "ca.pool.ntp.org", 0, 3600 * 1000);

CRGB leds[NUM_LEDS];
Animation animation;

unsigned long epoch;
uint8_t led_pos[16];
int count;

unsigned long prev_epoch = 0;
int prev_count = 0;
uint8_t prev_led_pos[16] = { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };

uint8_t decisec = 0;

void setup() {

  // initialize serial debug port
  Serial.begin(115200);
  Serial.println();

  // connect IO4 to GND to reconfig WiFi
  pinMode(RECONFIG_PIN, INPUT_PULLUP);

  int reconfig = digitalRead(RECONFIG_PIN);
  if (reconfig == LOW) {
    ESP8266AutoConfig.startAp(true);
  } else {  
    // starting WiFi
    bool connected = ESP8266AutoConfig.connectWiFi(true);
    if (connected) {

      // start NTP client
      ntpClient.begin();

    }
  }

  // setup LEDs
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
  FastLED.setBrightness(64);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}


// the loop function runs over and over again forever
void loop() {
  ESP8266AutoConfig.poll();
  ntpClient.update();

  epoch = ntpClient.getEpochTime();
  
  // update prev data only when decisec == 0
  if (epoch != prev_epoch && decisec == 0) {
    prev_epoch = epoch;
    decisec = 0;
    animation.createAnimation(epoch);
  } else {
    decisec++;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = animation.getColor(i, decisec);
  }

  FastLED.show();

  delay(100);
}
