#include <stdio.h>
#include <time.h>
#include "E101.h"

void setSpeed(int left, int right)
{
	if (left > 254) left = 254;
	if (left < -254) left = -254;
	if (right > 254) right = 254;
	if (right < -254) right = -254;
	set_motor(1, right);
	set_motor(2, left);
}

int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();

      setSpeed(0,0);
      sleep1(0,500000);
      setSpeed(-70,70);//The speed at which it turns. Both values must be equal, just in opposite directions!
      sleep1(3,500000);//This is how long it turns on-the-spot for. Needs to be long enough to go 90 degrees, roughly!
      setSpeed(0,0);
    
        set_motor(1, 0);
        set_motor(2, 0);

        sleep1 (0 ,500000);

    return 0;
}
