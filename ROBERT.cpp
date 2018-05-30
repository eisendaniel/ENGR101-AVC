#include <stdio.h>
#include <math.h>
#include "E101.h"


int lineWhiteThreshold = 127;
int minWhiteToSeeLine = 10000000;
float kp = 0.003; //Will need to adjust this
int qdr = 1; //Sets the start quadrant. FOR THE LOVE OF GOD, SET THIS TO 1 WHEN NOT DEBUGGING!!!!!!!
int loopDelay = 100000;
int baseSpeed = 110;
int minWhiteForQ3 = 10005000;

//=======================General Functions=======================
void setSpeed(int left, int right)
{
	if (left > 254) left = 254;
	if (left < -254) left = -254;
	if (right > 254) right = 254;
	if (right < -254) right = -254;
	set_motor(1, right);
	set_motor(2, left);
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
	take_picture();
      //display_picture(1,1); - For debugging only
        //Ends the loop if it detects the red square which signals the box-maze
        //Compound Boolean (I'm sorry) which triggers if there is red light and NOT green OR blue light, as white is a mix of all 3.
        if((get_pixel(160,120,0)>170)&&(get_pixel(160,120,1)<80)&&(get_pixel(160,120,2)<80))
        {
          return true;
        }
				else{return false;}
}

//===Alternate Error Signal Code===
double getErrorSignal()
{
	bool white = false;
	double finalError;

	take_picture();
	int threshold; //This initializes the max and min variables which help the program to see static "black or white" rather than shades of gray.
	//I'M COMMENTING THIS BECAUSE I SUCK WITH INITIALIZING VARIABLES AND IT PROBABLY DOESN'T WORK
	int min = 255;
	int max = 0;
	for (int k = 0; k < 319; k++)
	{
		if ((get_pixel(120,(k), 3)) < min)
		{min = get_pixel(120, (k), 3);}
		printf("Getting minimum!");

		if ((get_pixel(120, k, 3)) > max)
		{max = get_pixel(120, k, 3);}
		printf("Getting Maximum!");

		threshold = ((min + max) / 2);
	}
	for (int j = -160; j < 159; j++) //Loop for finding the error signal. Starts at -160 rather than 0 so that values further out from the center are amplified when multiplied with J
	{
		printf("Running get_pixel with row of 120, column of %d\n\n",(j+160));
		if ((get_pixel(120, (j+160), 3)) > threshold) {
			white = true;
		} else {
			white = false;
		}
		//  char white = get_pixel((j+160),120,3);
		double currentError = white * (j * 5.0);
		finalError = finalError + currentError;
	}
	return (finalError);
}

//=======================Quadrant Four=======================

void quadFourLoop() {

}

//Quadrant Three: Modified////////////////////////////////////////////////
void quadThreeBetaLoop()
{
	double errorSignalBeta = getErrorSignal();
	setSpeed(baseSpeed + errorSignalBeta*kp, baseSpeed - errorSignalBeta*kp);
	if(!canSeeLine)
	{Q3Turn(false);
	}
if(canSeeQ4)
{qdr=4;
return;}


}

//=======================Quadrant Three: Original=======================

void quadThreeLoop()
{
	double errorSignal;
	kp = 0.000033;
	bool clockwise = false;
	while(true) {
		take_picture();
		if (canSeeQ4())
		{qdr=4;
		return;}
		else if (canSeeLine())
		{
			//Robot is on track
			//printf("Can see line \n"); - Debug only
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

//=======================Quadrant two=======================
void quadTwoLoop()
{
	/*take_picture();
	if (canSeeLine())//Checks if there's a large amount of white. If so, goes to Quad 3.
	{
		if (numWhiteInImg(220, 230) > minWhiteForQ3)
		{
			//Robot detcts a large amount of white (has entered Quadrant 3)
			qdr=3;
			return;
		}
	}*/
	double errorSignalBeta = getErrorSignal();
	setSpeed(baseSpeed + errorSignalBeta*kp, baseSpeed - errorSignalBeta*kp);
}


//=======================Quadrant One=======================

void quadOne()
{
//set char array to contain IP
char serverIP[15] = {"130.195.6.196"};
//connect to server of IP and port
connect_to_server(serverIP, 1024);
//create char array
char Message[24] = {"Please"};
//sends message to the server
send_to_server(Message);
//receives message from server, sets to array 'Message'
receive_from_server(Message);
//print server output
//printf("%s", Message); //Re-impliment if testing!
//sends received message back to server
send_to_server(Message);
//end

	qdr=5;
	return;
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
  sleep1(2, 0);
	while(true)//Ensures that whatever the current quadrant is, it'll run that method until it's updated to run a new quadrant
	{
		//I'm sorry for the demonCode(tm), but it works - L
		if(qdr==1){quadOne();}
		else if (canSeeQ4()){setSpeed(0,0); return 0;}
		else if(qdr==2){quadTwoLoop();}
		else if(qdr==3){quadThreeLoop();}
		else if(qdr==4){quadFourLoop();}
		else{setSpeed(0,0); printf("WHAT DID YOU DO?! Shutting down and awaiting the singularity."); break;}
	}//If this triggers, it means something's gone horrifically wrong. Just stand by and wait for the implosion. This should literally NEVER happen.
}
