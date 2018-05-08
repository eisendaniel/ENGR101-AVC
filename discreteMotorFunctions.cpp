#include <stdio.h>
#include <time.h>
#include "E101.h"

int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();
    // Writes PWM with a duty cycle of 100% to both motors
    forwardMotors(255);

    // Waits for 1.5 seconds (1500000 microseconds )
    sleep1 (1 ,500000);

    // Writes a duty cycle of 100% to motor 1 and -100% to motor 2 (making it turn on the spot)
    spotTurnLeft(255);
    sleep1 (0 ,500000);

    // Writes PWM with a duty cycle of 0% to both motors
    stopMotors();
    sleep1 (0 ,500000);

    //Writes a signal of 150 (Approximately half) to motor 2, and -150 to motor 1, making it spot-turn
    spotTurnRight(150);
    sleep1 (0, 500000);

    //Stops both motors, again
    stopMotors();

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
