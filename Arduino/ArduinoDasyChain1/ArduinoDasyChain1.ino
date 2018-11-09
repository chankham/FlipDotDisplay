int id;
int incoming;
void setup() {
  // put your setup code here, to run once:
  id = 3;
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    
    incoming = Serial.parseInt();
    Serial.println(incoming);
    if(id == incoming){
      digitalWrite(12, !digitalRead(12));
    }
  }
}
