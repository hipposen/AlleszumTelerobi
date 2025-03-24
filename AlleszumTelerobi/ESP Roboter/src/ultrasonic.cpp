#include <NewPing.h>
#define SONAR_NUM 1      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = { // Sensor object array.
    NewPing(32, 33, MAX_DISTANCE)};

extern int distance;
int readUltrasonic()
{
    int distance = 0;

    distance = sonar[0].ping_cm();
    return distance;
}