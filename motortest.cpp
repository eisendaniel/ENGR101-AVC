#include <stdio.h>
#include <time.h>
#include "E101.h"


int main ()
{
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init ();

    for (int i = 0; i < 4; i++)
    {
        set_motor(1, 255);
        set_motor(2, 255);

        sleep1 (0 ,500000);;

        set_motor(1, 0);
        set_motor(2, 0);

        sleep1 (0 ,500000);;
    }
    return 0;
}
