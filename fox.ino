#include "MeMegaPi.h"

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeMegaPiDCMotor motor3(PORT3B);
MeMegaPiDCMotor motor4(PORT4B);

MeLineFollower lineFinder(PORT_8);

uint8_t motorMaxSpeed = 255;
uint8_t motorSpeed = 255;
uint8_t motorCarSpeed = 30;

char inputkey;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  motor3.run(motorSpeed);
  //  わたあめ棒の回転スピードはMaxではなく100程度にしておくと、わたあめの先端が禿げない
  lineTrace(); 
  changeHeight();
}


void lineTrace(){
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: 
      Serial.println("Sensor 1 and 2 are inside of black line"); 
      break;
    case S1_IN_S2_OUT: 
      Serial.println("Sensor 2 is outside of black line"); 
      motor2.run(motorCarSpeed);
        break;
    case S1_OUT_S2_IN: 
      Serial.println("Sensor 1 is outside of black line"); 
      motor2.run(-motorCarSpeed);
        break;
    case S1_OUT_S2_OUT: 
      Serial.println("Sensor 1 and 2 are outside of black line");
      motor2.stop(); 
       break;
    default: 
      break;
  }
}

void changeHeight(){
  inputkey =Serial.read();
  if( inputkey !=-1){
    switch(inputkey){
      case 'd':
        downHeight();
        Serial.println("高さを上げる");
        break;
      case 'u':
        upHeight(); 
        Serial.println("高さを下げる");
        break;
    }
  }
}

void downHeight(){
  motor4.run(30);
  delay(200);
  motor4.stop();
}

void upHeight(){
  motor4.run(-100);
  delay(200);
  motor4.stop();
}


