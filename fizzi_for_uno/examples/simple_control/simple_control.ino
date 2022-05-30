
#include "fizzi_for_uno.h"


long t = 0;
// connect a potentiometer to pin A0
const int potPin = A0;
int potVal = 0;

void setup(){
  initFizzi();
  pinMode(potPin,INPUT);

}

void updateControl(){
  //read value from potentiometer
  potVal = analogRead(potPin);
// scale down from 0-1023 to 0-15
potVal = potVal / 64;
}


byte output(){
  t ++;
  return t*(t>>potVal);
}



void loop(){
  updateFizzi();

}
