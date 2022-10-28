/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write and test a C program so that you can change the duty cycle on the Arduino
 * Serial Monitor. This program takes a number between 0‒255 where 0 = 0% duty cycle
 * and 255 = 100% duty cycle.

 * A sample program is provided below. Connect the oscilloscope probe to the
 * PWM pin you choose and observe the PWM signal while turning the potentiometer.
 * Repeat with various duty cycles. This program uses the analogWrite() function to
 * set the duty cycle on the output pin. 
 */
#define pwm_pin 2
int pot_signal;
int duty_cycle;

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);
}
void loop() {
 Serial.println("Enter a number from 0-255");
 while (Serial.available() == 0) {} // wait for input
 duty_cycle = Serial.readString().toInt();
 analogWrite(pwm_pin, duty_cycle);
 Serial.print((float)duty_cycle/255.0*100.0);
 Serial.println("%");
}
