#ifndef MOTCON_H
#define MOTCON_H
void setupMotor();
void forward();
void reverse();
void left();
void right();
void stop();
void leftrightRelease();
void resetMotor();
void updateSerial();
void setValues(int left, int right);
void safetyDance();
#endif