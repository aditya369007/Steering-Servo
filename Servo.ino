/*
 Name:    Servo_VS.ino
 Created: 10/11/2017 6:10:39 PM
 Author:  ADITYA
*/
const int Enable = 6;
const int InA = 7;
const int InB = 11;
const int time = 12000;
byte incdata;
unsigned long previousMillis;
unsigned long currenttime;
// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(Enable, OUTPUT);
  pinMode(InA, OUTPUT);
  Serial.begin(9600);

  
  digitalWrite(Enable, HIGH);


}

// the loop function runs over and over again until power down or reset
void loop() {


  if (Serial.available()>0)
  {
    incdata = Serial.read();

    if (incdata == 'd')
    {
      previousMillis = millis();
      digitalWrite(InA, LOW);
      analogWrite(InB, 1);
      while (time!=currenttime-previousMillis)
      {
        currenttime = millis();
        
      }
      analogWrite(InB, 0);
    }

    if (incdata == 'a')
    {


      previousMillis = millis();
      digitalWrite(InA, LOW);
      analogWrite(InB, 254);
      while (time != currenttime - previousMillis)
      {
        currenttime = millis();
        }
      analogWrite(InB, 0);

    }
    if (incdata == 's')
    {
      digitalWrite(InA, HIGH);
    }
  }
  



  
}

