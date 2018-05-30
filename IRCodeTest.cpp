#include <stdio.h>
#include <time.h>
#include "E101.h"

//Test this as a standalone 1st - good luck :/

void Q4 ()
{
  set_motor(1, 127); //set motors to default speed
  set_motor(2, 127);

  //Assumes sensor position D2 as left, D0 as front, D1 as right
  int SL = 2;
  int SF = 0;
  int SR = 1;
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
      distLeft = read_analog(SL);
      distFront = read_analog(SF);
      distRight = read_analog(SR);
      error = distRight-distLeft;

      //If robot detects red line before time gate
      if((get_pixel(160,120,0)>170)&&(get_pixel(160,120,1)<80)&&(get_pixel(160,120,2)<80))
      {
        set_motor(leftMotor, 0);
        set_motor(rightMotor, 0);
        isDriving = false;
        while (isDriving == false)
        {   //While botty is stopped
            distFront = read_analog(SF); //Check front sensor
            if (!( (distFront > 100) && (distFront < 500) ) ) //If clear ahead
            {
              set_motor(leftMotor, 127);
              set_motor(rightMotor, 127);
              isDriving = true;
            }
            else //Gate is shut
            {
              sleep1(0, 999999); //Sleep 1 second
            }
        }
      }

      if (isDriving == true)
      {  //Keep robot centered
        if ( (distLeft == distRight) || (error < 20) || (error > -20) )
        //If centred, or little error in positioning
        {  //Set both motors to default speed
          leftMotorSpeed = 127;
          rightMotorSpeed = 127;
          set_motor(leftMotor, leftMotorSpeed);
          set_motor(rightMotor, rightMotorSpeed);
        }
        else
        {  //Modify motor speeds based on the level of positioning error
          leftMotorSpeed = leftMotorSpeed - (error * 0.1);
          rightMotorSpeed = rightMotorSpeed + (error * 0.1);
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
        if (distLeft < distRight)
        { //Turn left
          set_motor(leftMotor, -127);
          set_motor(rightMotor, 127);
          sleep1(0, 999999); //Sleep 1 second - will need to adjust turning
          set_motor(leftMotor, 127);
          set_motor(rightMotor, 127);
          sleep1(0, 200000); //Sleep 0.2s - go forward a little
          isDriving = true;
        }
        else if (distLeft > distRight)
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
