/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Measure the analog voltage between the A/D channel 0 and GND (VSS) using a
 * multimeter. Run the program above, and record the voltage and A/D converter value.
 * Repeat the procedure with at least 5 different analog voltage inputs by turning the screw
 * of the potentiometer. Plot the result of A/D converter values with respect to the analog
 * voltage. What is the maximum/minimum converter values? How would you convert the
 * values to a voltage in the Arduino code
 */

// Initialize an integer to store the analog pin number
// In Arduino, A0 is an alias for the PIN_A0 number
int pot_pin = A0;
void setup()
{
    Serial.begin(9600);
    // Set the potentiometer pin as an input
    pinMode(pot_pin, INPUT);
}
void loop()
{
    // Read and display the analog value of the pot pin
    Serial.println(0.004934434 * (float)analogRead(pot_pin));
}

/*
 * Multimeter   =   Arduino Integer
 * 5.051 VDC    =   1023
 * 3.449 VDC    =   700
 * 3.015 VDC    =   611
 * 2.618 VDC    =   530
 * 2.157 VDC    =   436
 * 0.001 mVDC   =   0
 *
 * ADC to Voltage: V = 0.004934434 * A
 */
