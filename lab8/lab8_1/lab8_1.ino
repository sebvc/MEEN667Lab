/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program which displays the voltage output from the IR sensor.  Use the C
 * code you wrote in the A/D converter lab in Lab 3 with replacing the potentiometer with
 * this IR sensor.  Record the values of distance (from 10 cm to 70 cm at every 5 cm for
 * GP2D12 or from 5 cm to 25 cm at every 2.5 cm for GP2D120) and the corresponding
 * output voltage to calibrate this IR sensor.
 */
int ir_pin = A0;
float dist;

void setup()
{
  Serial.begin(9600);
  // Set the IR pin as an input
  pinMode(ir_pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  dist = AI2float(ir_pin, true);
  Serial.println(" cm");
}

float AI2float(int AI_pin, bool print = false)
{
  float V = 0.004934434 * (float)analogRead(AI_pin);
  if (print)
    Serial.print(V);
  return V;
}
/* LAB3_2 code
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