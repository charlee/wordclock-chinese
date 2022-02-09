/**
 * WiFiConfig.h - Store WiFi config in EEPROM.
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


#ifndef __WIFI_CONFIG_H__
#define __WIFI_CONFIG_H__

// ssid size and passphase size. Null terminator excluded.
#define SSID_SIZE 15
#define PASSPHRASE_SIZE 15


typedef struct {
  // +1 to include the null terminator.
  char ssid[SSID_SIZE + 1];
  char passphrase[PASSPHRASE_SIZE + 1];
  
  // checksum for all bytes excluding the checksum itself.
  // When validating, the sum of all bytes (including checksum byte) should be 0.
  unsigned char checksum;
} WiFiConfigData;



class WiFiConfigClass {

private:
  WiFiConfigData config;
  bool m_isValid = false;
  void computeChecksum();
  void validateChecksum();

public:
  // Read the config from EEPROM.
  void read();

  // Return the SSID as a C string.
  char* ssid();

  // Return the passphrase as a C string.
  char* passphrase();

  // Set the SSID before commiting.
  void setSsid(const char* ssid);

  // Set the passphrase before commiting.
  void setPassphrase(const char* passphrase);

  // Commit the SSID and passphrase to EEPROM.
  void commit();

  // Test if the cnofig is valid.
  bool isValid();
};


extern WiFiConfigClass WiFiConfig;


#endif