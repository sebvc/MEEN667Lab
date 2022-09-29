/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that can handle both types of interrupts you learned today 
 * (external using the pushbutton switch and internal timer using the Timer3 library). 
 *    • In the void loop() function, do nothing. 
 *    • When the timer interrupt is called, print “T”. 
 *    • When the the external interrupt is called, print “E”. 
 */ 

 // This is how we include non-standard libraries like Timer3 

#include "TimerThree.h" 
#define led_pinT 5 
#define led_pinSW 3 
volatile unsigned long i; 
  
void setup() { 
Serial.begin(9600); 
pinMode(3,OUTPUT); 
Timer3.initialize(5000000); // time before overflow in us 
Timer3.attachInterrupt(isrTimer); // isr triggered at overflow 
attachInterrupt(0, isrSwitch, FALLING); 

} 
 
void loop(){ } 
 
void isrSwitch(){ 
  Serial.println("E");
    digitalWrite(led_pinSW,HIGH); 
  for(i=0;i<500000;i++); // Give some delay 
  //delayMicroseconds(10000);  // another way to add delay 
  digitalWrite(led_pinSW,LOW); 
}

void isrTimer (){
  Serial.println("T");
    digitalWrite(led_pinT,HIGH); 
  for(i=0;i<500000;i++); // Give some delay 
  //delayMicroseconds(10000);  // another way to add delay 
  digitalWrite(led_pinT,LOW); 
}
