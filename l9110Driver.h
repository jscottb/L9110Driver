// L9110 MotorDriver Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#ifndef _L9110Driver_h_
#define _L9110Driver_h_

#include <inttypes.h>
#include <avr/io.h>

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8

class L9110_Motor {
public:
        L9110_Motor(uint8_t ia_pin, uint8_t ib_pin);
	bool run(uint8_t);
	void setSpeed(uint8_t);
        uint8_t getSpeed(void);
	uint8_t getState(void);
	uint8_t getDirection(void);
      	
private:
	uint8_t motor_ia, motor_ib, runstate, currentspeed;
};

#endif
