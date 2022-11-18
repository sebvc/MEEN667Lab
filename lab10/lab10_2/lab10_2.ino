/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Repeat Section 3 of Lab. 9 with this new DC motor.  After confirming the PWM’s 
 * functionality, combine the PWM code you developed in Section 3 of Lab. 9 with the 
 * sample encoder code given in Section 2.  Turn the potentiometer knob (instead of varying 
 * Vcc(ext)) to change and display the motor speed.
 */
#include "TimerThree.h"
#include "TimerOne.h"

#define pwm_pin 2
#define pot_pin A0
int pot_signal;
int duty_cycle;

// 10_1
long cnt = 0;
int b1=0, b2=0;
int encoder_pin = 5;
long v_current;
double conversion_factor = 0.00528;

void setup() 
{
    Serial.begin(9600);
    pinMode(pot_pin,INPUT);

    //10_1
    Timer1.initialize(200000); // interrupt triggered every 200 ms
    Timer3.initialize(1000);   // PWM carrier freq 1 kHz
    Timer1.attachInterrupt(Timer1_Interrupt);
    pinMode(encoder_pin, INPUT);
}
void loop() 
{
    // Serial.println("Enter a number from 0-255");
    // while (Serial.available() == 0) {} // wait for input
    
    //analogWrite(pwm_pin, duty_cycle);

    // 10_1
    if (digitalRead(encoder_pin))
        b1 = 1;
    else
        b1 = 0;

    // Serial.println("b1 & b2");
    // Serial.println(b1);
    // Serial.println(b2);
    if (b1 != b2)
        cnt++;
    b2 = b1;
}

void Timer1_Interrupt()
{
    duty_cycle = analogRead(pot_signal);
    v_current = conversion_factor * cnt;
    Serial.print("Speed of DC motor (rps) is: ");
    Serial.println(v_current);
    cnt = 0;
    Timer3.pwm(pwm_pin, duty_cycle); // pwm library
    // Serial.print(((double)duty_cycle)/(10.24));
    // Serial.println("%");
}