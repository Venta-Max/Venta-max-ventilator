#ifndef ACTUATORS_H
#define ACTUATORS_H
#define pump_EN 8
#define oxygen_valve_EN 
#define air_valve_EN
#define inhale_valve_EN
#define exhale_valve_EN

#include <Arduino.h>
void Toggle(void);
void init_actuators();
void turn_on_pump();
void turn_on_air_valve(int duty);
void turn_on_oxygen_valve(int duty);
void turn_on_inhale_valve(int duty);
void turn_on_exhale_valve(int duty);
#endif
