/*
 * CameraState.h
 *
 *  Created on: 25 Jan 2016
 *      Author: andrew
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

enum State {
	Off, Side, Back
};

class StateMachine {

public:
	StateMachine();
	virtual ~StateMachine();
	void buttonPush();
	void buttonLongPush();
	void reverseOn();
	void reverseOff();
	void timeout();
	State getState();
	char* getStateString();
private:
	State state;
	State prevState;
	void setState(State);
};

#endif /* STATEMACHINE_H_ */
