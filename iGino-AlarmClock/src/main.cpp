#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <time.h>
#include "IGINO_Config.h"
#include "IGINO_Server.h"
#include "IGINO_Display.h"

ESP8266WiFiMulti WiFiMulti;
IGINO_Display display = IGINO_Display();
IGINO_Server server = IGINO_Server(SERVER_LISTEN_PORT, display);

static void setupWifi();
static void setupMDNS();

/*
ref.: https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/
*/

#define UTC_OFFSET -3
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
int dst = 0;

// used by sprintf to format time displays
char LCDTime[] = "00000000";

void setup()
{
  Serial.begin(IGINO_SERIAL_BAUD_RATE);
  Serial.setDebugOutput(true);
  setupWifi();
  setupMDNS();
  server.init();
  display.init();
  configTime(UTC_OFFSET * gmtOffset_sec, dst, ntpServer1, ntpServer2);
}

void loop()
{
  server.handleClient();
  MDNS.update();
  
  time_t now = time(NULL);
  struct tm *timeinfo;
  time(&now);
  timeinfo = localtime(&now);
  sprintf(LCDTime, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  display.print(LCDTime, NULL);
  delay(500);
}

void setupWifi()
{
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(IGINO_WIFI_SSID, IGINO_WIFI_PASSWORD);
}

void setupMDNS()
{
  //Start the mDNS responder for esp8266.local
  if (MDNS.begin(MDNS_NAME))
  {
    Serial.println("mDNS responder started");
  }
  else
  {
    Serial.println("Error setting up MDNS responder!");
  }
}
