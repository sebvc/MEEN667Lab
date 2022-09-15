/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Build a circuit of 3 LEDs and write your own program to turn on the LEDs one at
 * a time, from left to right, with time delay of 500 ms. Modify the program you used for
 * digital output.
 */

// Initialize an integer to store the digital pin number
int led_out1 = 7;
int led_out2 = 6;
int led_out3 = 5;

void setup() {
    Serial.begin(9600);
    // Set the switch pin to digital input mode
    pinMode(led_out1,OUTPUT);
    pinMode(led_out2,OUTPUT);
    pinMode(led_out3,OUTPUT);
}

void loop() {
// Write a digital value to the led pin
// When set to HIGH, the digital pin will be at 5V
digitalWrite(led_out3,LOW);
digitalWrite(led_out1,HIGH);
// Delay for 500 milliseconds
delay(500);
// When set to LOw, the digital pin will be at ground
digitalWrite(led_out1,LOW);
digitalWrite(led_out2,HIGH);
delay(500);
digitalWrite(led_out2,LOW);
digitalWrite(led_out3,HIGH);
delay(500);


}

///////////////
