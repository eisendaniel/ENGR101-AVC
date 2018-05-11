#include <stdio.h>
#include <time.h>
#include "E101.h"
bool debug=true; //Sets the program into "debugging" mode. This will be phased out later on.
//Writes a PMW with a duty cycle of 0% to both motors, stopping both.
char phase = 2;//DEBUGGING ONLY, THIS SHOULD START AT PHASE 1!
double finalError=0;
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
//Takes an image, then scans the pixels along the middle of the image for white/black pixels, then attempts to convert them to a basic "Error signal" = the integer returned gives how "right" of the line the AVC is.
double getErrorSignal()
{
printf("Starting GetErrorSignal!");
take_picture();
int j=-160;
while(j<159)
 {
  printf("getErrorSignal's for loop started on cycle:%d\n",j);
  char white = get_pixel(120,(j+160),3);
  double currentError = white + j;

  finalError = finalError + currentError;
 //Get colour (modify code so it starts from the left and goes to the right)
 //Multiply colour value by current J value
 //Add the result to a "final value"
 //Once everything else is done, return the final value as an error signal.
 //NO CODE IS HERE YET, I WILL DO THIS LATER -L
 printf("Current FinalError is:%d \n",finalError);
 j=j+1;
 }
 printf("THE FINAL ERROR VALUE IS:%d",finalError);
 return(finalError);
}
int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();

    //Sets the AVC to "phase 1", where it follows a simple maze-following protocol
    while(phase==1)
    {


    }

    if(debug==true){getErrorSignal();sleep1(1,0);printf("Error signal:%f",finalError);}
    //sets the AVC to "phase 2", where it follows advanced maze-following protocols for sharp right-and-left hand turns. Might be integrated into the above function.
    while(phase==2&&false)
    {
      printf("No red detected!");
      take_picture();
      display_picture(1,1);
        //Ends the loop if it detects the red square which signals the box-maze
        //Compound Boolean (I'm sorry) which triggers if there is red light and NOT green OR blue light, as white is a mix of all 3.
        if((get_pixel(160,120,0)>170)&&(get_pixel(160,120,1)<80)&&(get_pixel(160,120,2)<80))
        {
          phase=3;
          printf("Red detected! Debug shutting down!");
        }
    }

    //Sets the AVC to "phase 3", which is enabled after the sensor/camera at the front detects the red square which signals the start of the "Box maze"
    //THIS IS WHERE THE DISCRETE SPOT-TURN FUNCTIONS ARE USED!
    while(phase==3)
    {

    }
    return 0;
}
