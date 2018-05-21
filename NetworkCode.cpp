int NetworkConnect () {
	init();
	//initialise
	
	connect_to_server("192.168.1.2", 1024);
	//connect to server of IP and port
	
	Char Message[24]; 
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
