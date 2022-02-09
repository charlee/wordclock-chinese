/**
 * ESP8266AutoConfig.h - esp8266 WiFi auto config.
 * Copyright (c) 2009-2021 Charlee Li and Intelliavant Technologies Ltd.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef __WIFI_AUTO_CONFIG_H__
#define __WIFI_AUTO_CONFIG_H__


#include <ESP8266WebServer.h>


// ESP8266AutoConfigClass
//
// Core class for auto configuring ESP8266.
// Auto-config will set ESP8266 in AP mode to allow users to connect to it with
// a browser to setup the SSID and passphrase for the WiFi.
// SSID and passphrase will be stored in the EEPROM so that future boot can use
// them to connect to WiFi.
class ESP8266AutoConfigClass {
private:
  ESP8266WebServer *m_server = NULL;
  bool m_isApMode = false;
  bool m_isAutoMode = false;

  void handleRoot();

  void handleConnect(); 

  void startWebServer();

  void stopWebServer();

public:

  // Call `poll()` in the `loop()` function to keep the auto-config working.
  // When in AP mode, `poll()` will call the `ESP8266WebServer.handleClient()`
  // to handle browser requeests.
  // WHen not in AP mode, `poll()` does nothing.
  void poll();

  // Manually start AP mode.
  // This is useful for reconfiguring WiFi.
  //
  // If `autoMode` is set to `true`, then `stopAp()` and `connectWiFi()` will
  // be called automatically once valid SSID and passphrase are set. 
  //
  // For example, connect IO4 with GND to reconfigure WiFi, regardless of EEPROM:
  //
  //     #define RECONFIG_PIN 4
  //     void setup() {
  //          pinMode(RECONFIG_PIN, INPUT_PULLUP);
  //          if (digitalRead(RECONFIG_PIN) == LOW) {
  //              ESP8266AutoConfig.startAp(true);
  //          } else {
  //              ESP8266AutoConfig.connectWiFi(true);
  //          }
  //     }
  bool startAp(bool autoMode = false);

  // Stop the AP mode.
  bool stopAp();

  // Connect to WiFi.
  // 
  // If `autoMode` is set to `true`, then `startAp()` is automatically called
  // when valid SSID or passphrase do not exist.
  // Furthremore, `stopAp()` and `connectWiFi()` will
  // be called automatically once valid SSID and passphrase are set. 
  //
  bool connectWiFi(bool autoMode = false);

  // Test if currently in AP mode.
  bool isApMode() const;
};


extern ESP8266AutoConfigClass ESP8266AutoConfig;

#endif
