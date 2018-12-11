#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;

// set up a new serial object
SoftwareSerial mySerial (rxPin, txPin);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  mySerial.begin(9600);
}
// the loop routine runs over and over again forever:
void processData(){
  
}
void loop() {
  // read the input pin:
  String data = "";
  if(Serial.available() > 0){
    char rr = Serial.read();
    Serial.print(rr);
    
    if(rr == '\n'){
      Serial.println(data);
      mySerial.println(data);
      data="";
    }
    else{
    data.concat(rr);
    }

  }
}
