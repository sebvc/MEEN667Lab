/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * 1. Read the two numbers you typed as ASCII characters.
 * 2. Convert these ASCII characters to integer values.
 * 3. Sum the two integers.
 * 4. Display the sum in the serial monitor
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
