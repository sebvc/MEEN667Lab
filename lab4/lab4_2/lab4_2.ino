/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Tune the end count in the for loop using the oscilloscope so that the LED can be lit for 500 ms.  
 */
// This is how we include non-standard libraries like Timer3 
#include "TimerThree.h" 
#define led_pin 3 
volatile unsigned long i; 
 
void setup() { 
  Serial.begin(9600); 
  pinMode(3,OUTPUT); 
  Timer3.initialize(5000000); // time before overflow in us 
  Timer3.attachInterrupt(isr); // isr triggered at overflow 
} 
 
void loop(){ 
  Serial.println("..."); 
  delay(100); 
} 
 
void isr(){ 
  Serial.println("Timer 3 Interrupt"); 
  digitalWrite(led_pin,HIGH); 
  for(i=0;i<500000;i++); // Give some delay 
  //delayMicroseconds(10000);  // another way to add delay 
  digitalWrite(led_pin,LOW); 
} 