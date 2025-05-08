#include "motorControl.h"
#include "hoverserial.h"
#include "ultrasonic.h"
#include <arduino.h>

int valueLeft, valueRight = 0;
int fwdCount=0;

void forward(int speedfactor = 1 )
{
        setValues(speedfactor*50, speedfactor*50);
}

void reverse()
{
    setValues(-50, -50);
    fwdCount=0;
}

void left()
{
    setValues(-25, 25);
    fwdCount=0;
}

void right()
{
    setValues(25, -25);
    fwdCount=0;
}

void stop()
{
    setValues(0, 0);
    fwdCount=0;
}

void leftrightRelease()
{
    stop();
}

void resetMotor()
{
    stop();
}

void shutdown()
{
    sendShutdown();
    fwdCount=0;
}

void setValues(int left, int right)
{
    valueLeft = left;
    valueRight = right;
}

void updateSerial()
{
    safetyDance();
    Send(valueLeft, valueRight);
}

void safetyDance()
{
    int distance = readUltrasonic();
   
    if (distance > 0 && distance < 30)
    {
        if (valueLeft > 0)
            valueLeft = 0;
        if (valueRight > 0)
            valueRight = 0;
    }
}

void setLimitRMP(int limit=60)
{


}
