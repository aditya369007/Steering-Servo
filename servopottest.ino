/*
Name:    Servo_VS.ino
Created: 10/11/2017 6:10:39 PM
Author:  ADITYA
*/
#define mid  580									//found by physically setting the steering at mid
#define left_comp	695								//found by physically setting the steering at left max
#define right_comp 463								//found by physically setting the steering at right max

const int Enable = 6;								//for the servo to start working
const int InA = 7;									//inhibit input has to be disabled for the motor to spin
const int InB = 11;									// the PWM input. 1 for direction 1 254 for direction 2
const int fdbk = A0;								//output of the encoder goes here
double currentpos = 0;								//variable for current position
double desired = mid;								//setting the desired position as mid
double pos_er = 0;									//position error

byte incdata;

void setup() {

	Serial.begin(9600);								//start serial comms
	pinMode(Enable, OUTPUT);						//setting enable, InA, InB in output mode
	pinMode(InA, OUTPUT);
	pinMode(InB, OUTPUT);
}

void loop() {
	currentpos = analogRead(fdbk);					//current postion will be the direct input of the analog pin
	pos_er = desired - currentpos;					//self explanatory
	Serial.print("CURRENT POSITION = ");			//Printing the needed variables for observation
	Serial.println(currentpos);						
	Serial.print("DESIRED POSITION = ");
	Serial.println(desired);
	Serial.print("ERROR TO BE COVERED = ");
	Serial.println(pos_er);
	delay(500);


	incdata = Serial.read();						//positional commands will be sent via serial terminal

	if (incdata == 'q')
	{
		desired = left_comp;
	}
	else if (incdata == 'z' && (currentpos < left_comp + 1))
	{
		desired = currentpos + 10;
	}
	else if (incdata == 'd' && (currentpos > right_comp - 1))
	{
		desired = currentpos - 10;
	}
	else if (incdata == 'e')
	{
		desired = right_comp;
	}
	else if (incdata == 'w')
	{
		desired = mid;
	}
	
	while (pos_er != 0)
	{
		digitalWrite(Enable, HIGH);
		digitalWrite(InA, LOW);
		currentpos = analogRead(A0);
		pos_er = desired - currentpos;					//self explanatory
		Serial.print("CURRENT POSITION = ");			//Printing the needed variables for observation
		Serial.println(currentpos);
		Serial.print("DESIRED POSITION = ");
		Serial.println(desired);
		Serial.print("ERROR TO BE COVERED = ");
		Serial.println(pos_er);
		delay(500);


		if (currentpos > right_comp)
		{
			digitalWrite(InA, LOW);
			analogWrite(InB, 254);
		}
		else if (currentpos < left_comp)
		{
			digitalWrite(InA, LOW);
			analogWrite(InB, 1);
		}


		if ((currentpos <= right_comp) && (currentpos >= left_comp))
		{
			if ((desired <= right_comp) && (desired >= left_comp))
			{
				if (pos_er >= 1)
				{
					digitalWrite(InA, LOW);
					analogWrite(InB, 254);
					
				}
				if (pos_er <= -1)
				{
					digitalWrite(InA, LOW);
					analogWrite(InB, 1);

				}
				else
				{

					digitalWrite(InA, HIGH);
					analogWrite(InB, 127);

				}
				
				
			}
		}







	}




}
