/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Vary Vcc(ext) between 0 V and 8 V and observe the change in the motor speed.
 * Use the Agilent programmable power supply for Vcc(ext).  Never exceed Vcc(ext) = 18 V,
 * the armature voltage rating of this motor.
 */

#include "TimerThree.h"
#include "TimerOne.h"
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

    // Serial.println("b1 & b2");
    // Serial.println(b1);
    // Serial.println(b2);
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
}