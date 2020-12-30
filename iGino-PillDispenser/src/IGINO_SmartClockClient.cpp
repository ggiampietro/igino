#include "IGINO_SmartClockClient.h"
#include "WiFiLink.h"
#include "IGINO_Config.h"

IGINO_SmartClockClient::IGINO_SmartClockClient(String serverAddress, int port)
{
    this->_serverAddress = serverAddress;
}

IGINO_SmartClockClient::~IGINO_SmartClockClient()
{
}

void IGINO_SmartClockClient::notify(String message)
{
    WiFiClient client;
    if (client.connect(IGINO_SMART_CLOCK_URL, 80))
    {
        String body = "{\"message\":\"" + message + "\"}";
        client.println("POST /notify HTTP/1.1");
        client.print("Host: ");
        client.println(IGINO_SMART_CLOCK_URL);
        client.println("User-Agent: Arduino/1.0");
        client.println("Connection: close");
        client.println("Accept: */*");
        client.print("Content-Length: ");
        client.println(body.length());
        // tell the server you are done with the header.
        client.println();
        client.println(body);
        client.stop();
        client.stop();
    }
}
