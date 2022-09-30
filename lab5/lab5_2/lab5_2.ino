/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that displays the encoder count value and direction using an
 * interrupt service routine and test it.  Note that you may have false interrupts due to the
 * contact bounce.  Use two interrupts triggered by CHANGE on pins 2 and 3. Use the
 * following code to get started:
 */

#define pin_a 2
#define pin_b 3
int count = 0;
bool dir = 0;
int state = 0;
int prevstate = 0;

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
    switch (dir)
    {
    case 1:
        Serial.print("Clockwise   ");
        break;
    case 0:
        Serial.print("Counter Clockwise   ");
        break;
    }
        Serial.println(count);
    // display the encoder count and direction
}
void doEncoder()
{
    bool stateA = digitalRead(pin_a);
    bool stateB = digitalRead(pin_b);
    if (stateA > stateB){
        state = 0;
    }
    if (stateA < stateB){
        state = 1;
    }
    if (!stateA && !stateB){
        state = 2;
    }
    if (stateA && stateB){
        state = 3;
    }
    
    switch (state)
    {
    case 0:
        if (prevstate == 2){
            dir = 0;
            count--;
        }
        if (prevstate == 3){
            dir = 1;
            count++;
        }    
        break;
    case 1:
        if (prevstate == 2){
            dir = 1;
            count++;
        }
        if (prevstate == 3){
            dir = 0;
            count--;
        }    
        break;

    }
    prevstate = state;
    // your ISR to count and determine direction
}