#include <WiFiUdp.h>
#include <NTPClient.h>

#include "ESP8266AutoConfig.h"

#define RECONFIG_PIN 4

WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "ca.pool.ntp.org", 0, 3600 * 1000);

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
}

// the loop function runs over and over again forever
void loop() {
  ESP8266AutoConfig.poll();
  ntpClient.update();

  Serial.println(ntpClient.getEpochTime());
  delay(1000);
}
