#ifndef fizzi_for_uno_h
#define fizzi_for_uno_h


#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "waves.h"


// size of the audiobuffer
#ifndef BUFFERSIZE
#define BUFFERSIZE 64
#endif
// instead of writing x = t%a one can also
// write x = t&(a-1) (at least when a is power of 2)
#define BUFFERSIZEMODULO (BUFFERSIZE-1)


#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit
#define fbi(a,b) ((a) ^= (1<<(b))) // flip bit


volatile uint8_t _audioBuffer[BUFFERSIZE];
uint8_t _write = 0;
volatile uint8_t _read = 0;

void initFizzi(){
  cli();
  // samplerate Timer 1 (16 Bit) -> 8 khz
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCNT1H = 0;
  TCNT1L = 0;
  TIMSK1 = 0;

  // set to CTC mode with OCR1A as top
  sbi(TCCR1B, WGM12);
  sbi(TCCR1B, CS10);

  // Fout = F_CPU/(2*prescaler*(1+compareValue))
  //768 + 231 = 999 -> eigentlich 16kHz ??!
  //OCR1AH =  0x03;
  //OCR1AL = 0xE7;
  // 256 + 243 = 499 -> 8 kHz
  //OCR1AH = 0x01;
  //OCR1AL = 0xF3;
  OCR1AH = 0x07;
  OCR1AL = 0xCF;

  // enable compare match interrupt
  sbi(TIMSK1, OCIE1A);

  // pwm timer 2 (8 Bit)
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  //fast PWM
  sbi(TCCR2A, WGM20);
  sbi(TCCR2A, WGM21);
  // compare output mode, clear on compare match with OC2A (pin 11)
  sbi(TCCR2A, COM2A1);
  //prescaler 1
  sbi(TCCR2B, CS20);

  sei();

  pinMode(11, OUTPUT);
}


byte output();


void updateBuffer(){
  while ((_read&BUFFERSIZEMODULO) != (_write&BUFFERSIZEMODULO)){
    _audioBuffer[_write&BUFFERSIZEMODULO] =output();
    _write ++;
  }
}

void updateControl();

void updateFizzi(){
  updateBuffer();
  updateControl();
}





ISR(TIMER1_COMPA_vect){
  OCR2A = _audioBuffer[_read&BUFFERSIZEMODULO];
  _read ++;
}





#endif
