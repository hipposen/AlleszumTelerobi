#ifndef CAMSERIAL_H
#define CAMSERIAL_H

#include "WString.h"

void setupCamserial();
void loopCamserial();

String *getIpAddr();
String *getWifiSsid();
String *getWifiPsk();

#endif
