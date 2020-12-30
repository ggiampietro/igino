#ifndef IGINO_BlynkClient_h
#define IGINO_BlynkClient_h

#include "Arduino.h"

class IGINO_BlynkClient
{
private:
    char *_authToken;

public:
    IGINO_BlynkClient(char *authToken, char *serverAddress, int port);
    ~IGINO_BlynkClient();
    void notify(String message);
};

#endif