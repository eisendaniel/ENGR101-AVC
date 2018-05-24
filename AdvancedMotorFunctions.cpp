#include <stdio.h>
#include <math.h>
#include "E101.h"


int lineWhiteThreshold = 127;
int minWhiteToSeeLine = 10000000;
float kp = 0.00005; //Will need to adjust this
int loopDelay = 100000;
int baseSpeed = 50;
int minWhiteForQ3 = 10005000;

//=======================General Functions=======================
void setSpeed(int left, int right)
{
	if (left > 254) left = 254;
	if (left < -254) left = -254;
	if (right > 254) right = 254;
	if (right < -254) right = -254;
	right *= -1;
	set_motor(1, left);
	set_motor(2, right);
}


//Updates white threshold to account for variations in lighting
void updateWhiteThreshold()
{
	take_picture();
	int totalWhite = 0;
	//Loop through whole image
	for (int r = 0; r < 240; r++)
	{
		for (int c = 0; c < 320; c++)
		{totalWhite += get_pixel(r, c, 3);}
	}
	//Set to average of all pixels
	lineWhiteThreshold = totalWhite / 76800;
}

//rowStart and rowEnd are inclusive. Remember to take picture before using.
double getLineErrorSignal(int rowStart, int rowEnd)
{
	int error = 0; //If negative, go left, if positive, go right
	int currWhite;
	for (int r = rowStart; r <= rowEnd; r++)
	{	//Loop through the rows we are looking at
		for (int c = 0; c < 320; c++)
		{	//Loop through the columns in the row
			currWhite = get_pixel(r, c, 3);
			error += currWhite*(c - 160);
		}
	}
	//Return the Average error of the rows
	return (double) error / (rowEnd - rowStart + 1);
}

//Returns number of white pixels in image. Call take picture first.
int numWhiteInImg(int rowStart, int rowEnd)
{
	int numWhite;
	for (int r = rowStart; r < rowEnd; r++)
	{
		for (int c = 0; c < 320; c++)
		{	//Loop through image
			if (get_pixel(r, c, 3) > lineWhiteThreshold)
			{	//Pixel is white
				numWhite++;
			}
		}
	}
	printf("numWhite: %d \n", numWhite);
	return numWhite;
}

bool canSeeLine()
{
	int numWhite = numWhiteInImg(220, 230);
	if (numWhite > minWhiteToSeeLine)
	{return true;}
	else {return false;}
}

void reverseUntilSeeLine()
{
	setSpeed(-40, -40);
	while (canSeeLine() == false)
	{
		take_picture();
		sleep1(0, loopDelay);
	}
	setSpeed(0, 0);
}

void Q3Turn(bool clockwise)
{
	int turnSpeed = 100;
	int speedOne = clockwise ? -turnSpeed : turnSpeed;
	int speedTwo = clockwise ? turnSpeed : -turnSpeed;
	setSpeed(speedOne, speedTwo);
	while (true)
	{
		take_picture();
		if (canSeeLine()) return;
		sleep1(0, loopDelay);
	}
}

bool canSeeQ4() {
	//Fill this out to detect red square
	return false;
}

//=======================Quadrant Four=======================

void quadFourLoop() {

}

//=======================Quadrant Three=======================

void quadThreeLoop()
{
	double errorSignal;
	kp = 0.000033;
	bool clockwise = false;
	while(true) {
		take_picture();
		if (canSeeQ4())
		{quadFourLoop();}
		else if (canSeeLine())
		{
			//Robot is on track
			printf("Can see line \n");
			errorSignal = getLineErrorSignal(220, 230);
			setSpeed(baseSpeed + errorSignal*kp, baseSpeed - errorSignal*kp);
		}
		else
		{
			//Robot is not on track
			printf("Can't see line");
			clockwise = !clockwise;
			Q3Turn(clockwise);
		}
		sleep1(0, loopDelay);
	}
}

//=======================Quadrant Two=======================

void quadTwoLoop()
{
	double errorSignal;
	while(true)
	{
		take_picture();
		if (canSeeLine())
		{
			if (numWhiteInImg(220, 230) > minWhiteForQ3)
			{
				//Robot has entered Q3
				break;
			}
			else
			{
				//Robot is on track
				printf("Can see line \n");
				errorSignal = getLineErrorSignal(220, 230);
				setSpeed(baseSpeed + errorSignal*kp, baseSpeed - errorSignal*kp);
			}
		}
		else
		{
			//Robot is not on track
			printf("Can't see line");
			reverseUntilSeeLine();
		}
		sleep1(0, loopDelay);
	}
	quadThreeLoop();
}

//=======================Quadrant One=======================

void quadOne()
{
	//Add code for opening gate here
	connect_to_server("130.195.6.196", 1024);
	//connect to server of IP and port

	send_to_server("Please");
	//sends message to the server

	char Message[24];
	//create char array

	receive_from_server(Message);
	//receives message from server, sets to array 'Message'

	printf("%s", Message);
	//print server output

	send_to_server(Message);
	//sends received message back to server

	quadTwoLoop();
}

int image_analysis()
{
  take_picture();
  int sum = 0;
  //float kp = 0; //Change this value
  //int proportional_signal = 0;
  int w, s;
  for (int i = 0; i < 320; i++)
  {
    w = get_pixel(i, 120, 3);
    if (w > 127)
	{s = 1;}
    else
	{s = 0;}
    sum = sum + (i - 160) * s;
  }
  //proportional_signal = sum * kp;
  return 0;
}

int get_ir(int pin)
{
  int ir = 0;
  for (int i = 0; i < 5; i++)
  {ir = ir + read_analog(pin); /*Change this*/}
  return(ir / 5);
}

/*void check_block(char dir[]) {
  if (dir[] == "forward") {
    reading = get_ir(front);
    if (reading < thresh) {
      set_motor(0, 0);
      set_motor(1, 0);
    }
  }
}*/

int main()
{
  init();
  sleep1(15, 0);
  quadOne();
}
