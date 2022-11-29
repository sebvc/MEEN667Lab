/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write this discrete-time control law Eq. (9) in C code.
 * u(k) = u(k-1)+2e(k)-e(k-1)
 */

double y,r,e,u,u1=0,e1=0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

Discrete_control() {
  y = get_speed();
  e = r-y; // error = target - current
  u = u1 + 2*e - e1; // u(k) = u(k-1) + 2e(k) - e(k-1)
  output_ctrl(u);
  u1=u;
  e1=e;
}
