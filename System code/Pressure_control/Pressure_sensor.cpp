#include "Pressure_sensor.h"
#include "Differentiator.h"
#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;
double T=0, P=0;
char status;
double pressure_offset = 0;
double pH2o = 0;


double pressure_calibration(){
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  bool success = false;
  while(!success){
    success = bmp180.begin();
  }
  for (int i = 0; i < 20 ; i++){
    status = bmp180.startTemperature();

    if (status != 0) {
      delay(10);
      status = bmp180.getTemperature(T);
  
      if (status != 0) {
        status = bmp180.startPressure(3);
  
        if (status != 0) {
          delay(status);
          status = bmp180.getPressure(P, T);
        }
      }
    }
  }
  double offset = P*1.01972;
  
  return offset;
}

double get_pressureh2o(double offset){
  status = bmp180.startTemperature();
  
  if (status != 0) {
    delay(10);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);
      }
  
    }
  }
  return P*1.01972 - offset;
}

//void setup() {
//  Serial.begin(9600);
//  
//  pressure_offset = pressure_calibration();
//  
//}
//
//void loop() {
//  pH2o = get_pressureh2o(pressure_offset);
//  Serial.println(pH2o);
//}
