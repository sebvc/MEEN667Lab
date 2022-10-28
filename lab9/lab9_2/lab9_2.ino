/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Calculate the cutoff frequency ( 1/(2*pi*R*C) Hz) of the RC low-pass filter. Check the
 * filtered PWM signal with various duty cycles. Using two channels of the oscilloscope
 * compare the filtered signal with the original PWM signal. Note that the cutoff frequency
 * of the low-pass filter is fixed.
 */

#define pwm_pin 2
int pot_signal;
float duty_cycle;
float R = 1000.0;
float C = 1.0 / 1000000.0;

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);
 pinMode(pwm_pin,OUTPUT);

}
void loop() {
 Serial.println("Enter a number from 0-255");
 while (Serial.available() == 0) {} // wait for input
 duty_cycle = Serial.readString().toInt();
 analogWrite(pwm_pin, duty_cycle);
 Serial.print(duty_cycle);
 Serial.print(" => ");
 Serial.print((float)duty_cycle*100.0/255.0);
 Serial.println("%");

 float cutoff = 1.0/(2.0*3.1415*R*C);
 Serial.print("The cut-off frequency is: ");
 Serial.println(cutoff);
}
