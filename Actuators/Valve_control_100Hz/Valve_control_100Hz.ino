#include <TimerOne.h>

#define air_valve 9
#define oxygen_valve 10
#define inhale_valve 11
#define exhale_valve 12

bool toggle_air_valve = false;
bool toggle_oxygen_valve = false;
bool toggle_inhale_valve = false;
bool toggle_exhale_valve = false;

bool state_air_valve = false;
bool state_oxygen_valve = false;
bool state_inhale_valve = false;
bool state_exhale_valve = false;

int counter_air = 0;
int counter_oxygen = 0;
int counter_inhale = 0;
int counter_exhale = 0;

int duty_air = 0;
int duty_oxygen = 0;
int duty_inhale = 0;
int duty_exhale = 0;

void Toggle(void)
{
  // air valve
  if (toggle_air_valve){
    
    if (counter_air <= duty_air && counter_air >= 0) {
      state_air_valve = true;
    } 
    if (counter_air > duty_air){
      state_air_valve = false;
    }
    digitalWrite(air_valve, state_air_valve);
  }
  counter_air++;
  if (counter_air >= 100){
    counter_air = 0;
   }
  if (!toggle_air_valve) digitalWrite(air_valve, toggle_air_valve);


  // oxygen valve
  if (toggle_oxygen_valve){
    
    if (counter_oxygen <= duty_oxygen && counter_oxygen >= 0) {
      state_oxygen_valve = true;
    } 
    if (counter_oxygen > duty_oxygen){
      state_oxygen_valve = false;
    }
    digitalWrite(oxygen_valve, state_oxygen_valve);
  }
  counter_oxygen++;
  if (counter_oxygen >= 100){
    counter_oxygen = 0;
   }
  if (!toggle_oxygen_valve) digitalWrite(oxygen_valve, toggle_oxygen_valve);


  // inhale valve
  if (toggle_inhale_valve){
    
    if (counter_inhale <= duty_inhale && counter_inhale >= 0) {
      state_inhale_valve = true;
    } 
    if (counter_inhale > duty_inhale){
      state_inhale_valve = false;
    }
    digitalWrite(inhale_valve, state_inhale_valve);
  }
  counter_inhale++;
  if (counter_inhale >= 100){
    counter_inhale = 0;
   }
  if (!toggle_inhale_valve) digitalWrite(inhale_valve, toggle_inhale_valve);


  // exhale valve
  if (toggle_exhale_valve){
    
    if (counter_exhale <= duty_exhale && counter_exhale >= 0) {
      state_exhale_valve = true;
    } 
    if (counter_exhale > duty_exhale){
      state_exhale_valve = false;
    }
    digitalWrite(exhale_valve, state_exhale_valve);
  }
  counter_exhale++;
  if (counter_exhale >= 100){
    counter_exhale = 0;
   }
  if (!toggle_exhale_valve) digitalWrite(exhale_valve, toggle_exhale_valve);



  
  
}


void setup() {
  Timer1.initialize(100);
  Timer1.attachInterrupt(Toggle);
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i<100; i++){
    toggle_air_valve = true;
    toggle_oxygen_valve = true;
    duty_air = i;
    duty_oxygen = i;
    interrupts();
    delay(20);
  }

}
