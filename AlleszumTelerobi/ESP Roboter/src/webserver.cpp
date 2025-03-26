#include "webserver.h"
#include <WiFi.h>
#include <DNSServer.h>
#include "ssid.h"
#include "motorControl.h"
#include "ESPmDNS.h"
#include "camserial.h"

const char *hostname = "telerobo";

void setupWebserver()
{
    WiFi.setHostname(hostname);

    // try to connect to existing network
#if defined(SSID) && defined(PSK)
    Serial.println("Connect WIFI from config");
    char const ssid[] = SSID;
    char const password[] = PSK;
    WiFi.begin(ssid, password);
# else
    Serial.print("\nTry to load WIFI data");
    String *ssidFromCam = getWifiSsid();
    String *pskFromCam = getWifiPsk();

    uint8_t timeout = 50;
    while (((ssidFromCam == nullptr) || (pskFromCam == nullptr)) && (timeout > 0))
    {
        // no data in EEPROM - loop camserial until we receive data
        Serial.print(".");
        delay(100);
        loopCamserial();
        ssidFromCam = getWifiSsid();
        pskFromCam = getWifiPsk();
        timeout--;
    }

    if ((ssidFromCam == nullptr) || (pskFromCam == nullptr))
    {
        Serial.println("Timeout no WIFI data received!");
        return;
    }

    WiFi.begin(ssidFromCam->c_str(), pskFromCam->c_str());
#endif

    Serial.print("\nWaiting for WIFI connection");
    timeout = 10;
    // Wait for connection, 5s timeout
    do
    {
        delay(500);
        loopCamserial(); // make sure to receive data while connecting
        updateSerial();
        Serial.print(".");
        timeout--;
    } while (timeout && WiFi.status() != WL_CONNECTED);

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WIFI connected!");
    }
    else
    {
        Serial.println("Unable to connect to WIFI!");
    }
}
