#ifndef OXYGEN_SENSOR_H
#define OXYGEN_SENSOR_H
#include <Arduino.h>
float calibrate_sensor();
float get_oxygen_percentage(float oxygen_offset);
#endif
