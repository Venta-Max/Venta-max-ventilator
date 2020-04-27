/*
  the purpose of this code is to get percise readings of oxygen concentrations
  the sensor used here is OOM202-1 from EnviTec and we applied an 44.2 amplification factor to the signal then read it on arduino pin7 (5.09 kohm / 220 kohm) 

  Author: Ahmed Radwan
  Author: Mohamed El Dodor

*/


#include "MedianFilterLib.h"

MedianFilter<float> medianFilter(20);
//float timeMean = 0;
float oxygen_ampient = 0;
float voltage_output = 0;
float oxygen_concentration = 0;
float calibrate_sensor(){
  float median = 0;
  for (int i=0 ; i < 20 ; i++){
    median = medianFilter.AddValue(analogRead(A0)*(5.0/1024.0));
    delay(100);
    }
  return median;
  }



void setup()
{
	Serial.begin(9600);
  oxygen_ampient = calibrate_sensor();
}
	

void loop()
{
  voltage_output = medianFilter.AddValue(analogRead(A0)*(5.0/1024.0));
  oxygen_concentration = (voltage_output / oxygen_ampient) * 20.9;
  Serial.println(oxygen_concentration);
}
