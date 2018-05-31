#include <stdio.h>
#include <time.h>
#include "E101.h"

//Test this as a standalone 1st - good luck :/

void quadFourLoop() 
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
  int leftMotor = 2;
  int rightMotor = 1;
  bool isDriving = true;

  while (true)
  {
      distLeft = read_analog(SL);
      distFront = read_analog(SF);
      distRight = read_analog(SR);

      //If robot detects red line before time gate
      take_picture();
      if((get_pixel(160,120,0)>170)&&(get_pixel(160,120,1)<80)&&(get_pixel(160,120,2)<80))
      {
        set_motor(leftMotor, 0);
        set_motor(rightMotor, 0);
        isDriving = false;
        while (isDriving == false)
        {   //While botty is stopped
            distFront = read_analog(SF); //Check front sensor
            if (distFront < 300) //If clear ahead
            {
              set_motor(leftMotor, 127);
              set_motor(rightMotor, 127);
              isDriving = true;
              break;
            }
            else //Gate is shut
            {
              sleep1(0, 999999); //Sleep 1 second
            }
        }
      }

      if (isDriving == true)
      {  //Keep robot centered
          if ((distLeft > 550) && (distRight < 450))
          { //Sway right - too close to left
            set_motor(leftMotor, 187);
            set_motor(rightMotor, 127);
            sleep1(0, 400000);
            set_motor(leftMotor, 127);
          }
          else if (((distLeft > 600) && (distLeft < 700)) && (distRight < 600))
          { //Sway left - too close to right
            set_motor(leftMotor, 127);
            set_motor(rightMotor, 187);
            sleep1(0, 400000);
            set_motor(rightMotor, 127);
          }
          else (((distLeft > 600) && (distLeft < 700)) && ((distRight > 500) && (distRight < 600)))
          { //Keep straight - already centred
            set_motor(leftMotor, 127);
            set_motor(rightMotor, 127);
          }
      }

	  if (distFront > 550)
	  {
		if (distLeft < 300)
		{ //Turn left
			set_motor(leftMotor, 0);
			set_motor(rightMotor, 0);
			sleep1(0,500000);
			set_motor(leftMotor, -200);
			set_motor(rightMotor, 200);
			sleep1(0,870000);
			set_motor(leftMotor, 127);
			set_motor(leftMotor, 127);
		}  
		else //(distRight < 100)
		{ //Turn right
			set_motor(leftMotor, 0);
			set_motor(rightMotor, 0);
			sleep1(0,500000);
			set_motor(leftMotor, 200);
			set_motor(rightMotor, -200);
			sleep1(0,870000);
			set_motor(leftMotor, 127);
			set_motor(leftMotor, 127);
		}
	  }
  }
}

int main ()
{
  init();
  quadFourLoop();
  return 0;
}
