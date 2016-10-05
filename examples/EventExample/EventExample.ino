
/*
	Basic joystick event example
 */

#include "Arduino.h"
#include "JoystickLib.h"

Joystick stick(A0, A1);

void printPosition() {
	Serial.print(F("X: "));
	Serial.println(stick.getX());
	Serial.print(F("Y: "));
	Serial.println(stick.getY());
	Serial.println();
}

void onUpHandler() {
	Serial.println(F("Direction: Up"));
	printPosition();
}

void onRightUpHandler() {
	Serial.println(F("Direction: Right-Up"));
	printPosition();
}

void onRightHandler() {
	Serial.println(F("Direction: Right"));
	printPosition();
}

void onRightDownHandler() {
	Serial.println(F("Direction: Right-Down"));
	printPosition();
}

void onDownHandler() {
	Serial.println(F("Direction: Down"));
	printPosition();
}

void onLeftDownHandler() {
	Serial.println(F("Direction: Left-Down"));
	printPosition();
}

void onLeftHandler() {
	Serial.println(F("Direction: Left"));
	printPosition();
}

void onLeftUpHandler() {
	Serial.println(F("Direction: Left-Up"));
	printPosition();
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		delay(10);
	}

	// Calibrate and print out position.
	Serial.println();
	Serial.print(F("Calibrating.... "));
	stick.calibrate();
	Serial.println(F("Done."));
	Serial.println(F("Calibrated zero position: "));
	printPosition();

	// Wire up event handlers.
	stick.onUp(onUpHandler);
	stick.onRightUp(onRightUpHandler);
	stick.onRight(onRightHandler);
	stick.onRightDown(onRightDownHandler);
	stick.onDown(onDownHandler);
	stick.onLeftDown(onLeftDownHandler);
	stick.onLeft(onLeftHandler);
	stick.onLeftUp(onLeftUpHandler);
}

void loop() {
	// Read joystick and process events every 300ms.
	stick.loop();
    delay(300);
}
