/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * trigger
 */

  int num1;
#define trigger_pin 53
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);    // sets the digital pin 13 as output
  digitalWrite(trigger_pin,HIGH);

}

void loop() {

  Serial.println("hello, world! ");
  while(Serial.available()==0) {  }
  num1= Serial.read()-'0';
  Serial.print(num1);
  if (num1=1) {
    digitalWrite(trigger_pin,LOW);
    Serial.println("trigger");
    delay(1);
    digitalWrite(trigger_pin,HIGH);
  }
  else
    digitalWrite(trigger_pin,HIGH);

}
