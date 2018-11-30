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

void Display(int x[25]) {
  Serial.println("\n\nDisplaying:");
  for (int j = 0; j < 25; j++) {
    if (j % 5 == 0)
      Serial.println("");
    Serial.print(x[j]);
    Serial.print(' ');
  }
}

int getCurrent(int pin, int modNum) {
  if (pin % 2 == 0) {
    return ((pin - 6 * (modNum - 1)) / 2);
  }
  else {
    return ((pin - 1 - 6 * (modNum - 1)) / 2);
  }
}

void setModule(int x[25], int modNum) {
  int count = (modNum - 1) * (50) + 6 * (int)(modNum - 1);
  const int changeAtATime = 5;
  int change[changeAtATime];
  int changeCount = 0;
  //Display(x);
  for (int i = 0; i < changeAtATime; ++i)
    change[i] = 0;

  for (int i = 0; i < 25; ++i) {
    //Serial.print("Checking Dot, Curr d: ");
    int c = getCurrent(count, modNum);
//    Serial.print(c);
//    Serial.print(" ");
//    Serial.println(count);
    if (x[i] && !current[getCurrent(count, modNum)]) {
      current[getCurrent(count, modNum)] = x[i];

      change[changeCount++] = count + 1;
    }

    if (!x[i] && current[getCurrent(count, modNum)]) {
      change[changeCount++] = count;

      current[getCurrent(count, modNum)] = x[i];
    }
    if (changeCount == changeAtATime || i == 24) {
      int p = 0;
      int inter[2] = {700, 300};
      while (p < 2) {
        for (int j = 0; j < changeCount; ++j) {

          msr.set_shift(change[j]);
        }
        delay(inter[p]);
        for (int j = 0; j < changeCount; ++j) {
          msr.clear_shift(change[j]);
        }
        delay(50);
        //Serial.print("jjjChanging Dot ");
        //Serial.println(change[j]);
        //        Serial.print("ChangeCount: ");
        //        Serial.println(changeCount);
        p++;
      }
      for (int j = 0; j < changeAtATime; ++j)
        change[j] = 0;
      p = 0;
      changeCount = 0;
    }

    count += 2;

  }
  //Serial.println("Displayed:\n");
  //Display(x);
  //delay(0);
}

void setWindow(int c[75]) {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    int arr[25];
    memcpy(arr, c + count, 25 * sizeof(int));

    setModule(arr, i + 1);
    count += 25;
  }
}

int x[25] =
{ 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};
int y[25] =
{ 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1
};
int h[25] =
{ 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0
};
int e[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0
};
int l[25] =
{ 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0
};
int o[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};
int w[25] =
{ 1, 0, 0, 0, 1,
  1, 0, 0, 0, 1,
  1, 0, 1, 0, 1,
  0, 1, 1, 1, 0,
  0, 1, 1, 1, 0
};
int r[25] =
{ 0, 0, 1, 1, 1,
  0, 1, 1, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0
};
int d[25] =
{ 0, 1, 1, 0, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 0, 0
};

int ex[25] =
{ 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 0, 0, 0, 0,
  0, 1, 0, 1, 0
};

int i[25] =
{ 0, 1, 1, 1, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 1, 1, 1, 0
};

int an1[25] =
{ 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};
int an2[25] =
{ 1, 1, 0, 0, 0,
  1, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};
int an3[25] =
{ 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0,
  1, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};
int an4[25] =
{ 1, 1, 1, 1, 0,
  1, 1, 1, 0, 0,
  1, 1, 0, 0, 0,
  1, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};
int an5[25] =
{ 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0,
  1, 1, 1, 0, 0,
  1, 1, 0, 0, 0,
  1, 0, 0, 0, 0
};

int one[25] =
{ 0, 0, 1, 0, 0,
  0, 1, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0
};

int two[25] =
{ 0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0
};

int three[25] =
{ 0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0
};

int four[25] =
{ 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};

int five[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0
};

int six[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};

int seven[25] =
{ 0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};


int eight[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};


int nine[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};

int zero[25] =
{ 0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};

int ten[25] =
{ 1, 0, 1, 1, 1,
  1, 0, 1, 0, 1,
  1, 0, 1, 0, 1,
  1, 0, 1, 0, 1,
  1, 0, 1, 1, 1
};

int eleven[25] =
{ 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0
};


int twelve[25] =
{ 1, 0, 1, 1, 1,
  1, 0, 0, 0, 1,
  1, 0, 1, 1, 1,
  1, 0, 1, 0, 0,
  1, 0, 1, 1, 1
};

int sec[25] =
{ 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 1
};

int* digitToArr(int d) {
  switch (d) {
    case 0:
      return zero;
    case 1:
      return one;
    case 2:
      return two;
    case 3:
      return three;
    case 4:
      return four;
    case 5:
      return five;
    case 6:
      return six;
    case 7:
      return seven;
    case 8:
      return eight;
    case 9:
      return nine;
    case 10:
      return ten;
    case 11:
      return eleven;
    case 12:
      return twelve;
  }
}

void displayTime(long curr) {
  long temp = curr;
  int i = 3;
  while (i > 0) {
    if (i == 1) {
      temp = curr;
    }
    else {
      temp = curr % 10;
      curr = curr / 10;
    }

    setModule(digitToArr(temp), i--);

  }
}

void error() {
  Serial.println("Wrong string");
}

void toggleSecond() {
  Serial.println("I am toggleSecond");
  if (current[74] == 0) {
    setModule(sec, 3);
  }
  else {
    setModule(x, 3);
  }
}

void arduinoClock() {
  unsigned long time1 = millis();
  long curr = 906;
  while (1) {
    //toggleSecond();
    if ( millis() - time1 >= 1000) {
      time1 = millis();
      //toggleSecond();
      curr++;
      if (curr == 1260) {
        curr = 100;
      }
      if ((curr - 60) % 100 == 0) {
        curr = curr + 40;
      }
      displayTime(curr);

      Serial.print("Displayed:");
      Serial.println(curr);
    }
  }
}

void helloWorld() {
  setModule(h, 2);
  setModule(e, 2);
  setModule(l, 2);
  setModule(l, 2);
  setModule(o, 2);
  setModule(w, 2);
  setModule(o, 2);
  setModule(r, 2);
  setModule(l, 2);
  setModule(d, 2);
  setModule(ex, 2);

}


void clearModules() {
  setModule(x, 1);
  setModule(x, 2);
  setModule(x, 3);
}

void hi() {
  setModule(x, 1);
  setModule(h, 1);
  setModule(i, 2);
  setModule(ex, 3);
}

void readStdString(){
  if (Serial.available() > 0) {
        String incoming = Serial.readString();
        Serial.println(incoming);
        if(id == incoming[1]){
          for(int i = 0; i < 75; ++i)
            receive[i] = incoming[i+3];
           if(incoming[78] != '#')
            error();
           else
            setWindow(receive);
          digitalWrite(12, !digitalRead(12));
        }
  }
}

void readIntClock(){
  if (Serial.available() > 0) {
        long incoming = Serial.parseInt();
        displayTime(incoming);

        Serial.println(incoming);
  }
}

void raspPi() {
  readIntClock();
  //readStdString();
  
}

void setAll() {
  setModule(y, 1);
  setModule(y, 2);
  setModule(y, 3);
}

void animation() {

  setModule(an1, 1);
  setModule(an2, 1);
  setModule(an3, 1);
  setModule(an4, 1);
  setModule(an5, 1);

  setModule(an1, 2);
  setModule(an2, 2);
  setModule(an3, 2);
  setModule(an4, 2);
  setModule(an5, 2);

  setModule(an1, 3);
  setModule(an2, 3);
  setModule(an3, 3);
  setModule(an4, 3);
  setModule(an5, 3);

  setModule(an5, 3);
  setModule(an4, 3);
  setModule(an3, 3);
  setModule(an2, 3);
  setModule(an1, 3);

  setModule(an5, 2);
  setModule(an4, 2);
  setModule(an3, 2);
  setModule(an2, 2);
  setModule(an1, 2);

  setModule(an5, 1);
  setModule(an4, 1);
  setModule(an3, 1);
  setModule(an2, 1);
  setModule(an1, 1);

  setModule(x, 1);
  setModule(x, 2);
  setModule(x, 3);
}


void setup ()
{
  pinMode (latchPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
  Serial.begin(9600);
  //Serial.println("Current:\n");
  for (int i = 0; i < 75; ++i) {
    current[i] = 1;
    //if (i % 5 == 0 || i % 25 == 0)
      //Serial.println("");
    //Serial.print(current[i]);
    //Serial.print(' ');

  }

  id = 1;
  clearModules();
  //setWindow(current);
}

void loop ()
{

  //raspPi();
    arduinoClock();
    //clearModules();
    //setAll();
  //  helloWorld();

  //S
  //  while (1);
}

