#include <stdio.h>
#include <time.h>
#include "E101.h"
bool debug=true; //Sets the program into "debugging" mode. This will be phased out later on.
//Writes a PMW with a duty cycle of 0% to both motors, stopping both.
char phase = 2;//DEBUGGING ONLY, THIS SHOULD START AT PHASE 1!

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
take_picture();
int threshold; //This initializes the max and min variables which help the program to see static "black or white" rather than shades of gray.
//I'M COMMENTING THIS BECAUSE I SUCK WITH INITIALIZING VARIABLES AND IT PROBABLY DOESN'T WORK
int min=255;
int max=0;
for(int k=0; k<320;k++)
{
if ((get_pixel((k),120,3))<min){min=get_pixel((k),120,3);}
if ((get_pixel((k),120,3))>max){max=get_pixel((k),120,3);}
threshold=((min+max)/2);
}

for(int j=-160; j<159;j++)//Loop for finding the error signal. Starts at -160 rather than 0 so that values further out from the center are amplified when multiplied with J
 {
   if((get_pixel((j+160),120,3))>threshold){char white = 1;} else{char white = 0;}
//  char white = get_pixel((j+160),120,3);
  double currentError = white * (j*5);

  double finalError = finalError + currentError;
 //Get colour (modify code so it starts from the left and goes to the right)
 //Multiply colour value by current J value
 //Add the result to a "final value"
 //Once everything else is done, return the final value as an error signal.
 //NO CODE IS HERE YET, I WILL DO THIS LATER -L
 }
 printf("THE FINAL ERROR VALUE IS:%d",finalError);

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

    while(debug==true){getErrorSignal();sleep1(5,0);}
    //sets the AVC to "phase 2", where it follows advanced maze-following protocols for sharp right-and-left hand turns. Might be integrated into the above function.
    while(phase==2)
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
