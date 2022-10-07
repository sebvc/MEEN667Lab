/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Switch CLK signal
 */

#define clk_pin 53
void setup() {
  // put your setup code here, to run once:
  pinMode(clk_pin, OUTPUT);    // sets the digital pin 13 as output

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(80);
  digitalWrite(clk_pin,HIGH);
  Serial.println(1);
  delay(80);
  digitalWrite(clk_pin,LOW);
  Serial.println(0);
}
