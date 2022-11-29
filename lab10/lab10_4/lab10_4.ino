/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write and implement a C program to close the speed control loop of the DC motor 
 * system.  Use the sample program given in Section 2 as a skeleton.  Inside the interrupt-
 * service routine (i.e., the C function, Timer3_Interrupt()) in this sample code, add 
 * your own codes in the following sequence:  
 *  1. Resolve the rotor speed with the encoder value. 
 *  2. Implement the discrete-time control law given in Eq. (9). 
 *  3. Generate PWM output. 
 *  4. Save data.  
 * In addition, the user should be able to set the reference speed input.  This information 
 * must be accepted in the loop() function.  Test your program and ensure the motor 
 * speed follows the reference speed input.   
 */
#include "TimerThree.h"
#include "TimerOne.h"

#define pwm_pin 2


long y;
long r=60; //rps
long e,u,u1=0,e1=0; 
long cnt = 0;
int b1=0, b2=0;
int encoder_pin = 5;
long v_current;
double conversion_factor = 0.00528;

void setup()
{
    Serial.begin(9600);
    Timer1.initialize(200000); // interrupt triggered every 200 ms
    Timer3.initialize(1000);   // PWM carrier freq 1 kHz
    Timer1.attachInterrupt(Timer1_Interrupt);
    pinMode(encoder_pin, INPUT);
}

void loop()
{
    if (digitalRead(encoder_pin))
        b1 = 1;
    else
        b1 = 0;
    if (b1 != b2)
        cnt++;
    b2 = b1;
}

void Timer1_Interrupt()
{
    v_current = conversion_factor * cnt;
    Serial.print("Speed of DC motor (rps) is: ");
    Serial.println(v_current);
    cnt = 0;
    Discrete_control();

}

void Discrete_control() 
{
  e = r-v_current;//v_current; // error = target - current_speed
  u = u1 + 2*e - e1; // u(k) = u(k-1) + 2e(k) - e(k-1)
  Timer3.pwm(pwm_pin, u); // pwm library
  u1=u;
  e1=e;
}
