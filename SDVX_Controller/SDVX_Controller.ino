//
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Joystick.h>
//#include <Keyboard.h>

#define BT_A 4
#define BT_B 5
#define BT_C 8
#define BT_D 7
#define FX_R 10
#define FX_L 9
#define START 6

#define ENCODER_L0 3
#define ENCODER_L1 2

#define ENCODER_R0 0
#define ENCODER_R1 1

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   11, 0,                   // Button Count, Hat Switch Count
                   false, false, false,     // X, Y , Z
                   false, false, false,     // Rx, Ry, Rz
                   false, false,            // rudder, throttle
                   false, false, false);    // accelerator, brake, steering

Encoder enc_r(ENCODER_R0, ENCODER_R1);
Encoder enc_l(ENCODER_L0, ENCODER_L1);

long count_l, count_r;


void setup() {
  pinMode(BT_A, INPUT_PULLUP);
  pinMode(BT_B, INPUT_PULLUP);
  pinMode(BT_C, INPUT_PULLUP);
  pinMode(BT_D, INPUT_PULLUP);
  pinMode(FX_L, INPUT_PULLUP);
  pinMode(FX_R, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  Joystick.begin(false);
}

void loop() {
//  count_l = enc_l.read();
//  count_r = enc_r.read();
  
  Joystick.setButton(0, !digitalRead(BT_A));
  Joystick.setButton(1, !digitalRead(BT_B));
  Joystick.setButton(2, !digitalRead(BT_C));
  Joystick.setButton(3, !digitalRead(BT_D));
  Joystick.setButton(4, !digitalRead(FX_L));
  Joystick.setButton(5, !digitalRead(FX_R));
  Joystick.setButton(6, !digitalRead(START));

  // LEFT ENCODER //
  if (enc_l.read() == 0)
  {
    Joystick.setButton(7, false);
    Joystick.setButton(8, false);
  }
  else
  {
    if (enc_l.read() > 0) // CW
    {
      Joystick.setButton(7, false);
      Joystick.setButton(8, true);
//      Keyboard.write('e');
    }
    else // CCW
    {
      Joystick.setButton(7, true);
      Joystick.setButton(8, false);
//      Keyboard.write('w');
    }
    enc_l.write(0);
  }

  // RIGHT ENCODER //
  if (enc_r.read() == 0)
  {
    Joystick.setButton(9, false);
    Joystick.setButton(10, false);
  }
  else
  {
    if (enc_r.read() > 0) // CW
    {
      Joystick.setButton(9, false);
      Joystick.setButton(10, true);
//      Keyboard.write('o');
    }
    else // CCW
    {
      Joystick.setButton(9, true);
      Joystick.setButton(10, false);
//      Keyboard.write('i');
    }
    enc_r.write(0);
  }
  Joystick.sendState();
}
