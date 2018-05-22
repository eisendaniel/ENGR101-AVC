#include <stdio.h>
#include <time.h>
#include "E101.h"

int NetworkConnect () {	
	connect_to_server("130.195.6.196", 1024);
	//connect to server of IP and port
	
	char Message[24]; 
	//create char array
	
	Message = ("P", "l", "e", "a", "s", "e"); 
	//should contain connection password
	
	send_to_server(Message);
	//sends message to the server
	
	receive_from_server(Message);
	//receives message from server, sets to array 'Message'
	
	send_to_server(Message);
	//sends received message back to server
	
	return 0;
	//end
}
int main () {
	init();
	NetworkConnect();
	return 0;
}
