// Do not remove the include below
#include "CarCam.h"

#define D(input) {Serial.print(input); Serial.flush();}
#define Dln(input) {Serial.println(input); Serial.flush();}

#define BTN_PIN 9
#define REV_PIN 8

#define LONG_PRESS 1000
#define TIMEOUT 5000

volatile boolean lastLong = false;
volatile byte oldPins = 0x0F;

volatile unsigned long tLastAction = 0;

volatile unsigned long tOn = 0;
volatile unsigned long tOff = 0;

StateMachine stateMachine = StateMachine();
Switcher switcher = Switcher();

enum Event {
	Timeout, Push, LongPush, ReverseOn, ReverseOff
};

void handleEvent(Event event){
	switch (event) {
		case (Push):
			stateMachine.buttonPush();
			break;
		case (LongPush):
			stateMachine.buttonLongPush();
			break;
		case (ReverseOn):
			stateMachine.reverseOn();
			break;
		case (ReverseOff):
			stateMachine.reverseOff();
			break;
		case (Timeout):
			stateMachine.timeout();
			break;
		default:
			break;
	}
	switcher.doSwitch(stateMachine.getState());
}

void button() {
	tLastAction = millis();
	byte newPins = PIND;
	//Serial.println(newPins, BIN);

	byte change = newPins ^ oldPins;
	byte btn = !bitRead(newPins, BTN_PIN);
	byte rev = !bitRead(newPins, REV_PIN);;
	byte changeBtn = change & bit(BTN_PIN);
	byte changeRev = change & bit(REV_PIN);

	if ( changeBtn ) {
		//D("BTN ");
		//Dln(btn);

		btn ? tOn = tLastAction : tOff = tLastAction;

		if (!btn && tOff - tOn < LONG_PRESS) {
			//Dln("BTN");
			handleEvent(Push);
		}
		if (!btn) {
			lastLong = false;
		}
	}
	if ( changeRev ) {
		if (rev) {
			handleEvent(ReverseOn);
		} else {
			handleEvent(ReverseOff);
		}
	}
	if ( changeBtn || changeRev ) {
		oldPins = newPins;
	}
}

//The setup function is called once at startup of the sketch
void setup()
{

	Serial.begin(115200);
	Dln("Start");
	pinMode(BTN_PIN, INPUT_PULLUP);
	pinMode(REV_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BTN_PIN), button, CHANGE);
	attachInterrupt(digitalPinToInterrupt(REV_PIN), button, CHANGE);
	interrupts();
}

// The loop function is called in an endless loop
void loop()
{
	//Dln(sleepForever);
	unsigned long tCurrent = millis();
	if( !lastLong && ( tOn > tOff ) && ( tCurrent - tOn > LONG_PRESS ) ) {
		handleEvent(LongPush);
		lastLong = true;
	}

	if ( tCurrent - tLastAction > TIMEOUT) {
		handleEvent(Timeout);
	}


	if ( stateMachine.getState() == Off )  {
		Dln("Sleep");
		LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
	}
}
