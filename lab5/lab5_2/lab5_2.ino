/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that displays the encoder count value and direction using an
 * interrupt service routine and test it.  Note that you may have false interrupts due to the
 * contact bounce.  Use two interrupts triggered by CHANGE on pins 2 and 3. Use the
 * following code to get started:
 */

#define pin_a 2
#define pin_b 3
void setup()
{
    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    attachInterrupt(0, doEncoder, CHANGE);
    // encoder pin on interrupt0-pin 2
    attachInterrupt(1, doEncoder, CHANGE);
    // encoder pin on interrupt1-pin 3
    Serial.begin(9600);
    Serial.println("start");
}

void loop()
{
    // display the encoder count and direction
}
void doEncoder()
{
    // your ISR to count and determine direction
}