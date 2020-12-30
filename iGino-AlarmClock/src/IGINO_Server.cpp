#include "IGINO_Server.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

/*
ref.: 
https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html
https://tttapa.github.io/ESP8266/Chap08%20-%20mDNS.html
*/

IGINO_Server::IGINO_Server(int port, IGINO_Display &display)
{
    this->_server = new ESP8266WebServer(port);
    this->_display = &display;
}

IGINO_Server::~IGINO_Server()
{
    free(this->_server);
    this->_server = NULL;
    this->_display = NULL;
}

void IGINO_Server::init()
{
    this->_server->on("/", HTTP_GET, [this]() { this->handleRoot(); });
    this->_server->onNotFound([this]() { this->handleNotFound(); });
    this->_server->on("/notify", HTTP_POST, [this]() { this->handleNotify(); });
    this->_server->begin();
    Serial.println("HTTP server started");
}

void IGINO_Server::handleClient()
{
    this->_server->handleClient();
}

void IGINO_Server::handleRoot()
{
    this->_server->send(200, "text/html", "24:00");
}

void IGINO_Server::handleNotFound()
{
    this->_server->send(404, "text/plain", "404: Not found");
}

void IGINO_Server::handleNotify()
{
    this->_server->send(200, "text/text", "OK");
    this->_display->print("Hora de la medicacion!", "Que mejores!!!");
    delay(30000);
}
