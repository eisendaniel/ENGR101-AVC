#include <stdio.h>
#include <time.h>
#include "E101.h"

int main () {	
	//initialise
	init();
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
	printf("%s", Message);
	//sends received message back to server
	send_to_server(Message);
	//end
	return 0;
}
