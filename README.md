==========================================================================
# JoystickLib :: Joystick library for Arduino
[![Build Status](https://travis-ci.org/cyrusbuilt/JoystickLib.svg?branch=master)](https://travis-ci.org/cyrusbuilt/JoystickLib)
==========================================================================

## LICENSE

Licensed under GPL v2 (the "License"); you may not use this library except
in compliance with the License.  You may obtain a copy of the License at:

http://www.gnu.org/licenses/gpl-2.0.html

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Description

This is a library that provides an API foor reading one or more Joysticks
attached to an Arduino. This is a multi-instance library, so you can read
multiple joysticks. Only one analog pin is needed per axis. Most analog
joysticks are basically just (2) potentiometers that act as voltage dividers.
This library is based on the JoystickShield library (https://github.com/sudar/JoystickShield).
This library, however, does not process button events. It also does not
process joystick events separately. Events are fired immediately upon
detecting a state change (if, and only if, a state change *actually*
occurs).

## How to use

Copy the entire folder containing this library to the "libraries" folder
of your Arduino installation or sketchbook. Then include JoystickLib.h in
your sketch. See example below:
```cpp
#include "Arduino.h"
#include "JoystickLib.h"

// Create joystick instance attached to pins A0 (X-axis) and A1
// Y-axis. This will also set the default threshold values.
Joystick stick(A0, A1);

void setup() {
	Serial.begin(9600);
	stick.calibrate();
}

void loop() {
	stick.loop();

	Serial.print("X = ");
	Serial.println(stick.getX());

	Serial.print("Y = ");
	Serial.println(stick.getY());

	delay(300);
}
```

## How to install

If you are using PlatformIO (http://platformio.org/), you can simply run the following command:
```
platformio lib install joysticklib
```

Otherwise, download the zip from https://github.com/cyrusbuilt/ArduinoHAF/archive/master.zip then extract its contents to a folder called "ArduinoHAF" and then move that folder to your libraries folder.
