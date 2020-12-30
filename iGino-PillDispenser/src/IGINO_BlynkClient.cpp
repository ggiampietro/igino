#include "WiFiLink.h"
#include "IGINO_BlynkClient.h"
#include "IGINO_Config.h"

IGINO_BlynkClient::IGINO_BlynkClient(char *authToken, char *serverAddress, int port)
{
    this->_authToken = authToken;
}

IGINO_BlynkClient::~IGINO_BlynkClient()
{
}

//  Send push notification
// https://blynkapi.docs.apiary.io/#reference/0/application-network-status/notify
// POST http://blynk-cloud.com/auth_token/notify
void IGINO_BlynkClient::notify(String message)
{
    WiFiClient client;
    if (client.connect(IGINO_BLINK_URL, IGINO_BLINK_PORT))
    {
        String body = "{\"body\":\"" + message + "\"}";
        client.print("POST /");
        client.print(this->_authToken);
        client.print("/notify HTTP/1.1");
        client.println();
        client.print("Host: ");
        client.println(IGINO_BLINK_URL);
        client.println("User-Agent: Arduino/2.2");
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.println("Accept: */*");
        client.print("Content-Length: ");
        client.println(body.length());
        // tell the server you are done with the header.
        client.println();
        client.println(body);
        client.stop();
    }
}
