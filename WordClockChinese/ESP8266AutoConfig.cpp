#include "ESP8266AutoConfig.h"
#include "WiFiConfig.h"

#define XSTR(s) STR(s)
#define STR(s) #s

const char * form = "\
<form action='/connect' method='POST'>\
  <div>SSID: <input type='text' name='ssid' maxlength='" XSTR(SSID_SIZE) "'></div>\
  <div>Passphase: <input type='text' name='passphrase' maxlength='" XSTR(PASSPHRASE_SIZE) "'></div>\
  <div><button type='submit'>Connect</button></div>\
<form>\
";


void ESP8266AutoConfigClass::handleRoot() {
  m_server->send(200, "text/html", form);
}

void ESP8266AutoConfigClass::handleConnect() {
  String argName;

  if (m_server->method() != HTTP_POST) {
    m_server->send(405, "text/plain", "Method Not Allowed");
  } else {
    for (uint8_t i = 0; i < m_server->args(); i++) {
      argName = m_server->argName(i);
      if (argName.equals("ssid")) {
        WiFiConfig.setSsid(m_server->arg(i).c_str());
      } else if (argName.equals("passphrase")) {
        WiFiConfig.setPassphrase(m_server->arg(i).c_str());
      }
    }

    if (strlen(WiFiConfig.ssid()) > 0) {
      Serial.printf("SSID=%s saved.\n", WiFiConfig.ssid());
      WiFiConfig.commit();

      m_server->send(200, "text/plain", "SSID and Passphrase saved.");

      if (m_isAutoMode) {
        stopAp();
      }
    } else {
      m_server->send(400, "text/html", "Empty SSID, please <a href='/'>try again</a>.");
    }
  }
}

void ESP8266AutoConfigClass::poll() {
  if (m_isApMode && m_server) {
    m_server->handleClient();
  }
}

void ESP8266AutoConfigClass::startWebServer() {
  m_server = new ESP8266WebServer(80);
  Serial.print("Starting web m_server for AP mode...");
  m_server->on("/", std::bind(&ESP8266AutoConfigClass::handleRoot, this));
  m_server->on("/connect", std::bind(&ESP8266AutoConfigClass::handleConnect, this));
  m_server->begin();
  Serial.println("done.");
}

void ESP8266AutoConfigClass::stopWebServer() {
  if (m_server) {
    m_server->close();
    m_server->stop();
    m_server = NULL;
  }
}

bool ESP8266AutoConfigClass::startAp(bool autoMode) {
  Serial.print("Starting AP mode...");

  bool result = WiFi.softAP("ESP8266", "");

  if (result) {
    Serial.println("ready");
    startWebServer();
    m_isApMode = true;
  } else {
    Serial.println("failed");
  }

  m_isAutoMode = autoMode;

  return result;
}

bool ESP8266AutoConfigClass::stopAp() {
  Serial.print("Stopping AP mode...");

  stopWebServer();

  bool result = WiFi.softAPdisconnect(true);
  if (result) {
    Serial.println("done");
    m_isApMode = false;
  } else {
    Serial.println("failed");
  }

  if (m_isAutoMode) {
    connectWiFi(true);
  }

  return result;
}

bool ESP8266AutoConfigClass::connectWiFi(bool autoMode) {
  int status;

  Serial.print("Reading SSID from EEPROM...");
  WiFiConfig.read();

  bool isValid = WiFiConfig.isValid();

  if (isValid) {
    Serial.printf("done, SSID = %s\n", WiFiConfig.ssid());
  } else {
    Serial.print("failed\n");
  }

  if (isValid) {
    // connect to wifi
    Serial.printf("Connecting to %s", WiFiConfig.ssid());

    WiFi.begin(WiFiConfig.ssid(), WiFiConfig.passphrase());

    status = WiFi.status();
    while (status != WL_CONNECTED && status != WL_CONNECT_FAILED && status != WL_WRONG_PASSWORD) {
      delay(500);
      Serial.print(".");
      status = WiFi.status();
    }

    if (status == WL_CONNECTED) {
      Serial.printf("connected, IP = %s\n", WiFi.localIP().toString().c_str());
      return true;
    } else {
      Serial.printf("failed\n");
    }
  }

  m_isAutoMode = autoMode;
  if (autoMode) {
    startAp(true);
  }

  return false;
}

bool ESP8266AutoConfigClass::isApMode() const {
  return m_isApMode;
}


ESP8266AutoConfigClass ESP8266AutoConfig;