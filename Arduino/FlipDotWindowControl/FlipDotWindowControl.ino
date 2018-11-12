#include <MultiShiftRegister.h>
int latchPin = 8;
int clockPin = 11;
int dataPin = 12;

//// How many 8 bit shift registers we're talking to.
//# Two 8 bit registers can host 16 individuallly
//# addressable binary outputs.
int numberOfRegisters = 21;

//# Setup group of shift registers and name it `msr`.
//# All outputs are initialized to low/off.
MultiShiftRegister msr (numberOfRegisters, latchPin, clockPin, dataPin);

int current[75];
int receive[75];
int id;

void Display(int x[25]){
  Serial.println("\n\nDisplaying:");
    for(int j=0; j < 25; j++){
      if(j%5 == 0)
        Serial.println("");
      Serial.print(x[j]);
      Serial.print(' ');
    }
}

void setModule(int x[25], int modNum){
  int count = (modNum-1)*(50) ;
  const int changeAtATime = 5;
  int change[changeAtATime];
  int changeCount = 0;
  Display(x);
  for(int i=0; i<changeAtATime; ++i)
    change[i] = 0;
    
  for (int i = 0; i < 25; ++i){
      if(x[i] && !current[count]){
          current[count]=x[i];
      
          change[changeCount++] = count+1;
      }
        
      if(!x[i] && current[count]){
          change[changeCount++] = count;

          current[count]=x[i];
      }
      if(changeCount == changeAtATime || i == 24){
        int p = 0;
        int inter[2] = {700, 300};
      while(p < 2){
        for(int j=0; j < changeCount; ++j){
          //Serial.print("jjjChanging Dot ");
          //Serial.println(change[j]);
            msr.set_shift(change[j]);
        }
        delay(inter[p]);
        for(int j=0; j<changeCount; ++j){
            msr.clear_shift(change[j]);
        }
        delay(200);
        //Serial.print("ChangeCount: ");
        //Serial.println(changeCount);
        p++;
      }
      for(int j=0; j<changeAtATime; ++j)
            change[j] = 0;
      p=0;
      changeCount = 0;
      }
        
      count+=2;
      
  }
  delay(400);
}

void setWindow(int c[75]){
  int count = 0;
  for(int i = 0; i < 3; i++){
    int arr[25];
    memcpy(arr, c+count, 25*sizeof(int));
    
    setModule(arr, i+1);
    count+=25;
  }
}

void setup ()
{
    pinMode (latchPin, OUTPUT);
    pinMode (clockPin, OUTPUT);
    pinMode (dataPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Current:\n");
    for(int i = 0; i < 75; ++i){
      current[i] = 1;
      if(i%5 == 0 || i%25 == 0)
        Serial.println("");
      Serial.print(current[i]);
      Serial.print(' ');
      
    }

    id = 1;
    
    //setWindow(current);
}

int x[25] =    
    {0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0};
int y[25] =    
    {1, 1, 1, 1, 1,
     1, 1, 1, 1, 1,
     1, 1, 1, 1, 1,
     1, 1, 1, 1, 1,
     1, 1, 1, 1, 1};
int h[25] =    
    {0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0};
int e[25] =    
    {0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0};
int l[25] =    
    {0, 1, 0, 0, 0,
     0, 1, 0, 0, 0,
     0, 1, 0, 0, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0};
int o[25] =    
    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0};
int w[25] =    
    {1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 1, 0, 1,
     0, 1, 1, 1, 0,
     0, 1, 1, 1, 0};
int r[25] =    
    {0, 0, 1, 1, 1,
     0, 1, 1, 0, 0,
     0, 1, 0, 0, 0,
     0, 1, 0, 0, 0,
     0, 1, 0, 0, 0};
int d[25] =    
    {0, 1, 1, 0, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 0, 0};

int ex[25] =    
    {0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 1, 0, 0};

void error(){
  Serial.println("Wrong string");
}

void loop ()
{
  
//  if(Serial.available()>0){
//    
////    incoming = Serial.readString();
////    Serial.println(incoming);
////    if(id == incoming[1]){
////      for(int i = 0; i < 75; ++i)
////        receive[i] = incoming[i+3];
////       if(incoming[78] != '#')
////        error();
////       else
////        setWindow(receive);
////      digitalWrite(12, !digitalRead(12));
////    }
//  }
  setModule(x, 1);
  setModule(h, 1);
  setModule(e, 1);
  setModule(l, 1);
  setModule(l, 1);
  setModule(o, 1);
  setModule(w, 1);
  setModule(o, 1);
  setModule(r, 1);
  setModule(l, 1);
  setModule(d, 1);
  setModule(ex, 1);
  setModule(y, 1);

  Serial.print("Done!!!");
  while(1);

  
}

