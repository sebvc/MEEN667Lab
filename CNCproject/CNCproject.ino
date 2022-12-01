/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * MEEN 433/667 Project
 */

#include "ComponentDrivers.h"

#define XIN1 23 // triger IN 1->4->3->2 for black straight cable
#define XIN2 25
#define XIN3 27
#define XIN4 29

#define YIN1 31 // triger IN 1->3->2->4 for colored crossed cable
#define YIN2 33
#define YIN3 35
#define YIN4 37

#define EIN1 39 // triger IN 1->4->3->2 for black straight cable
#define EIN2 41
#define EIN3 43
#define EIN4 45

#define LIM1NO 53
#define LIM2NO 52

//
#define pi 3.14159265359                                 // Define pi cause C is C mhm
const int stepsPerRevolution = 200;                      // Confirmed from Amazon description 1.8deg step angle
const float stepsPerRad = stepsPerRevolution / (2 * pi); // Conversion from radians to steps
const float mm_per_cameraUnit = 2; // calibrate this

float X_coordinate;
float X_diameter=11.89;//mm
float X_radius = X_diameter / 2;

float Y_coordinate;
float Y_diameter=11.89;//mm
float Y_radius = Y_diameter / 2;

enum DIR1
{
  CW = LOW,
  CCW = HIGH
};
enum DIR2
{
  left = LOW,
  right = HIGH
};
enum DIR3
{
  up = LOW,
  down = HIGH
};
enum NO
{
  open = HIGH,
  closed = LOW
};

dynStepper Xstepper, Ystepper, Estepper;
int target = 0, motor;
uint16_t currTime, lastTime, loopTime, loopTimex, loopTimey;
int delayms = 1;
unsigned int slowFactorX = 1, slowFactorY = 1;
String msg; 
int raspberyInstruct=5;
void setup()
{
  // put your setup code here, to run once:

  // Xstepper = dynStepper(XIN1, XIN4, XIN3, XIN2);// triger IN 1->4->3->2 for black straight cable
  Xstepper = dynStepper(XIN1, XIN3, XIN2, XIN4);// triger IN 1->3->2->4 for colored crossed cable
  Ystepper = dynStepper(YIN1, YIN3, YIN2, YIN4);// triger IN 1->3->2->4 for colored crossed cable
  // Estepper = dynStepper(EIN1, EIN3, EIN2, EIN4);

  Serial.begin(9600);
  Xstepper.setZero();
  Ystepper.setZero();
  // Estepper.setZero();
  Xstepper.setTarget(0);
  Ystepper.setTarget(0);
  // Estepper.setTarget(0);

  lastTime = micros();

  pinMode(LIM1NO, INPUT_PULLUP);
  pinMode(LIM2NO, INPUT_PULLUP);
  //  digitalWrite(PIN, LOW);
  // homing('x');
  // homing('y');
  // Serial.println("Enter Target Postion: \n"
  //              "Enter with motor selection prefix\n"
  //              "e.g. x100 or e-50");
}

void loop()
{
 	readSerialPort();
 	if (msg == "zero") {
    raspberyInstruct = 0;
 	}else if(msg=="move"){
    raspberyInstruct = 1;
  }
 	//delay(500);


  // put your main code here, to run repeatedly:
  switch (raspberyInstruct) {
    default:
      //nothing
      break;
    case 0:
      //do homing
      homing('x');
      homing('y');
      sendData("finish");
      raspberyInstruct=5;
      break;
    case 1:
      // set target
      while ( Serial.available() == 0) {} 
      readSerialPort();
      Serial.print((msg.toFloat()));
      Xstepper.setTarget(-1*msg.toFloat());
      while ( Serial.available() == 0) {} 
      readSerialPort();
      Serial.print((msg.toFloat()));
      Ystepper.setTarget(-1*msg.toFloat());
    
      raspberyInstruct=3;
      break;
      case 3:
       //moving
       if ((Xstepper.getError()==0) && (Ystepper.getError()==0)) {
         sendData("finish");
         raspberyInstruct=5;
       }
       break;
    case 5:
      sendData("\nhello\n");
      raspberyInstruct=6;
      break;
    case 6:
      // do nothing
      break;
  }
  //(default movement)
  // target--; // Read user input and hold it in a variable
  // Xstepper.setTarget(target);
  // Ystepper.setTarget(target);
  // Zstepper.setTarget(target);

  currTime = micros();
  loopTime = (currTime - lastTime);

  Xstepper.update(loopTime >> slowFactorX);
  Ystepper.update(loopTime >> slowFactorY);
  // Estepper.update(loopTime);

  lastTime = currTime;
  delay(delayms);
}

void homing(char motor)
{
  switch (motor)
  {
  case 'X':
  case 'x':
  case '1':
    // set X
    while (digitalRead(LIM1NO) == open)
    {
      target++;
      Xstepper.setTarget(target);
      currTime = micros();
      loopTime = currTime - lastTime;
      Xstepper.update(loopTime);
      lastTime = currTime;
      delay(10);
    }
    Xstepper.setZero();
    delay(1000);
    break;
  case 'Y':
  case 'y':
  case '2':
    // set Y
    while (digitalRead(LIM2NO) == open)
    {
      target++;
      Ystepper.setTarget(target);
      currTime = micros();
      loopTime = currTime - lastTime;
      Ystepper.update(loopTime);
      lastTime = currTime;
      delay(10);
    }
    Ystepper.setZero();
    delay(1000);
    break;
  case 'E':
  case 'e':
  case '3':
    // set extruder
    while (digitalRead(LIM1NO) == open)
    {
      target++;
      Estepper.setTarget(target);
      currTime = micros();
      loopTime = currTime - lastTime;
      Estepper.update(loopTime);
      lastTime = currTime;
      delay(10);
    }
    Estepper.setZero();
    break;
  }
}

void SetMotorTarget() {
  if(Serial.available()==1) {
    motor = Serial.read();
    target = Serial.parseInt(); //Read user input and hold it in a variable
    // Serial.println("Choose target Stepper motor:\n"
    //                "X,x,1 : X-axis\n"
    //                "Y,y,2 : Y-axis\n"
    //                "E,e,3 : Extruder Positon");
    switch (motor) {
    case 'X':
    case 'x':
    case '1':
      //set X
      Xstepper.setTarget(-1*target);
      break;
    case 'Y':
    case 'y':
    case '2':
      //set Y
      Ystepper.setTarget(-1*target);
      break;
    case 'E':
    case 'e':
    case '3':
      //set extruder
      //Estepper.setTarget(-1*target);
      break;
    default:
      Serial.print("value not understood: ");
      Serial.println((char)motor);
      break;
    }
    // target = Serial.parseInt(); //Read user input and hold it in a variable
    // Xstepper.setTarget(target);
    // Ystepper.setTarget(target);
    // Zstepper.setTarget(target);
      Serial.println("\nEnter Target Postion.");
  }
  
}


// Raspberry pi Communication

void readSerialPort() {
 	msg = "";
  //while ( Serial.available() == 0) {} 
 	if (Serial.available()) {
 			delay(10);
 			while (Serial.available() > 0) {
 					msg += (char)Serial.read();
 			}
 			Serial.flush();
 	}
}
void sendData(String str) {
 	//send msg
 	Serial.print(str);
}