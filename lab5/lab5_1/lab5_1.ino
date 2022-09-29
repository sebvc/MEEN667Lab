/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that displays the encoder count value and rotation direction.
 * Because it is a 16-ppr (or 6-ppr) quadrature encoder, the number of counts per revolution
 * is 64 (or 24). You need to give at least 5-ms delay before reading again to accommodate
 * the contact bounce. Use a flat screw driver to rotate the encoder shaft to test your code.
 */

#define pin_a 2
#define pin_b 3

void setup()
{
    Serial.begin(9600);
    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
}

void loop()
{
    if (digitalRead(pin_a))
    {
        Serial.println("A");
    }
    if (digitalRead(pin_b))
    {
        Serial.println("B");
    }
}
