#include "main.h"
#include "motorControl.h"
#include "ota.h"
#include "hoverserial.h"
#include "servo.h"
#include "camserial.h"

#include <ArduinoOTA.h>

void setup(void)
{
    Serial.begin(115200);
    setupCamserial();
    serialSetup();
    ServoSetup();
    setupWebserver();
    setupGui();
    setupOTA();
}

void loop(void)
{
    loopCamserial();
    updateSerial();
    guiLoop();
    ArduinoOTA.handle();
    //Servoloop();
}
