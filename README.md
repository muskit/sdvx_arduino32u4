# sdvx_arduino32u4
SDVX controller sketch for ATmega32U4-based Arduinos.

* `SDVX_Keyboard` is recommended, sends keyboard (and optionally mouse) signals.
* `SDVX_Controller` sends controller HID signals, may need rework.

## Required Libraries
* [Encoder](https://www.arduino.cc/reference/en/libraries/encoder/)
* [Joystick](https://www.arduino.cc/reference/en/libraries/joystick/) (for `SDVX_Controller`)
