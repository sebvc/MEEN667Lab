/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Connect VDD (pin 8) to 5 V and GND (pin 4) to GND on Arduino for power.  For
 * control/data communication, connect DQ, CLK, and RST to three following digital pins
 * on the Arduino Mega.
 *  _____________ _______
 * |   DS1620    |  Mega |
 * | DQ (pin 1)  |   2   |
 * | CLK (pin 2) |   3   |
 * | RST (pin 3) |   4   |
 * |_____________|_______|
 *
 * Run the following sample program with your own functions of GetByte() and
 * PutByte().  Refer to the DS1620 datasheet. Notice that the data sheet refers to pin DQ
 * as both an input and an output. This means that you will need to switch it between types
 * using the pinMode() function. In order for this to work properly do not define the DQ pin
 * as an input or output in Setup(). Instead define it as an input or output right before you
 * use the pin in GetByte() and PutByte();
 */

#define DQ 2
#define CLK 3 // 750ms CLK (min)
#define RST 4
#define halfFreq 400
unsigned char Temp;
unsigned char sign_bit;

void setup()
{
  Serial.begin(9600);
  pinMode(CLK, OUTPUT);
  pinMode(RST, OUTPUT);
}

void loop()
{

  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  PutByte(0xEE);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);
  PutByte(0xAA);
  Temp = GetByte();
  sign_bit = GetByte();
  digitalWrite(RST, LOW);
  Temp >>= 1;
  Serial.print("Temp: ");
  Serial.println(Temp);
}
unsigned char GetByte(void)
{ // GetByte() reads a 8-bit serial temperature signal from a DS1620 through the Arduino Mega pin 2 and  returns a 8-bit character.
  int i; 
  int data; 
  int D; 
 
  D = 0; 
  for (i=0; i<=7; i++) { 
    digitalWrite(CLK,LOW); 
    digitalWrite(CLK,HIGH); 
    pinMode(DQ,INPUT); 
    data=digitalRead(DQ); 
    D = D + (data << i); 
  } 
  return D; 
  /*
  pinMode(DQ, INPUT);
  unsigned char temp = 0;
  for (int i = 0; i < 8; i++)
  {
    // temp += digitalRead(DQ) << i;
    bitWrite(temp, i, digitalRead(DQ));
  }
  return temp;
  */
}

void PutByte(unsigned char data)
{ // PutByte() receives a 8-bit character and writes a 8-bit serial signal to a DS1620 through the Arduino Mega pin 2, returning nothing.
{ 
  int i; 
  pinMode(DQ,OUTPUT); 
  for(i=0; i<=7; i++) { 
    if(data%2 == 1) 
      digitalWrite(DQ,HIGH); 
    else 
      digitalWrite(DQ,LOW); 
    digitalWrite(CLK,HIGH); 
    digitalWrite(CLK,LOW); 
    data >>= 1; 
  } 
} 
  /*
  pinMode(DQ, OUTPUT);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(DQ, bitRead(data, i));
  }
  */
}

void CLK_SIGNAL(void)
{
  delay(halfFreq);
  digitalWrite(CLK, HIGH);
  delay(halfFreq);
  digitalWrite(CLK, LOW);
}