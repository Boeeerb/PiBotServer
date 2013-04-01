#include <Servo.h>

Servo servo1;
Servo servo2;

int ser1 = 0;
int ser2 = 0;
int motA = 0;
int motB = 0;

int trig1 = 6;
int trig2 = 2;


int motA1 = 7;
int motA2 = 12;
int motB1 = 8;
int motB2 = 9;

int motAE = 10;
int motBE = 11;

void setup()
{
  Serial.begin(9600);

  servo1.attach(2);
  servo2.attach(3);


  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);


  pinMode(motAE, OUTPUT); // Motor Enable pins
  pinMode(motBE, OUTPUT);

  pinMode(motA1, OUTPUT); // Motor poles config
  pinMode(motA2, OUTPUT);
  pinMode(motB1, OUTPUT);
  pinMode(motB2, OUTPUT);
}

void loop() {

  while (Serial.available() > 0) {

    int value0 = Serial.parseInt();
    int value1 = Serial.parseInt();
    int value2 = Serial.parseInt();
    int value3 = Serial.parseInt();
    int value4 = Serial.parseInt();


    if ( Serial.read() == '\n' ) {

      int axisy = value0;
      int axisx = value1;

if ( value2 == 1 ) {
  
  digitalWrite(trig1,HIGH);
} else {
  digitalWrite(trig1,LOW);
}

      if ( value3 == 1 ) {
        //Move Servos

        ser1 = map(axisy, 0, 265, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
        servo1.write(ser1);                  // sets the servo position according to the scaled value 
        ser2 = map(axisx, 0, 265, 45, 135);     // scale it to use it with the servo (value between 0 and 180) 
        servo2.write(ser2);                  // sets the servo position according to the scaled value 




      } 
      else {





        if ( axisy > 140 ) {
          // go forward
          motA = map(axisy, 140, 265, 50, 265);
          motB = map(axisy, 140, 265, 50, 265);
          if ( axisx < 100 ) {
            // go left
            int motBvalue = map(axisx, 0, 100, 50, 265);
            motB = motB - motBvalue;
          } 
          else if ( axisx > 140 ) {
            // go right
            int motAvalue = map(axisx, 140, 265, 265, 50);
            motA = motA - motAvalue;
          } 
          else {
            // forward both (DO NOTHING as value is already set)
          }
          motorfwd(motB,motA);
        } 
        else if (axisy < 100 ) {
          // go forward
          motA = map(axisy, 0, 100, 265, 50);
          motB = map(axisy, 0, 100, 265, 50);
          if ( axisx < 100 ) {
            // go left
            int motAvalue = map(axisx, 0, 100, 265, 50);
            motA = motA - motAvalue;
          } 
          else if ( axisx > 140 ) {
            // go right
            int motBvalue = map(axisx, 140, 265, 50, 265);
            motB = motB - motBvalue;
          } 
          else {
            // forward both (DO NOTHING as value is already set)
          }
          motorbwd(motB,motA);
        } 
        else {
          if ( axisx < 100 ) {
            // rotate on spot left
            motA = map(axisx, 0, 100, 265, 50);
            motorlef(motA, motA);
          } 
          else if ( axisx > 140 ) {
            // rotate on spot right
            motA = map(axisx, 140, 265, 50, 265);
            motorrig(motA, motA);
          } 
          else {
            motorstop(motA,motB);
          }
        }
      }
    }
  }
}


void motorfwd(int motAspd, int motBspd) {

  digitalWrite(motA1, HIGH);
  digitalWrite(motA2, LOW);
  analogWrite(motAE, motAspd);

  analogWrite(motBE, motBspd);
  digitalWrite(motB1, LOW);
  digitalWrite(motB2, HIGH);
}

void motorbwd(int motAspd, int motBspd) {

  analogWrite(motAE, motAspd);
  digitalWrite(motA1, LOW);
  digitalWrite(motA2, HIGH);

  analogWrite(motBE, motBspd);
  digitalWrite(motB1, HIGH);
  digitalWrite(motB2, LOW);
} 

void motorrig(int motAspd, int motBspd) {

  analogWrite(motAE, motAspd);
  digitalWrite(motA1, LOW);
  digitalWrite(motA2, HIGH);

  analogWrite(motBE, motBspd);
  digitalWrite(motB1, LOW);
  digitalWrite(motB2, HIGH);
}

void motorlef(int motAspd, int motBspd) {

  analogWrite(motAE, motAspd);
  digitalWrite(motA1, HIGH);
  digitalWrite(motA2, LOW);

  analogWrite(motBE, motBspd);
  digitalWrite(motB1, HIGH);
  digitalWrite(motB2, LOW);
} 

void motorstop(int motAspd, int motBspd) {
  analogWrite(motAE, 0);
  digitalWrite(motA1, LOW);
  digitalWrite(motA2, LOW);
  analogWrite(motBE, 0);
  digitalWrite(motB1, LOW);
  digitalWrite(motB2, LOW);
}













