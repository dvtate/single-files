import socket;
import sys;

host = "127.0.0.1";

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);

client_addr = ("127.0.0.1", 10000);



print ("The client is starting :D");

try:
	sock.connect(client_addr);
except:
	print("ERROR: port in use/can\'t connect");
	new_port = raw_input("New port number: ");
	sock.bind((host, int(new_port)));
	#quit();


try:
	data = "hello there :P";
	sock.sendall(data);
	data = sock.recv(1024);
	print (data);
	
	
	data = "close";
	sock.sendall(data);
	data = sock.recv(1024);
	print (data);

finally:
	sock.close();
