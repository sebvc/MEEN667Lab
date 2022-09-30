/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that displays the encoder count value and rotation direction.
 * Because it is a 16-ppr (or 6-ppr) quadrature encoder, the number of counts per revolution
 * is 64 (or 24). You need to give at least 5-ms delay before reading again to accommodate
 * the contact bounce. Use a flat screw driver to rotate the encoder shaft to test your code.
 */

#define pin_a 2
#define pin_b 3
char lastState, newState; // A or B
bool stateA, stateB;
unsigned int count = 0;
bool dir = 0;        // direction of robot: 1:true:CW:A-Leading  & 0:false:CCW:B-leading
bool stopped = true; // if robot moving last read alt to moving=false
char arr[4];
int index = 0;
/* Order
 * 1/CW : A -> D/neither -> B -> C/both |  
 *      ^-------------------------|  
 * B is leading
 * 
 * 0/CCW :A -> C/both -> B -> D?neither |  
 *      ^-------------------------|  
 * A is leading 
 * 
 */




void setup()
{
    Serial.begin(9600);
    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);

    lastState = Update(stateA,stateB);

}

void loop()
{
    delay(10);
    stateA = digitalRead(pin_a);
    stateB = digitalRead(pin_b);
    newState = Update(stateA,stateB);
    
    switch (lastState)
    {
    case 'A':
        if (newState=='A')
            stopped=true;
        else if (newState=='D') // neither
        {
            stopped=false;
            dir = 1; // CW
            count++;
        }
        else if (newState=='C') // both
        {
            stopped=false;
            dir = 0; // CCW
            count--;
        }
        break;
    
    case 'B':
        if (newState=='B')
            stopped=true;
        else if (newState=='C') // both
        {
            stopped=false;
            dir = 1; // CW
            count++;
        }
        else if (newState=='D') // neither
        {
            stopped=false;
            dir = 0; // CCW
            count--;

        }
        break;
    
    case 'C': // both
        if (newState=='C')// both
            stopped=true;
        else if (newState=='A') 
        {
            stopped=false;
            dir = 1; // CW
            count++;
        }
        else if (newState=='B') 
        {
            stopped=false;
            dir = 0; // CCW
            count--;
        }
        break;
    
    case 'D': // neither
        if (newState=='D')// neither
            stopped=true;
        else if (newState=='B') 
        {
            stopped=false;
            dir = 1; // CW
            count++;
        }
        else if (newState=='A') 
        {
            stopped=false;
            dir = 0; // CCW
            count--;
        }
        break;
    
    default:
        break;
    }
    //mod count to encoder revolution scale
    count %= 64;

    Serial.print("count: ");
    Serial.print(count);
    Serial.print('\t');
    Serial.print( dir? "CW\t" : "CCW\t");
    Serial.println(stopped? "Stopped" : "Moving");

    lastState = newState;

    //         if (dir == 0){

    //         count += 1
    //     }
    //     Serial.println("A");
    //     dir = 1
    // }
    // else if (digitalRead(pin_b))
    // {
    //      if (dir == 1){

    //         count += 1
    //     }
    //     Serial.println("B");
    //     dir = 0
    // }
    // delay(5);
}


char Update(bool stateA, bool stateB)
{
    char last;
    if (stateA && stateB)
    {
        last='C';//both
    }
    else if ((!stateA) && (!stateB))
    {
        last = 'D';//neither
    }
    else
    {

        if (stateA)
        {
            last = 'A';
        }
        if (stateB)
        {
            last ='B';
        }
    }
    //Serial.println(last);
    return last;
}
