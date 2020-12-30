#ifndef GG_HTTPClient_h
#define GG_HTTPClient_h

#include "Arduino.h"

class IGINO_SmartClockClient
{
private:
String _serverAddress;

public:
    IGINO_SmartClockClient(String serverAddress, int port);
    ~IGINO_SmartClockClient();
    void notify(String message);
};

#endif