int id;
void setup() {
  // put your setup code here, to run once:
  id = 0;
  //pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i < 3; ++i){
    Serial.println(i+1);
    delay(1000);
  }
}
