#include "main.h"
#include "motorControl.h"
#include "ota.h"
#include "hoverserial.h"
#include "servo.h"

#include <ArduinoOTA.h>

void setup(void)
{
  serialSetup();
  setupWebserver();
  setupGui();
  setupMotor();
  setupOTA();
  ServoSetup();
}

void loop(void)
{
  ArduinoOTA.handle();
  webserverLoop();
  guiLoop();
  updateSerial();
  //Servoloop();
}
