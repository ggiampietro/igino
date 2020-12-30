#ifndef IGINO_Server_h
#define IGINO_Server_h

#include "ESP8266WebServer.h"
#include "IGINO_Display.h"

class IGINO_Server
{
private:
    ESP8266WebServer *_server;
    IGINO_Display *_display;
public:
    IGINO_Server(int port, IGINO_Display &display);
    ~IGINO_Server();
    void init();
    void handleClient();
    void handleRoot();
    void handleNotFound();
    void handleNotify();
};

#endif