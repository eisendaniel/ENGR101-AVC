#include <stdio.h>
#include <time.h>
#include "E101.h"

//Test this as a standalone 1st - good luck :/

void Q4 ()
{
  //180 degree turn - will need to adjust these values
  set_motor(1, 127);
  set_motor(2, -127);
  sleep1(0, 999999); //sleep 1 second
  set_motor(1, 127); //set motors to default speed
  set_motor(2, 127);

  //Assumes sensor position D0 as left, D1 as front, D2 as right
  int SL = 0;
  int SF = 1;
  int SR = 2;
  int distFront;
  int distLeft;
  int distRight;
  int leftMotorSpeed = 127;
  int rightMotorSpeed = 127;
  int leftMotor = 2;
  int rightMotor = 1;
  int error;
  bool isDriving = true;

  while (true)
  {
      distLeft = read_digital(SL);
      distFront = read_digital(SF);
      distRight = read_digital(SR);

      //Robot will go through time gate with this code - will need to
      //add some code here to tell it - if detects red, stop, if no obstacle go,
      //if there is obstacle, wait and try again.

      if (isDriving == true)
      {  //Keep robot centered
        error = distRight-distLeft;
        if ( (distLeft == distRight) || (error < 20) )
        //If centred, or little error in positioning
        {  //Set both motors to default speed
          leftMotorSpeed = 127;
          rightMotorSpeed = 127;
          set_motor(leftMotor, leftMotorSpeed);
          set_motor(rightMotor, rightMotorSpeed);
        }
        else
        {  //Modify motor speeds based on the level of positioning error
          leftMotorSpeed = leftMotorSpeed + (error * 0.1);
          rightMotorSpeed = rightMotorSpeed - (error * 0.1);
          set_motor(leftMotor, leftMotorSpeed);
          set_motor(rightMotor, rightMotorSpeed);
        }
      }

      if ( (distFront > 100) && (distFront < 500) ) //If going to crash into wall
      {
        isDriving = false;
        set_motor(leftMotor, 0);
        set_motor(rightMotor, 0);
        sleep1(0, 200000); //Sleep 0.2 seconds
        if (distLeft > distRight)
        { //Turn left
          set_motor(leftMotor, -127);
          set_motor(rightMotor, 127);
          sleep1(0, 999999); //Sleep 1 second - will need to adjust turning
          set_motor(leftMotor, 127);
          set_motor(rightMotor, 127);
          sleep1(0, 200000); //Sleep 0.2s - go forward a little
          isDriving = true;
        }
        else if (distLeft < distRight)
        { //Turn right
          set_motor(leftMotor, 127);
          set_motor(rightMotor, -127);
          sleep1(0, 999999); //Sleep 1 second - will need to adjust turning
          set_motor(leftMotor, 127);
          set_motor(rightMotor, 127);
          sleep1(0, 200000); //Sleep 0.2s - go forward a little
          isDriving = true;
        }
        else
        {
          //pAnIc!! (if neither side has a gap)
          set_motor (leftMotor, 0);
          set_motor (rightMotor, 0);
          break;
        }
      }
  }
}

int main ()
{
  init();
  Q4();
  return 0;
}
