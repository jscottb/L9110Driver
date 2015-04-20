// L9110 Motor driver Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include <avr/io.h>
#include "WProgram.h"
#endif

#include "L9110Driver.h"

L9110_Motor::L9110_Motor(uint8_t ia_pin, uint8_t ib_pin) {
 	motor_ia =     ia_pin;
	motor_ib = ib_pin;
	pinMode(motor_ia, OUTPUT);
	pinMode(motor_ib, OUTPUT);
}

bool L9110_Motor::run(uint8_t cmds) {
	if (((FORWARD | BACKWARD) & cmds) == (FORWARD | BACKWARD)) {
		return false;
	}
	if (((BRAKE | RELEASE) & cmds) == (BRAKE | RELEASE)) {
		return false;
	}
	if ((cmds & FORWARD) == FORWARD) {
      analogWrite(motor_ia, currentspeed);
		analogWrite(motor_ib, LOW);
		runstate = (runstate & (BRAKE | RELEASE)) | FORWARD;
	}
	if ((cmds & BACKWARD) == BACKWARD) {
      analogWrite(motor_ib, currentspeed);
		analogWrite(motor_ia, LOW);
		runstate = (runstate & (BRAKE | RELEASE)) | BACKWARD;
	}
	if ((cmds & RELEASE) == RELEASE) {
  	   if ((runstate & FORWARD) == FORWARD) {
         analogWrite(motor_ia, currentspeed);
		   analogWrite(motor_ib, LOW);
      }

      if ((runstate & BACKWARD) == BACKWARD) {
         analogWrite(motor_ib, currentspeed);
		   analogWrite(motor_ia, LOW);
      }

      runstate = (runstate & (FORWARD | BACKWARD)) | RELEASE;
	}

	if ((cmds & BRAKE) == BRAKE) {
           analogWrite(motor_ia, LOW);
           analogWrite(motor_ib, LOW);
           runstate = (runstate & (FORWARD | BACKWARD)) | BRAKE;
	}
	return true;
}

void L9110_Motor::setSpeed(uint8_t speed) {
    if (speed > 255) speed = 255;
    else if (speed < 0) speed = 0;
    currentspeed = speed;
    if ((runstate & FORWARD) == FORWARD) {
       analogWrite(motor_ia, currentspeed);
       analogWrite(motor_ib, LOW);
    }

    if ((runstate & BACKWARD) == BACKWARD) {
       analogWrite(motor_ib, currentspeed);
       analogWrite(motor_ia, LOW);
    }
}

uint8_t L9110_Motor::getSpeed(void) {
   return (uint8_t) currentspeed;
}

uint8_t L9110_Motor::getState(void) {
	return runstate & (BRAKE | RELEASE);
}

uint8_t L9110_Motor::getDirection(void) {
	return runstate & (FORWARD | BACKWARD);
}
