#define pwm_pin 2
int pot_signal;
float duty_cycle;

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);
 pinMode(pwm_pin,OUTPUT);
}
void loop() {
 pot_signal = analogRead(A0);
 duty_cycle = pot_signal/1023.0;
 analogWrite(pwm_pin, duty_cycle*255);
 Serial.print(duty_cycle*100);
 Serial.println("%");
}
