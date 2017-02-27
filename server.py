import socket;
import sys;

host = "127.0.0.1";

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
server_address = (host, 10000); #localhost + port 10000

print ("The server is starting :D");

# start working
try:
	sock.bind(server_address);
except:
	print("ERROR: port in use.");
	new_port = raw_input("New port number: ");
	sock.bind((host, int(new_port)));
	#quit();

sock.listen(1);

print ("Listening...");
	
while True:
	connection, address = sock.accept();
	while True:	
		data = connection.recv(1024);
		print("recieved :D %s" %(data));
		connection.sendall(data);
		if (data == "close"):
				break;
	connection.close();
		
		
