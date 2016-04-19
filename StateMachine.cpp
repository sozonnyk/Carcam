#include "StateMachine.h"

StateMachine::StateMachine() {
	setState(Off);
}

StateMachine::~StateMachine() {
}

void StateMachine::setState(State state) {
	this->prevState = this->state;
	this->state = state;
}

State StateMachine::getState() {
	return this->state;
}

char* StateMachine::getStateString() {
	switch (this->state) {
	case (Off):
		return "Off";
	case (Side):
		return "Side";
	case (Back):
		return "Back";
	}
}

void StateMachine::buttonPush() {
	switch (this->state) {
	case (Off):
	case (Back):
		setState(Side);
		break;
	case (Side):
		setState(Back);
		break;
	default:
		break;
	}
}

void StateMachine::buttonLongPush() {
	switch (this->state) {
	case (Side):
	case (Back):
		setState(Off);
		break;
	default:
		break;
	}
}

void StateMachine::reverseOn() {
	switch (this->state) {
	case (Off):
	case (Side):
		setState(Back);
		break;
	default:
		break;
	}
}

void StateMachine::reverseOff() {
	switch (this->state) {
	case (Back):
		if (this->prevState == Side)
			setState(Side);
		if (this->prevState == Off)
			setState(Off);
		break;
	default:
		break;
	}
}

void StateMachine::timeout() {
	switch (this->state) {
	case (Side):
	case (Back):
		setState(Off);
		break;
	default:
		break;
	}
}
