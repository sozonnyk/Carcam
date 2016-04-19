/*
 * Switcher.h
 *
 *  Created on: 31 Mar 2016
 *      Author: andrew
 */

#ifndef SWITCHER_H_
#define SWITCHER_H_
#include "StateMachine.h"
#include "Arduino.h"
#include "Servo.h"

class Switcher {
public:
	void doSwitch(State state);
	Switcher();
	virtual ~Switcher();
};

#endif /* SWITCHER_H_ */
