#include <MultiShiftRegister.h>

int latchPin  = 8;
int clockPin = 11;
int dataPin = 12;

// How many 8 bit shift registers we're talking to.
// Two 8 bit registers can host 16 individually
// addressable binary outputs.
int numberOfRegisters = 21;

// Setup group of shift registers and name it `msr`.
// All outputs are initialized to low/off.
MultiShiftRegister msr (numberOfRegisters , latchPin, clockPin, dataPin); 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}
 int dotnum = 51;
 int x = (dotnum*2 + 6*(int)((dotnum>25)?((dotnum>50)?(2):1):0)) - 2;
  
void loop() {
  // Prepare to turn on pin 5.
  // Pin 5 is still low/off.
  //for(int i = 0; i <= 16; i+=2){
 Serial.println(x);
  msr.set(x);

  // Shift data out, with appropriate latches.
  // Pin 5 is now high/on.
  msr.shift();

  delay(500);

  // Turn pin 5 back off.
  msr.clear(x);
  msr.shift();

   msr.set(x+1);

  // Shift data out, with appropriate latches.
  // Pin 5 is now high/on.
  msr.shift();

  delay(500);

  // Turn pin 5 back off.
  msr.clear(x+1);
  msr.shift();
//  delay(5000);
//  x+=2;
  //}

//
//  // Turn pin 12 (4th output on the second shift register)
//  // on and off again.
//  msr.set(12); 
//  msr.shift(); 
//  delay(1000);
//  msr.clear(12); 
//  msr.shift(); 
//
//  delay(1000);
//
//  // This set and shift business is getting repetitive.
//  // Let's do it in one line instead.
//  msr.set_shift(14);
//  delay(1000);
//  msr.clear_shift(14);
//
//  delay(1000);
//
//  // But wait, this is inefficient. It doesn't actually turn
//  // outputs 5 and 12 on simultaneously. There is a very tiny delay
//  // as it shifts output 5 before setting output 12. This may or
//  // may not be a problem, depending on your application.
//  msr.set_shift(5);
//  msr.set_shift(12);
//  delay(1000);
//  msr.clear_shift(5);
//  msr.clear_shift(12);
//
//  delay(1000);
//
//  // So, consider doing this to prepare both outputs before shifting them.
//  msr.set(5);
//  msr.set(12);
//  msr.shift();
//  delay(1000);
//  msr.clear(5);
//  msr.clear(12);
//  msr.shift();
//
//  delay(1000);
}
