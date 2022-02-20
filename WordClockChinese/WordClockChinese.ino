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
uint8_t led_pos[16];
int count;

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


void fill_leds(const CHSV& start, const CHSV& end) {
  CHSV hsv = start;
  uint8_t dh = (end.h - start.h) / (count - 1);
  uint8_t ds = (end.s - start.s) / (count - 1);
  uint8_t dv = (end.v - start.v) / (count - 1);

  for (int i = 0; i < count; i++) {
    leds[led_pos[i]] = hsv;
    hsv.h += dh;
    hsv.s += ds;
    hsv.v += dv;
  }
}


// the loop function runs over and over again forever
void loop() {
  ESP8266AutoConfig.poll();
  ntpClient.update();

  int i;

  unsigned long epoch = ntpClient.getEpochTime();
  Serial.println(epoch);
  
  count = getLEDsByEpoch(epoch, -5 * 3600, &(led_pos[0]));

  Serial.println(led_pos[0]);
  Serial.println(count);

  // clear all
  fill_solid(&(leds[0]), NUM_LEDS, CRGB::Black);

  Serial.println("cleared");

  fill_leds(CHSV(224, 187, 255), CHSV(0, 187, 255));

  Serial.println("filled");

  // for (i = 0; i < 3; i++) {
  //   if (tm_leds.month[i] == 99) break;
  //   leds[tm_leds.month[i]] = CRGB::Red;
  // }

  // for (i = 0; i < 4; i++) {
  //   if (tm_leds.day[i] == 99) break;
  //   leds[tm_leds.day[i]] = CRGB::Green;
  // }

  // for (i = 0; i < 5; i++) {
  //   if (tm_leds.hour[i] == 99) break;
  //   leds[tm_leds.hour[i]] = CRGB::Blue;
  // }

  // for (i = 0; i < 4; i++) {
  //   if (tm_leds.minute[i] == 99) break;
  //   leds[tm_leds.minute[i]] = CRGB::Yellow;
  // }

  FastLED.show();

  delay(1000);
}
