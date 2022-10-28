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
 Serial.print((float)duty_cycle*100.0/255.0);
 Serial.println("%");
}
