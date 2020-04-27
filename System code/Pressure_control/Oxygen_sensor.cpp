/*
  the purpose of this code is to get percise readings of oxygen concentrations
  the sensor used here is OOM202-1 from EnviTec and we applied an 44.2 amplification factor to the signal then read it on arduino pin7 (5.09 kohm / 220 kohm) 

  Author: Ahmed Radwan
  Author: Mohamed El Dodor

*/
#include "Oxygen_sensor.h"
#include "MedianFilterLib.h"

MedianFilter<float> medianFilterOxygen(20);

float calibrate_sensor(){
  float median = 0;
  for (int i=0 ; i < 20 ; i++){
    median = medianFilterOxygen.AddValue(analogRead(A0)*(5.0/1024.0));
    delay(100);
    }
  return median;
}
float get_oxygen_percentage(float oxygen_offset){
  float voltage_output = medianFilterOxygen.AddValue(analogRead(A0)*(5.0/1024.0));
  float oxygen_concentration = (voltage_output / oxygen_offset) * 20.9;
  return oxygen_concentration;
  }
  
