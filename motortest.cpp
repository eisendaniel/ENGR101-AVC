#include <stdio.h>
#include <time.h>
#include "E101.h"


int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();
    // Writes PWM with a duty cycle of 0% to motor 1
    set_motor (1 ,0);

    // Waits for 0.5 seconds (500000 microseconds )
    sleep1 (0 ,500000);

    // Writes PWM with a duty cycle of 100% to motor 1
    set_motor (1 ,255);
    set_motor (2 ,255);
    sleep1 (0 ,500000);

    // Writes PWM with a duty cycle of 0% to motor 1
    set_motor (1 ,0);
    sleep1 (0 ,500000);

    return 0;
}
