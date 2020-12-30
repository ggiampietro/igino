#ifndef GG_Wifi_h
#define GG_Wifi_h

// https://github.com/jandrassy/arduino-library-wifilink
// https://github.com/jandrassy/arduino-firmware-wifilink
#include "WiFiLink.h"

class IGINO_Wifi
{
private:
    WiFiClass *_wifi;
    // the Wifi radio's status
    int _status = WL_IDLE_STATUS;
    void printWifiStatus();

public:
    IGINO_Wifi();
    ~IGINO_Wifi();
    void init(Stream *serial);
};

#endif
