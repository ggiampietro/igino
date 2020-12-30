#include "Arduino.h"
#include "IGINO_Wifi.h"
#include "IGINO_Config.h"

IGINO_Wifi::IGINO_Wifi()
{
    this->_wifi = new WiFiClass();
}

IGINO_Wifi::~IGINO_Wifi()
{
    this->_wifi->disconnect();
    free(this->_wifi);
    this->_wifi = NULL;
}

void IGINO_Wifi::init(Stream *serial)
{
    this->_wifi->init(serial);
    delay(3000); //wait while WiFiLink firmware connects to WiFi with Web Panel settings

    if (this->_wifi->checkFirmwareVersion("1.1.0"))
    {
        this->_wifi->resetESP(); // to clear 'sockets' after sketch upload
        delay(500);      // let firmware initialize
    }

    //Check if communication with the wifi module has been established
    if (this->_wifi->status() == WL_NO_WIFI_MODULE_COMM)
    {
        Serial.println("Communication with WiFi module not established.");
        while (true)
            ; // don't continue:
    }

    // attempt to connect to Wifi network:
    while (this->_status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(IGINO_WIFI_SSID);
        // Connect to WPA/WPA2 network:
        this->_status = this->_wifi->begin(IGINO_WIFI_SSID, IGINO_WIFI_PASSWORD);
        // wait 10 seconds for connection:
        delay(10000);
    }

    Serial.println("Connected");
    printWifiStatus();
}

void IGINO_Wifi::printWifiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(this->_wifi->SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = this->_wifi->localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = this->_wifi->RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
