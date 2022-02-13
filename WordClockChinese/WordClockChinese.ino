#include <WiFiUdp.h>
#include <NTPClient.h>

#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>

#include "ESP8266AutoConfig.h"
#include "ChineseWordMatrix.h"


#define RECONFIG_PIN 2

#define NUM_LEDS 70
#define DATA_PIN 4

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "ca.pool.ntp.org", 0, 3600 * 1000);

CRGB leds[NUM_LEDS];

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

  int i;

  unsigned long epoch = ntpClient.getEpochTime();
  // Serial.println(epoch);
  
  TimeLEDs tm_leds = getLEDsByEpoch(epoch, -5 * 3600);

  fill_solid(&(leds[0]), NUM_LEDS, CRGB::Black);

  for (i = 0; i < 3; i++) {
    if (tm_leds.month[i] == 99) break;
    leds[tm_leds.month[i]] = CRGB::Red;
  }

  for (i = 0; i < 4; i++) {
    if (tm_leds.day[i] == 99) break;
    leds[tm_leds.day[i]] = CRGB::Green;
  }

  for (i = 0; i < 5; i++) {
    if (tm_leds.hour[i] == 99) break;
    leds[tm_leds.hour[i]] = CRGB::Blue;
  }

  for (i = 0; i < 4; i++) {
    if (tm_leds.minute[i] == 99) break;
    leds[tm_leds.minute[i]] = CRGB::Yellow;
  }

  Serial.printf("r, g, b = %d, %d, %d\n", leds[0].r, leds[0].g, leds[0].b);

  FastLED.show();

  delay(1000);
}
