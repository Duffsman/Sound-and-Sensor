
#include "fizzi_for_uno.h"
#include "fizziEnvelope.h"
#include "fizziButton.h"


fizziEnvelope envelope = fizziEnvelope();

// connect a button to pin 2
fizziButton button = fizziButton();
const int buttonPin = 2;

long t = 0;

void setup() {
  initFizzi();
  pinMode(buttonPin, INPUT_PULLUP);
  button.attach(buttonPin);

  envelope.setADSR(100, 200, 200, 400);

}

void updateControl() {
  button.update();

  if (button.fell()) {
    envelope.noteOn();
  }
  // only when the envelope is inactive it should be changed
  if(envelope.isActive() == false){
    envelope.setADSR(random(100,300),random(100,300),random(100,255),random(200,500));
  }

}


byte output() {
  //increment t
  t ++;
  byte out = t * (t >> 6) | (t << 3) & 123;
  return  envelope.next(out);
}



void loop() {
  updateFizzi();

}
