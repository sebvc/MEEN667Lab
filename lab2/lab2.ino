/* Team: Sebastian Villa, Logan Morris, Alan Gregory
 * Assignment:
 * Write a program that maintains a database of dates of birth of 12 users.  You have 
 * to give each of them a user id number (01-12) and ask for his/her date of birth. To protect 
 * anyone’s privacy, use fictitious dates of birth.  A 5-character password should be allotted 
 * to system administrator with user id number “00.”   Only the system administrator should 
 * be able to see the dates of birth of all users and calculate the average age of the group in 
 * years, months, and days.  To simplify your calculation, you can use 30 days in every 
 * month. 
 */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int incomingByte = 0;

void loop() {
      // put your main code here, to run repeatedly:
  // Send data only when you receive data.
  // Wait until there is something to read:
  while (Serial.available() == 0) {}

  incomingByte = Serial.read();

  // Say what you got:
  Serial.print("I received: ");
  Serial.println(incomingByte);

  }
