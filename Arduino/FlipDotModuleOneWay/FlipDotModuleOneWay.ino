#include <MultiShiftRegister.h>
int latchPin = 8;
int clockPin = 11;
int dataPin = 12;
int numberOfRegisters = 7;

//# Setup group of shift registers and name it `msr`.
//# All outputs are initialized to low/off.
MultiShiftRegister msr (numberOfRegisters, latchPin, clockPin, dataPin);


void setup() {
  // put your setup code here, to run once:
pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i< 50; i+=1){
    msr.set_shift(i);
    delay(800);
    msr.clear_shift(i);
  }
}
