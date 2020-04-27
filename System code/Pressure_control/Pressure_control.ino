//#include "Oxygen_sensor.h"
//#include "Pressure_sensor.h"
//#include "Actuators.h"
//#include <PID_v1.h>
//
//float oxygen_offset_ = 0;
//float pressure_offset_ = 0;
//
//
//double Setpoint, Input, Output;
//double Kp=2, Ki=5, Kd=1;
//PID deltaP_control(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//float p_H2o = 0;
//
//
//void setup() {
//  Serial.begin(9600);
//  init_actuators();
//  turn_on_air_valve(0);
//  turn_on_oxygen_valve(0);
//  turn_on_inhale_valve(0);
//  turn_on_exhale_valve(100);
//  delay(5000);
//  oxygen_offset_ = calibrate_sensor();
//  pressure_offset_ = pressure_calibration();
////  while(1);
//  
//  
//}
//
//void loop() {
//  p_H2o = get_pressureh2o(pressure_offset_);
//  turn_on_air_valve(100);
//  turn_on_oxygen_valve(100);
//  
//  if (p_H2o >= 60){
//    turn_on_inhale_valve(0);
//    turn_on_exhale_valve(70);
//  }
//  if (p_H2o < 20){
//    turn_on_inhale_valve(70);
//    turn_on_exhale_valve(0);
//  }
//  
////  float oxygen = get_oxygen_percentage(oxygen_offset_);
//  Serial.println(p_H2o);
//  
////  delay(1);        // delay in between reads for stability
//}


#include "Actuators.h"
#include "MedianFilterLib.h"
#include <Wire.h> //Including wire library

MedianFilter<float> medianFilter(20);
//float timeMean = 0;
float oxygen_ampient = 0;
float voltage_output = 0;
float oxygen_concentration = 0;

//
int Time = 0;
double I_Time, E_Time;
int OxygenPercentage;
float In_line[6];
double P1 = 0, P2 = 0, D_P = 0;
int flag = 0;
int32_t frequency = 80; //frequency (in Hz)
//


//
int valve_Air = 9;
int valve_Oxygen = 10;
int valve_In = 11;
int valve_Ex = 12;
//

void setup()
{
  Serial.begin(9600);
  pinMode(9, OUTPUT); pinMode(10, OUTPUT);
  pinMode(11, OUTPUT); pinMode(12, OUTPUT);
  init_actuators();
  oxygen_ampient = calibrate_sensor();

  digitalWrite(12,0);
  digitalWrite(11,1);
  Serial.begin(9600);
  int x = 0;
  Serial.println("IN_Pressure, EX_Pressure, I2E, Re_Rate, Oxygen, Type_Patient");
  while (x < 6)
  { int flag = 0;
    while (Serial.available())
    {
      In_line[x] = (float)Serial.parseFloat();
      Serial.println(In_line[x]);
      if (flag == 0)
      {
        x++;
        flag = 1;
      }
    }
  }
  Serial.println("End Of Readings");
  for (int i = 0; i < 6; i++)
  { Serial.print(In_line[i]);
    Serial.print(",");
  }
  Serial.println();
  I_Time = (In_line[3] / (60 * (pow(In_line[2], -1) + 1)));
  E_Time = I_Time * pow(In_line[2], -1);
  Serial.println(I_Time);
  Serial.println(E_Time);
}

////index of date
//IN_Pressure --> 0
//EX_Pressure --> 1
//I2E --> 2
//Re_Rate --> 3
//Oxygen --> 4
//Type_Patient -->5 (1 for male , 2 for femail , 3 for child).

void loop()
{
  Mixer_VC(In_line[4]);
  Oxygen_Sensor();
}


void Mixer_VC(float Oxygen_conc)
{
  int PWM;
  if (Oxygen_conc == 20)
  {
    turn_on_air_valve(100);
    turn_on_oxygen_valve(0);
  }
  else if (Oxygen_conc <= 60 && Oxygen_conc > 20)
  {
    PWM =  ((Oxygen_conc - 20) * 100 / (100 - Oxygen_conc));
    turn_on_air_valve(0);
    turn_on_oxygen_valve(PWM);
  }
  else if (Oxygen_conc <= 100 && Oxygen_conc > 60)
  {
    PWM = ((100 - Oxygen_conc) * 100 / (Oxygen_conc - 20));
    turn_on_air_valve(PWM);
    turn_on_oxygen_valve(0);
  }
}

void Oxygen_Sensor()
{
  voltage_output = medianFilter.AddValue(analogRead(A0) * (5.0 / 1024.0));
  oxygen_concentration = (voltage_output / oxygen_ampient) * 20.9;
  Serial.println(oxygen_concentration);
}

float calibrate_sensor()
{
  float median = 0;
  for (int i = 0 ; i < 20 ; i++) {
    median = medianFilter.AddValue(analogRead(A7) * (5.0 / 1024.0));
    delay(100);
  }
  return median;
}
