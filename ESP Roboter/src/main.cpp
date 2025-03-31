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
auto diff = millis();
void loop(void)
{
    if ((millis() - diff) > 500){loopCamserial();diff = millis();}
    updateSerial();
    guiLoop();
    ArduinoOTA.handle();
    //Servoloop();
}
