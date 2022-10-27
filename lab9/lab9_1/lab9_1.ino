/* A sample program is provided below. Connect the oscilloscope probe to the
 * PWM pin you choose and observe the PWM signal while turning the potentiometer.
 * Repeat with various duty cycles. This program uses the analogWrite() function to
 * set the duty cycle on the output pin. 
 */

#define pwm_pin 2
int pot_signal;
float duty_cycle;

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);
}
void loop() {
 pot_signal = analogRead(A0);
 duty_cycle = pot_signal/1023.0;
 analogWrite(pwm_pin, duty_cycle*255);
 Serial.print(duty_cycle*100);
 Serial.println("%");
}
