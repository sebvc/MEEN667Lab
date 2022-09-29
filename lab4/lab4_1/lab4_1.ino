/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * In the program above, the external interrupt is set to RISING which occurs with a 
 * LOW-to-HIGH transition.  In the ISR, the LED pin is turned on and then turned off after 
 * a short delay.  Run the program and fill out the following table. 
 * 
 * a.  attachInterrupt(0, isr, RISING); 
 *                        |___________________Switch status_______________|
 *                        | Not pressed |  Press | Keep pressed | Release |
 * -----------------------|-------------|--------|--------------|---------|
 * |Input to interrupt pin|      H      | H to L |      L       | L to H  | // Noted that our button is normally closed
 * |----------------------|-------------|--------|--------------|---------|
 * |Interrupt? (Yes, No)  |     No      |   No   |     No       |   Yes   |
 * |----------------------|-------------|--------|--------------|---------|
 * 
 * Modify your program so that the external interrupt edge selection is HIGH-to-LOW 
 * (FALLING instead of RISING) and fill out the following table. 
 * 
 * b.  attachInterrupt(0, isr, FALLING); 
 *                        |___________________Switch status_______________|
 *                        | Not pressed |  Press | Keep pressed | Release |
 * |----------------------|-------------|--------|--------------|---------|
 * |Input to interrupt pin|      H      | H to L |      L       | L to H  | // Noted that our button is normally closed
 * |----------------------|-------------|--------|--------------|---------|
 * |Interrupt? (Yes, No)  |     No      |   Yes  |     No       |   No    |
 * |----------------------|-------------|--------|--------------|---------|
 */

#define led_pin 3 
volatile unsigned long i; 

void setup() { 
  Serial.begin(9600); 
  pinMode(led_pin, OUTPUT); 
  // Create an interrupt service on interrupt 0 
  attachInterrupt(0, isr, FALLING); 
} 
 
void loop() { 
  Serial.println("..."); 
  delay(100); 
} 
 
void isr(){ 
  Serial.println("External Interrupt"); 
  digitalWrite(led_pin,HIGH); 
  for(i=0;i<500000;i++); // Give some delay 
  //delayMicroseconds(10000);  // another way to add delay 
  digitalWrite(led_pin,LOW); 
} 
