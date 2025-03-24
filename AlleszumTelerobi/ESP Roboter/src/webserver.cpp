#include "webserver.h"
#include <WiFi.h>
#include <DNSServer.h>
#include "ssid.h"
#include "motorControl.h"
#include "ESPmDNS.h"


const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;

const char *hostname = "telerobo";

void setupWebserver()
{


    WiFi.setHostname(hostname);

    // try to connect to existing network
    WiFi.begin(ssid, password);
    Serial.print("\n\nTry to connect to existing network");

    {
        uint8_t timeout = 10;

        // Wait for connection, 5s timeout
        do
        {
            delay(500);
            updateSerial();
            Serial.print(".");
            timeout--;
        } while (timeout && WiFi.status() != WL_CONNECTED);


    }
   
}