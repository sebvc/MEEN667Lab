/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * In the program above, the external interrupt is set to RISING which occurs with a 
 * LOW-to-HIGH transition.  In the ISR, the LED pin is turned on and then turned off after 
 * a short delay.  Run the program and fill out the following table. 
 * 
 * a.  attachInterrupt(0, isr, RISING); 
 *                        |___________________Switch status________________|
 *                        | Not | pressed | Press | Keep pressed | Release |
 * -----------------------|-----|---------|-------|--------------|---------|
 * |Input to interrupt pin|     |         |       |              |         |
 * |(L, H, L to H, H to L)|     |         |       |              |         | 
 * |----------------------|-----|---------|-------|--------------|---------|
 * |Interrupt? (Yes, No)  |     |         |       |              |         |
 * |----------------------|-----|---------|-------|--------------|---------|
 * 
 * Modify your program so that the external interrupt edge selection is HIGH-to-LOW 
 * (FALLING instead of RISING) and fill out the following table. 
 * 
 * b.  attachInterrupt(0, isr, FALLING); 
 *                        |___________________Switch status________________|
 *                        | Not | pressed | Press | Keep pressed | Release |
 * |----------------------|-----|---------|-------|--------------|---------|
 * |Input to interrupt pin|     |         |       |              |         |
 * |(L, H, L to H, H to L)|     |         |       |              |         | 
 * |----------------------|-----|---------|-------|--------------|---------|
 * |Interrupt? (Yes, No)  |     |         |       |              |         |
 * |----------------------|-----|---------|-------|--------------|---------|
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}
// Declarations
int num1=0, num2=0;

void loop() {
// put your main code here, to run repeatedly:
//  Serial.println("Mechatronics");

//Send data only when you receive data.
//Wait until there is something to read:
  while (Serial.available() == 0) {}
  num1= Serial.read()-'0';
  Serial.print("num1: ");
  Serial.println(num1);
  while (Serial.available() == 0) {}
  num2= Serial.read()-'0';
  Serial.print("num2: ");
  Serial.println(num2);
  
// Say what you got:
  Serial.print("sum= ");
  Serial.println(num1+num2); 
  
  }
