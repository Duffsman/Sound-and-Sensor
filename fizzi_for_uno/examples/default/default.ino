
#include "fizzi_for_uno.h"


long t = 0;

void setup(){
  initFizzi();

}

void updateControl(){


}


byte output(){
  //increment t
  t ++;
  return t*(t>>6) | (t<<3) & 123;
}



void loop(){
  updateFizzi();

}
