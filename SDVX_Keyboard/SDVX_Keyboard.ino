/**
 * For use with a 32u4-based Arduino (Pro Micro, Leonardo, etc).
 * 
 * Refer to defines below for pinout.
 */
#define ENCODER_OPTIMIZE_INTERRUPTS
#define KNOBS_USE_KEYBOARD
#include <Encoder.h>
#include <Keyboard.h>
#include <Mouse.h>

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

  Mouse.begin();
  Keyboard.begin();
}

void loop() {
//  count_l = enc_l.read();
//  count_r = enc_r.read();

  digitalRead(START) ? Keyboard.release(KEY_RETURN) : Keyboard.press(KEY_RETURN);

  !digitalRead(BT_A) ? Keyboard.press('d') : Keyboard.release('d');
  !digitalRead(BT_B) ? Keyboard.press('f') : Keyboard.release('f');
  !digitalRead(BT_C) ? Keyboard.press('j') : Keyboard.release('j');
  !digitalRead(BT_D) ? Keyboard.press('k') : Keyboard.release('k');

  !digitalRead(FX_L) ? Keyboard.press('c') : Keyboard.release('c');
  !digitalRead(FX_R) ? Keyboard.press('m') : Keyboard.release('m');
  
  // LEFT ENCODER //
  int leftInit = enc_l.read();
  int rightInit = enc_r.read();
  delay(3);
  
  #ifdef KNOBS_USE_KEYBOARD
    int leftDelta = enc_l.read() - leftInit;
    int rightDelta = enc_r.read() - rightInit;
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
    Mouse.move(enc_l.read()-leftInit, 0, 0);
    Mouse.move(0, enc_r.read()-rightInit, 0);
  #endif
  
  enc_l.write(0);
  enc_r.write(0);
}
