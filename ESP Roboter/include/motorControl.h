#ifndef MOTCON_H
#define MOTCON_H

void forward();
void reverse();
void left();
void right();
void stop();
void leftrightRelease();
void resetMotor();
void shutdown();
void updateSerial();
void setValues(int left, int right);
void safetyDance();

#endif
