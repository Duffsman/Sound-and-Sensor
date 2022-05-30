
#ifndef fizziEnvelope_h
#define fizziEnvelope_h

#include <Arduino.h>


/** @defgroup fizziEnvelope
  a simple ADSR envelope
*/
class fizziEnvelope{

public:


  fizziEnvelope(){
    computeIncr();
  };



  void setADSR(uint16_t a, uint16_t d, uint16_t s, uint16_t r){
    _adsr[0] = a*8;
    _adsr[1] = d*8;
    _adsr[2] = s;
    _adsr[3] = r*8;

    computeIncr();

  };

  void setSustainLevel(uint8_t sLvl){
    _sLvl = sLvl;
    _asDiff= 255-_sLvl;
  };



  void noteOn() {
    if(_state == 4){
      _state = 0;
      _timer = _adsr[0];
      _return = 0;
    } else if(_retrigger){
      _state = 0;
      _timer = _adsr[0];
      _return = 0;
    }

  };

  /** @ingroup fizziEnvelope
  * DESCRIPTION: when set to true the envelope stays in sustainphase until
  * set to false again \n
  * INPUT: true or false \n
  * RETURN: -
  */

  void hold(bool h){
    _hold = h;
  };


  bool isActive() {

    return _state!=4;
  };

  /** @ingroup fizziEnvelope
  * DESCRIPTION: compute next value of the envelope  \n
  * INPUT: - \n
  * RETURN: Next value of the Envelope (0-255)
  */

  uint8_t next(){

    return compute();
  };

  /** @ingroup fizziEnvelope
  * DESCRIPTION: compute next value of the envelope and apply it to a sample  \n
  * INPUT: a sample (0-255) \n
  * RETURN: envelope applied to sample (0-255)
  */
  uint8_t next(uint8_t sample) {

    return (compute()*sample)>>8;
  }

  /** @ingroup fizziEnvelope
  * DESCRIPTION: enable retrigger, so the envelope can be interrupted   \n
  * INPUT: bool \n
  * RETURN: -
  */

  void setRetrigger(bool b){
    _retrigger = b;
  }



private:
  /* STATES
  * 0 ATTACK
  * 1 DECAY
  * 2 SUSTAIN
  * 3 RELEASE
  * 4 IDLE
  */
  uint8_t _state = 4;

  uint16_t _adsr [4] = {
    500,500,500,500
  };

  bool _hold = false;
  bool _retrigger = false;
  uint8_t _sLvl = 127;
  uint8_t _asDiff = 255-_sLvl;
  int _timer = 0;
  uint16_t _incr[3];
  int _return = 0;

  void computeIncr() {
    // compute difference between attack and sustain levle
    _asDiff = 255-_sLvl;
    // increment value from 0 to attackLevel (maximum value 255)
    _incr[0] = 65280/_adsr[0];
    // increment value from attacklevel to sustainLevel
    _incr[1] = (_asDiff<<8)/_adsr[1];
    // increment value from sustainLevel to 0
    _incr[2] = (_sLvl<<8)/_adsr[3];
  }


  uint8_t compute() {
    // change state according to _adsr times

    if((!_timer) && _state != 4){
      _state ++;
      _timer = _adsr[_state];

    }


    switch(_state){

      case 0: // ATTACK
      _timer --;
      _return += _incr[0];
      break;

      case 1: // DECAY
      _timer --;
      _return -= _incr[1];
      break;

      case 2: // SUSTAIN
      _timer --;
      break;

      case 3: // RELEASE
      // if envelope is not in hold mode return value from release phase
      // otherwise don't change  return value
      if(!_hold){
        _timer --;
        _return -= _incr[2];
      }
      break;

      default:
      _return = 0;
      break;

    }
    return (_return >>8);
  };

};


#endif
