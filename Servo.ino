#include "TimerOne.h"



const int Enable = 6;
const int InA = 7;
const int InB = 11;
unsigned long starttime;
unsigned long endtime;
byte incdata;
void setup() {
  pinMode(10,OUTPUT);
  Timer1.initialize();

  pinMode(Enable, OUTPUT);
  pinMode(InA, OUTPUT);
  Serial.begin(9600);
  
  // put your setup code here, to run once:
 digitalWrite(Enable, HIGH);
 
}

void loop() {


 if (Serial.available()>0)
 {
  incdata = Serial.read();

  if (incdata == 'd')
  {
     digitalWrite(InA, LOW);
analogWrite(InB, 1);
delay(1500*8);
analogWrite(InB,0);
    }
    
   if (incdata == 'a')
  {
    
    
    digitalWrite(InA, LOW);
analogWrite(InB, 254);
delay(1500*8);

}
    }
  if (incdata == 's')  
 {
  digitalWrite(InA,HIGH); 
  }

  
  } 

}
