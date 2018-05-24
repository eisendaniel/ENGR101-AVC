#include <stdio.h>
#include <time.h>
#include "E101.h"

int main () {	
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
	
	return 0;
	//end
}
