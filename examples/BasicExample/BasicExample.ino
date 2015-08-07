/*
	Basic joystick usage example.
 */


#include "Arduino.h"
#include "JoystickLib.h"

Joystick stick(A0, A1);

void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(10);
	}

	// Calibrate the joystick. For this to be effective, the joystick should
	// be resting at its center position.
	stick.calibrate();
}

void loop() {
	stick.loop();
	Serial.println();
	Serial.println();

	// Figure out what direction the joystick is in and print it.
	if (stick.isUp()) {
		Serial.println(F("Up"));
	}

	if (stick.isRightUp()) {
		Serial.println(F("Right-Up"));
	}

	if (stick.isRight()) {
		Serial.println(F("Right"));
	}

	if (stick.isRightDown()) {
		Serial.println(F("Right-Down"));
	}

	if (stick.isDown()) {
		Serial.println(F("Down"));
	}

	if (stick.isLeftDown()) {
		Serial.println(F("Left-Down"));
	}

	if (stick.isLeft()) {
		Serial.println(F("Left"));
	}

	if (stick.isLeftUp()) {
		Serial.println(F("Left-Up"));
	}

    delay(300);
}
