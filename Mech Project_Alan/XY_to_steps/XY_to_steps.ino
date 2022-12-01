/* 
This code is for Alan to make a function that converts inputed XY coordinates to a number of steps.
These numbers of steps are how many steps the stepper motor must turn to reach the position.
*/

#include <Stepper.h>
#define STEPS 100 // Is this even needed?

#define output_pin 2
#define input_pin A0

const int stepsPerRevolution = 200; // Confirmed from Amazon description 1.8deg step angle
#define pi 3.14159265359 // Define pi cause C is C mhm
const float stepsPerRad = stepsPerRevolution / (2*pi); // Conversion from radians to steps

float X_coordinate;
float X_diameter;
float X_radius = X_diameter / 2;

float Y_coordinate;
float Y_diameter;
float Y_radius = Y_diameter / 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input_pin, INPUT);
  pinMode(output_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Alan can code C");
  X_coordinate = 5;

}

int Coord2Step(float Coordinate, float Radius) {
  // Converts XY float to number of steps as an integer
  float Radians = Coordinate/Radius;
  return (int)(Radians * stepsPerRad); // Not sure if you can turn float*float into an integer
}