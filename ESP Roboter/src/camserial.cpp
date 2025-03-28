#include "camserial.h"
#include <Arduino.h>
#include <Preferences.h>
#include "ssid.h"

String receivedText = "";
char receivedChars[SOC_UART_FIFO_LEN];
bool newData = false;
int ind1,ind2,ind3;
String IPFromCam;
String SSIDFromCam;
String PSKFromCam;
bool ip, ssid, psk = false;
bool wifiDataUpdated = false;
bool loopCamserialDeactivated = false;
Preferences eep;
uint8_t eepWriteLimit = 1;

void loadEeprom()
{
    eep.begin("wifi", true);
    SSIDFromCam = eep.getString("ssid", "");
    PSKFromCam = eep.getString("psk", "");
    eep.end();

    ssid = (SSIDFromCam.length() == 0) ? false : true;
    psk = (PSKFromCam.length() == 0) ? false : true;
    if (ssid && psk)
    {
        Serial.println("WIFI data found in EEPROM");
    }
    else
    {
        Serial.println("WIFI data not found in EEPROM");
    }
}

void saveEeprom()
{
    Serial.println("Write updated WIFI data to EEPROM");
    if (eepWriteLimit > 0)
    {
        eep.begin("wifi", false);
        eep.putString("ssid", SSIDFromCam);
        eep.putString("psk", PSKFromCam);
        eep.end();
        eepWriteLimit--;
    }
    else
    {
        Serial.println("Error EEPROM write exceeded!");
    }
}

void recvWithStartEndMarkers()
{
    bool recvInProgress = false;
    size_t ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial2.available() > 0 && newData == false)
    {
        rc = Serial2.read();
        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= SOC_UART_FIFO_LEN)
                {
                    Serial.println("Error receivedChars buffer limit!");
                    ndx = SOC_UART_FIFO_LEN - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
}

void setupCamserial()
{
    Serial2.begin(9600,SERIAL_8N1,22,21);
    loadEeprom();
}

void loopCamserial()
{
    if (loopCamserialDeactivated)
    {
        // TODO: deactivate loop if needed
        // return;
    }
    recvWithStartEndMarkers();

    if (newData == true) { // read until find newline
        Serial.printf("loop %d\n", newData);
        receivedText = receivedChars;
        if(receivedText.length() > 0)
        {
            ind1 = receivedText.indexOf(',');
            IPFromCam = receivedText.substring(0, ind1);
            ip = (IPFromCam.length() == 0) ? false : true;
            ind2 = receivedText.indexOf(',', ind1+1 );
            String tmpSSIDFromCam = receivedText.substring(ind1+1, ind2);
            if (!tmpSSIDFromCam.equals(SSIDFromCam))
            {
                Serial.println("SSID updated");
                SSIDFromCam = tmpSSIDFromCam;
                ssid = (SSIDFromCam.length() == 0) ? false : true;
                wifiDataUpdated = ssid;
            }
            ind3 = receivedText.indexOf(',', ind2+1 );
            String tmpPSKFromCam = receivedText.substring(ind2+1, ind3);
            if (!tmpPSKFromCam.equals(PSKFromCam))
            {
                Serial.println("PSK updated");
                PSKFromCam = tmpPSKFromCam;
                psk = (PSKFromCam.length() == 0) ? false : true;
                wifiDataUpdated &= psk;
            }
            Serial.println("IP von CAM:");
            Serial.println(IPFromCam);
            if (ssid && psk)
            {
                Serial.println("WIFI data used from ESPCAM");
                loopCamserialDeactivated = true;
            }
            else
            {
                Serial.println("Error receiving WIFI data from ESPCAM");
            }
            // Serial.println(SSIDFromCam);
            // Serial.println(PSKFromCam);
        }

        receivedText = ""; // clear after processing for next line
        newData = false;
    }

    if (wifiDataUpdated)
    {
        wifiDataUpdated = false;
        saveEeprom();
#if !defined(SSID) || !defined(PSK)
        Serial.println("ESP reset...");
        // TODO: remove comment if it works
         delay(500);
         ESP.restart();
#endif
    }
}

String *getIpAddr()
{
    return ip ? &IPFromCam : nullptr;
}

String *getWifiSsid()
{
    return ssid ? &SSIDFromCam : nullptr;
}

String *getWifiPsk()
{
    return psk ? &PSKFromCam : nullptr;
}
