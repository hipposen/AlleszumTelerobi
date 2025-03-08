#include "motorControl.h"
#include "hoverserial.h"
#include "ultrasonic.h"
#include <arduino.h>
int LeftMotorPin = 23;
int rightMotorPin = 22;
int valueLeft, valueRight = 0;
void setupMotor()
{
    /*pinMode(LeftMotorPin, OUTPUT);
    pinMode(rightMotorPin, OUTPUT);
    analogWrite(LeftMotorPin, 0);
    analogWrite(rightMotorPin, 0);*/
}

void forward()
{
    setValues(500, 500);
}

void reverse()
{
    setValues(-500, -500);
}

void left()
{
    setValues(-250, 250);
}

void right()
{
    setValues(250, -250);
}

void stop()
{
    setValues(0, 0);
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