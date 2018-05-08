#include <stdio.h>
#include <time.h>
#include "E101.h"

int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();
    char phase = 2;//DEBUGGING ONLY, THIS SHOULD START AT PHASE 1!

    //Sets the AVC to "phase 1", where it follows a simple maze-following protocol
    while(phase=1)
    {


    }

    //sets the AVC to "phase 2", where it follows advanced maze-following protocols for sharp right-and-left hand turns. Might be integrated into the above function.

    while(phase=2)
    {
      printf("No red detected!");

        //Ends the loop if it detects the red square which signals the box-maze
        //Compound Boolean (I'm sorry) which triggers if there is red light and NOT green OR blue light, as white is a mix of all 3.
        if((get_pixel(160,120,0)=1)&&(get_pixel(160,120,1)=0)&&(get_pixel(160,120,2)=0))
        {
          phase=3;
          printf("Red detected! Debug shutting down!");
        }
    }

    //Sets the AVC to "phase 3", which is enabled after the sensor/camera at the front detects the red square which signals the start of the "Box maze"
    //THIS IS WHERE THE DISCRETE SPOT-TURN FUNCTIONS ARE USED!
    while(phase=3)
    {

    }
    return 0;
}




//Writes a PMW with a duty cycle of 0% to both motors, stopping both.
void stopMotors()
{
  set_motor(1, 0);
  set_motor(2, 0);
}

//Moves both motors in the "forward" direction with a given speed as a parameter
void forwardMotors(double speed)
{
  set_motor(1, speed);
  set_motor(2, speed);

}
//Moves both motors in the "backward" direction with a given speed as a parameter
void backMotors(double speed){
 forwardMotors(-speed);
}

//Turns both motors in opposite directions for [time] milliseconds, with a speed of [speed]
void spotTurnLeft(double speed, double time)
{
  set_motor(1, speed);
  set_motor(2, -speed);
  sleep1 (0, time);
  stopMotors();
}

void spotTurnRight(double speed, double time)
{
  spotTurnLeft(-speed, time);
}
