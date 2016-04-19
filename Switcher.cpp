/*
 * Switcher.cpp
 *
 *  Created on: 31 Mar 2016
 *      Author: andrew
 */

#include "Switcher.h"

#define POWER_PIN 10
#define SWITCH_PIN 11

#define CAM_SIDE 255
#define CAM_BACK 180

#define D(input) {Serial.print(input); Serial.flush();}
#define Dln(input) {Serial.println(input); Serial.flush();}

//Video switcher: 0-149: input 1, 150 - 223: input 2, 224-255: input 3.

void Switcher::doSwitch(State state) {
	switch (state) {
	case Off:
		Dln("Off");
		//Power cameras off
		digitalWrite(POWER_PIN, LOW);
		analogWrite(SWITCH_PIN,0);
		break;
	case Side:
		Dln("Side");
		digitalWrite(POWER_PIN, HIGH);
		analogWrite(SWITCH_PIN,CAM_SIDE);
		break;
	case Back:
		Dln("Back");
		digitalWrite(POWER_PIN, HIGH);
		analogWrite(SWITCH_PIN,CAM_BACK);
		break;
	default:
		break;
	}
}

Switcher::Switcher() {
	pinMode(POWER_PIN, OUTPUT);
	pinMode(SWITCH_PIN, OUTPUT);
	doSwitch(Off);
}

Switcher::~Switcher() {
}

