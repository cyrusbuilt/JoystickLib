/*
JoystickLib.cpp - Multi-instance joystick library for Arduino.

Author: Chris Brunner <cyrusbuilt at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "JoystickLib.h"
#include "Arduino.h"

Joystick::Joystick() {
	this->setJoystickPins(A0, A1);
	this->setThreshold(JL_DEFAULT_X_POS_LOW, JL_DEFAULT_X_POS_HIGH, JL_DEFAULT_Y_POS_LOW, JL_DEFAULT_Y_POS_HIGH);
	this->_currentState = CENTER;
	this->clearCallbacks();
}

Joystick::Joystick(short x, short y) {
	this->setJoystickPins(x, y);
	this->setThreshold(JL_DEFAULT_X_POS_LOW, JL_DEFAULT_X_POS_HIGH, JL_DEFAULT_Y_POS_LOW, JL_DEFAULT_Y_POS_HIGH);
	this->_currentState = CENTER;
	this->clearCallbacks();
}

Joystick::~Joystick() {
	this->clearCallbacks();
}

void Joystick::setJoystickPins(short x, short y) {
	this->_x_analog_pin = x;
	this->_y_analog_pin = y;
	pinMode(this->_x_analog_pin, INPUT);
	pinMode(this->_y_analog_pin, INPUT);
}

void Joystick::setThreshold(int xLow, int xHigh, int yLow, int yHigh) {
	this->_x_pos_low = xLow;
	this->_x_pos_high = xHigh;
	this->_y_pos_low = yLow;
	this->_y_pos_high = yHigh;
}

void Joystick::clearCallbacks() {
	this->centerCallback = NULL;
	this->upCallback = NULL;
	this->rightUpCallback = NULL;
	this->rightCallback = NULL;
	this->rightDownCallback = NULL;
	this->downCallback = NULL;
	this->leftDownCallback = NULL;
	this->leftCallback = NULL;
	this->leftUpCallback = NULL;
	this->notCenterCallback = NULL;
}

void Joystick::calibrate() {
	int i = 0;
	int xCenter = 0;
	for (i = 0; i < 10; i++) {
		xCenter += analogRead(this->_x_analog_pin);
	}

	xCenter /= i;

	int yCenter = 0;
	for (i = 0; i < 10; i++) {
		yCenter += analogRead(this->_y_analog_pin);
	}

	yCenter /= i;

	this->_stroke = max(this->_x_analog_pin, this->_y_analog_pin) * 1.01;
	this->setThreshold(xCenter - JL_CENTER_TOLERANCE,
						xCenter + JL_CENTER_TOLERANCE,
						yCenter - JL_CENTER_TOLERANCE,
						yCenter + JL_CENTER_TOLERANCE);
}

void Joystick::loop() {
	int x = 0;
	int y = 0;

	// Read both axis'.
	this->_xPos = analogRead(this->_x_analog_pin);
	this->_yPos = analogRead(this->_y_analog_pin);

	// Compute X-axis positional value. Range is -100 (left) -> 0 (center) -> +100 (right).
	if (this->_xPos > this->_x_pos_high) {
		x = 1;
		this->_xPos = map(this->_xPos, this->_x_pos_high, this->_x_pos_high + this->_x_pos_low, 0, 100);
		this->_xPos = constrain(this->_xPos, 0, 100);
	}
	else if (this->_xPos < this->_x_pos_low) {
		x = -1;
		this->_xPos = map(this->_xPos, 0, this->_x_pos_low, -100, 0);
	}
	else {
		this->_xPos = 0;
	}

	// Compute Y-axis positional value. Range is -100 (down) -> 0 (center) -> +100 (up).
	if (this->_yPos > this->_y_pos_high) {
		y = 1;
		this->_yPos = map(this->_yPos, this->_y_pos_high, this->_y_pos_high + this->_y_pos_low, 0, 100);
		this->_yPos = constrain(this->_yPos, 0, 100);
	}
	else if (this->_yPos < this->_y_pos_low) {
		y = -1;
		this->_yPos = map(this->_yPos, 0, this->_y_pos_low, -100, 0);
	}
	else {
		this->_yPos = 0;
	}

	// Now determine what direction we're going in.
	JoystickStates state = CENTER;
	if (x == -1) {
		// Handle left-down/left/left-up.
		if (y == -1) {
			state = LEFT_DOWN;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->leftDownCallback != NULL) {
					this->leftDownCallback();
				}
			}
		}
		else if (y == 0) {
			state = LEFT;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->leftCallback != NULL) {
					this->leftCallback();
				}
			}
		}
		else {
			state = LEFT_UP;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->leftUpCallback != NULL) {
					this->leftUpCallback();
				}
			}
		}
	}
	else if (x == 0) {
		// Handle up/center/down.
		if (y == -1) {
			state = DOWN;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->downCallback != NULL) {
					this->downCallback();
				}
			}
		}
		else if (y == 0) {
			state = CENTER;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->centerCallback != NULL) {
					this->centerCallback();
				}
			}
		}
		else {
			state = UP;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->upCallback != NULL) {
					this->upCallback();
				}
			}
		}
	}
	else {
		// Handle right-down/right/right-up.
		if (y == -1) {
			state = RIGHT_DOWN;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->rightDownCallback != NULL) {
					this->rightDownCallback();
				}
			}
		}
		else if (y == 0) {
			state = RIGHT;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->rightCallback != NULL) {
					this->rightCallback();
				}
			}
		}
		else {
			state = RIGHT_UP;
			if (this->_currentState != state) {
				this->_currentState = state;
				if (this->rightUpCallback != NULL) {
					this->rightUpCallback();
				}
			}
		}
	}
}

bool Joystick::isCenter() {
	return (this->_currentState == CENTER);
}

bool Joystick::isUp() {
	return (this->_currentState == UP);
}

bool Joystick::isRightUp() {
	return (this->_currentState == RIGHT_UP);
}

bool Joystick::isRight() {
	return (this->_currentState == RIGHT);
}

bool Joystick::isRightDown() {
	return (this->_currentState == RIGHT_DOWN);
}

bool Joystick::isDown() {
	return (this->_currentState == DOWN);
}

bool Joystick::isLeftDown() {
	return (this->_currentState == LEFT_DOWN);
}

bool Joystick::isLeft() {
	return (this->_currentState == LEFT);
}

bool Joystick::isLeftUp() {
	return (this->_currentState == LEFT_UP);
}

bool Joystick::isNotCenter() {
	return (this->_currentState != CENTER);
}

int Joystick::getX() {
	return this->_xPos;
}

int Joystick::getY() {
	return this->_yPos;
}

void Joystick::onCenter(void (*centerCallback)(void)) {
	this->centerCallback = centerCallback;
}

void Joystick::onUp(void (*upCallback)(void)) {
	this->upCallback = upCallback;
}

void Joystick::onRightUp(void (*rightUpCallback)(void)) {
	this->rightUpCallback = rightUpCallback;
}

void Joystick::onRight(void (*rightCallback)(void)) {
	this->rightCallback = rightCallback;
}

void Joystick::onRightDown(void (*rightDownCallback)(void)) {
	this->rightDownCallback = rightDownCallback;
}

void Joystick::onDown(void (*downCallback)(void)) {
	this->downCallback = downCallback;
}

void Joystick::onLeftDown(void (*leftDownCallback)(void)) {
	this->leftDownCallback = leftDownCallback;
}

void Joystick::onLeft(void (*leftCallback)(void)) {
	this->leftCallback = leftCallback;
}

void Joystick::onLeftUp(void (*leftUpCallback)(void)) {
	this->leftUpCallback = leftUpCallback;
}

void Joystick::onNotCenter(void (*notCenterCallback)(void)) {
	this->notCenterCallback = notCenterCallback;
}