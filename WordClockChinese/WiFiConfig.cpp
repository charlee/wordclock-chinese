#include "WiFiConfig.h"
#include "EEPROMConfig.h"
#include <Arduino.h>
#include <string.h>


void WiFiConfigClass::computeChecksum() {
  size_t i;
  uint8_t sum = 0;

  Serial.printf("Computing EEPROM checksum..");
  for (i = 0; i < sizeof(WiFiConfigData) - 1; i++) {
    sum += *((uint8_t*)&config + i);
    Serial.printf("%x ", *((uint8_t*)&config + i));
  };

  Serial.printf("sum = %x\n", sum);

  config.checksum = -sum;
}

void WiFiConfigClass::validateChecksum() {

  size_t i;
  uint8_t sum = 0;

  Serial.printf("Validating EEPROM..");
  for (i = 0; i < sizeof(WiFiConfigData); i++) {
    sum += *((uint8_t*)&config + i);
    Serial.printf("%x ", *((uint8_t*)&config + i));
  }
  Serial.printf("\n");

  m_isValid = (sum == 0);

  if (!m_isValid) {
    config.ssid[0] = 0;
    config.passphrase[0] = 0;
    config.timezone = 0;
  }
}

void WiFiConfigClass::read() {

  EEPROMConfig<WiFiConfigData> reader;
  reader.read(&config);
  validateChecksum();
}

char* WiFiConfigClass::ssid() {
  return config.ssid;
}

char* WiFiConfigClass::passphrase() {
  return config.passphrase;
}

int8_t WiFiConfigClass::timezone() {
  return config.timezone;
}

void WiFiConfigClass::setSsid(const char* ssid) {
  strncpy(config.ssid, ssid, SSID_SIZE);
}

void WiFiConfigClass::setPassphrase(const char* passphrase) {
  strncpy(config.passphrase, passphrase, PASSPHRASE_SIZE);
}

void WiFiConfigClass::setTimezone(const int8_t timezone) {
  config.timezone = timezone;
}


void WiFiConfigClass::commit() {
  EEPROMConfig<WiFiConfigData> writer;
  computeChecksum();
  writer.write(config);
}

bool WiFiConfigClass::isValid() {
  return m_isValid;
}


WiFiConfigClass WiFiConfig;
