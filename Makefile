all: client server

client: display_client.c socket_data.h
	gcc -o client display_client.c

server: display_server.c socket_data.h
	gcc -o server display_server.c

clean:
	rm -f client server
