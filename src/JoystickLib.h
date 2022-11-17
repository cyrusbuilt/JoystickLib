/*
JoystickLib.h - Multi-instance joystick library for Arduino.

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

#ifndef JoystickLib_h
#define JoystickLib_h

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#define JL_CENTER_TOLERANCE 5
#define JL_DEFAULT_X_POS_LOW 510
#define JL_DEFAULT_X_POS_HIGH 530
#define JL_DEFAULT_Y_POS_LOW 510
#define JL_DEFAULT_Y_POS_HIGH 540

/**
 * Possible joystick states.
 */
enum JoystickStates {
	CENTER,
	UP,
	RIGHT_UP,
	RIGHT,
	RIGHT_DOWN,
	DOWN,
	LEFT_DOWN,
	LEFT,
	LEFT_UP
};

/**
 * @brief The Joystick class provides an API for reading positional data
 * from an analog joystick.
 */
class Joystick {
public:
	/**
	 * Initializes a new instance of the Joystick class. This is the default
	 * constructor, which assumes that the X-axis is connected to analog input
	 * A0 and the Y-axis is connected to analog input A1.
	 */
	Joystick();

	/**
	 * Initializes a new instance of the Joystick class with the analog input
	 * pins to use for the X and Y axis.
	 * @param x The analog input pin to read for the X-axis position.
	 * @param y The analog input pin to read for the Y-axis position.
	 */
	Joystick(short x, short y);

	/**
	 * Class destructor.
	 */
	~Joystick();

	/**
	 * Sets the analog input pins to use for the X and Y-axis.
	 * @param x The analog input pin to read for the X-axis position.
	 * @param y The analog input pin to read for the Y-axis position.
	 */
	void setJoystickPins(short x, short y);

	/**
	 * Configures the threshold values for the joystick.
	 * @param xLow  The low threshold for the X-axis.
	 * @param xHigh The high threshold for the X-axis.
	 * @param yLow  The low threshold for the Y-axis.
	 * @param yHigh The high threshold for the Y-axis.
	 */
	void setThreshold(int xLow, int xHigh, int yLow, int yHigh);

	/**
	 * Calibrates the joystick based on "resting position" values.
	 */
	void calibrate();

	/**
	 * Reads the joystick positional values and processes event callbacks. This
	 * should be called within the main loop() method of your sketch.
	 */
	void loop();

	/**
	 * Checks to see if the joystick is in the center position.
	 * @return true if centered; Otherwise, false.
	 */
	bool isCenter();

	/**
	 * Checks to see if the joystick is in the up position.
	 * @return true if up; Otherwise, false.
	 */
	bool isUp();

	/**
	 * Checks to see if the joystick is in the right and up position.
	 * @return true if right-up; Otherwise, false.
	 */
	bool isRightUp();

	/**
	 * Checks to see if the joystick is in the right position.
	 * @return true if right; Otherwise, false.
	 */
	bool isRight();

	/**
	 * Checks to see if the joystick is in the right and down position.
	 * @return true if right-down; Otherwise, false.
	 */
	bool isRightDown();

	/**
	 * Checks to see if the joystick is in the down position.
	 * @return true if down; Otherwise, false.
	 */
	bool isDown();

	/**
	 * Checks to see if the joystick is in the left and down position.
	 * @return true if down; Otherwise, false.
	 */
	bool isLeftDown();

	/**
	 * Checks to see if the joystick is in the left position.
	 * @return true if left; Otherwise, false.
	 */
	bool isLeft();

	/**
	 * Checks to see if the joystick is in the left and up position.
	 * @return true if left-up; Otherwise, false.
	 */
	bool isLeftUp();

	/**
	 * Checks to see if the joystick is not centered.
	 * @return true if not centered; Otherwise, false.
	 */
	bool isNotCenter();

	/**
	 * Gets the X-axis value.
	 * @return The X-axis value.
	 */
	int getX();

	/**
	 * Gets the Y-axis value.
	 * @return The Y-axis value.
	 */
	int getY();

	/**
	 * Sets the method to call when the joystick is centered.
	 * @param centerCallback The method to call when centered.
	 */
	void onCenter(void (*centerCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the up position.
	 * @param upCallback The method to call when up.
	 */
	void onUp(void (*upCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the right-up position.
	 * @param rightUpCallback The method to call when right-up.
	 */
	void onRightUp(void (*rightUpCallback)(void));

	/**
	 * The method to call when the joystick is in the right position.
	 * @param rightCallback The method to call when right.
	 */
	void onRight(void (*rightCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the right-down position.
	 * @param rightDownCallback The method to call when right-down.
	 */
	void onRightDown(void (*rightDownCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the down position.
	 * @param downCallback The method to call when down.
	 */
	void onDown(void (*downCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the left-down position.
	 * @param leftDownCallback The method to call when left-down.
	 */
	void onLeftDown(void (*leftDownCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the left position.
	 * @param leftCallback The method to call when left.
	 */
	void onLeft(void (*leftCallback)(void));

	/**
	 * Sets the method to call when the joystick is in the left-up position.
	 * @param leftUpCallback The method to call when left-up.
	 */
	void onLeftUp(void (*leftUpCallback)(void));

	/**
	 * Sets the method to call when the joystick is not centered.
	 * @param notCenterCallback The method to call when not centered.
	 */
	void onNotCenter(void (*notCenterCallback)(void));
private:
	/**
	 * @brief clearCallbacks Initializes all callback points to null.
	 */
	void clearCallbacks();

	// Threshold values.
	int _x_pos_low;
	int _x_pos_high;
	int _y_pos_low;
	int _y_pos_high;

	// Joystick pins.
	short _x_analog_pin;
	short _y_analog_pin;

	// Joystick positioning.
	volatile int _xPos;
	volatile int _yPos;
	byte _stroke;

	// Current state.
	volatile JoystickStates _currentState;

	// Joystick callbacks.
	void (*centerCallback)(void);
  void (*upCallback)(void);
  void (*rightUpCallback)(void);
  void (*rightCallback)(void);
  void (*rightDownCallback)(void);
  void (*downCallback)(void);
  void (*leftDownCallback)(void);
  void (*leftCallback)(void);
  void (*leftUpCallback)(void);
	void (*notCenterCallback)(void);
};

#endif
