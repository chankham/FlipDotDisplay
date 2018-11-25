#include <MultiShiftRegister.h>
int latchPin = 8;
int clockPin = 11;
int dataPin = 12;
int numberOfRegisters = 21;

//# Setup group of shift registers and name it `msr`.
//# All outputs are initialized to low/off.
MultiShiftRegister msr (numberOfRegisters, latchPin, clockPin, dataPin);


void setup() {
  // put your setup code here, to run once:
pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i< 162; i+=1){
    if(i == 50)
      i = 56;
    if(i == 106)
      i += 6;
    msr.set_shift(i);
    delay(500);
    Serial.print("jjjChanging Dot ");
    Serial.println(i);
    msr.clear_shift(i);
  }
  while(1);
}
