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

// Declarations
int option, user_ID, num1, num2, num3, num4, count = 0; // count is current number of users
char password[] = "12345";                              // {'1','2','3','4','5','\0'};
bool pass_correct;
String date;
int month[13], days[13], year[13], age[13]; // age[] stored in days.
int average_age, age_days, current_user_age_days;
int i;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  month[0] = 9;
  days[0] = 8;
  year[0] = 2022;
}

int Prompt()
{
  Serial.println("MENU:\t[0] Enter Existing User ID"
                 "\n\t[1] Add New User");
  while (Serial.available() == 0)
  {
  }
  return Serial.read() - '0';
}

String days2str(int day)
{
  int y, m;
  y = day / 360;
  day %= 360;
  m = day / 30;
  day %= 30;
  return String(y) + "yrs " + String(m) + "months " + String(day) + "days";
}

void loop()
{
  // put your main code here, to run repeatedly:
START:
  option = Prompt();

  switch (option)
  {
  case 0:
    Serial.print("Enter Existing User ID (00-");
    if (count < 10)
    {
      Serial.print("0");
    }
    Serial.println(String(count) + ")");
    while (Serial.available() == 0)
    {
    } // wait for input
    user_ID = Serial.readString().toInt();
    if (user_ID == 0)
    {
      Serial.print("Please Enter Admin(00) Password: ");
      while (Serial.available() == 0)
      {
      } // wait for input
      String inputed_password = Serial.readString();
      Serial.println("*****");
      if (inputed_password.equals(password))
      {
        Serial.println("Correct Password.");

        // ADMIN ACTIVITIES
        int sum = 0;
        for (i = 1; i <= count; i++)
        {
          // calc avg of age elements
          sum += age[i];
          Serial.println("User" + String(i) + ":\tBirthday: " + String(month[i]) + "/" + String(days[i]) + "/" + String(year[i]) + "\n\tAge: " + days2str(age[i]));
        }
        age[0] = sum / count; // average of ages.
        Serial.println("---------------------------------\n"
                       "Average Age: " +
                       days2str(age[0]));

        // current_user_birthday = String(month[i]) + '/' + String(days[1]) + '/' + String(year[i])

        // current_user_birthday_days = month[i]*30 + days[i] + year[i]*12*30 ;
        // current_user_age_days = current_date_days - current_user_birthday_days ;
      }
      else
      {
        Serial.println("Incorrect Password!");
        goto START;
      }
    }
    else if ((user_ID <= count) && (user_ID > 0))
    {
      Serial.println("User" + String(user_ID) + ":\tBirthday: " + String(month[user_ID]) + "/" + String(days[user_ID]) + "/" + String(year[user_ID]) + "\n\tAge: " + days2str(age[user_ID]));
    }
    break;

  case 1:
    while (true)
    {
      count += 1;
      if (count > 12)
      {
        Serial.println("Max Users Reached");
        goto START;
      }
      Serial.print(" New User ID: ");
      Serial.println(count);
      Serial.println("\nEnter birthday in the following format: DD/MM/YYYY");
      while (Serial.available() == 0)
      {
      }
      date = Serial.readString();
      Serial.println(date);
      if (date.length() != 10)
      {
        Serial.println("Incorrect Date Format");
        goto START;
      }

      days[count] = (date[0] - '0') * 10 + (date[1] - '0');
      Serial.println(days[count]);
      month[count] = (date[3] - '0') * 10 + (date[4] - '0');
      Serial.println(month[count]);
      year[count] = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
      Serial.println(year[count]);

      num2 = (year[0] - year[count]) * 360;
      num3 = (month[0] - month[count]) * 30;
      num4 = (days[0] - days[count]);
      if (num3 < 0)
      {
        num3 = 12 + num3;
        num2--;
      }
      if (num4 < 0)
      {
        num4 = 30 + num4;
        num3 = num3 - 30;
      }
      age[count] = num2 + num3 + num4;
      break;

    default:
      Serial.println("Invalid entry");
      goto START;
      break;
    }
  }
}
