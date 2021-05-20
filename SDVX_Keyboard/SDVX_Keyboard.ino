/**
 * For use with a 32u4-based Arduino (Pro Micro, Leonardo, etc).
 * "Pro Micro" knock-offs use "Arduino Micro" for board firmware.
 */
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Keyboard.h>
#include <Mouse.h>

// un-comment to use VOL output as keypress instead of mouse
//#define KNOBS_USE_KEYBOARD

//Pinout (Arudino pins); change to fit your setup
#define BT_A 7
#define BT_B 6
#define BT_C 5
#define BT_D 4
#define FX_R 8
#define FX_L 9
#define START 16
#define ENCODER_L0 3
#define ENCODER_L1 2
#define ENCODER_R0 0
#define ENCODER_R1 1

Encoder enc_r(ENCODER_R0, ENCODER_R1);
Encoder enc_l(ENCODER_L0, ENCODER_L1);

// for Serial output funs
long count_l = 0, count_r = 0;
unsigned long i = 0;

void setup() {
  pinMode(BT_A, INPUT_PULLUP);
  pinMode(BT_B, INPUT_PULLUP);
  pinMode(BT_C, INPUT_PULLUP);
  pinMode(BT_D, INPUT_PULLUP);
  pinMode(FX_L, INPUT_PULLUP);
  pinMode(FX_R, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);

  Mouse.begin();
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // Buttons //
  digitalRead(START) ? Keyboard.release(KEY_RETURN) : Keyboard.press(KEY_RETURN);

  !digitalRead(BT_A) ? Keyboard.press('d') : Keyboard.release('d');
  !digitalRead(BT_B) ? Keyboard.press('f') : Keyboard.release('f');
  !digitalRead(BT_C) ? Keyboard.press('j') : Keyboard.release('j');
  !digitalRead(BT_D) ? Keyboard.press('k') : Keyboard.release('k');

  !digitalRead(FX_L) ? Keyboard.press('c') : Keyboard.release('c');
  !digitalRead(FX_R) ? Keyboard.press('m') : Keyboard.release('m');

  // Encoder (VOL) //
  int leftInit = enc_l.read();
  int rightInit = enc_r.read();
  delay(1);
  int leftDelta = enc_l.read() - leftInit;
  int rightDelta = enc_r.read() - rightInit;
  
  #ifdef KNOBS_USE_KEYBOARD
    if(leftDelta != 0)
    {
      if(leftDelta < 0)
      {
        Keyboard.release('s');
        Keyboard.press('a');
      }
      else
      {
        Keyboard.release('a');
        Keyboard.press('s');
      }
    }
    else
    {
      Keyboard.release('a');
      Keyboard.release('s');
    }
    if(rightDelta != 0)
    {
      if(rightDelta < 0)
      {
        Keyboard.release(';');
        Keyboard.press('l');
      }
      else
      {
        Keyboard.release('l');
        Keyboard.press(';');
      }
    }
    else
    {
      Keyboard.release('l');
      Keyboard.release(';');
    }
  #else
    Mouse.move(leftDelta, 0, 0);
    Mouse.move(0, rightDelta, 0);
  #endif
  enc_l.write(0);
  enc_r.write(0);

  count_l += leftDelta;
  count_r += rightDelta;
  Serial.println(count_l+count_r);
}
