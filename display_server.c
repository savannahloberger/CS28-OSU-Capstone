#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "socket_data.h"
#define BUF_SIZE 500
#define PORTNUMBER 14221
#define TIMEOUT 2

static SensorData dummy_data;

void error(const char *msg) {
  perror(msg);
  exit(1);
}

void to_data(char *buffer){
  double x;
  double y;
  double z;
  unsigned int time;
  int sensor_type;
  int driver_library;

  char sub_buffer[50] = {0};
//get x
  int i = 0;
  int buf_i = 0;
  while(buffer[i] != '|'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  i++;
  sscanf(sub_buffer, "%lf", &x);
//get y
  memset(sub_buffer, 0, 50);
  buf_i = 0;
  while(buffer[i] != '|'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  sscanf(sub_buffer, "%lf", &y);
  i++;
//get z
  memset(sub_buffer, 0, 50);
  buf_i = 0;
  while(buffer[i] != '|'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  sscanf(sub_buffer, "%lf", &z);
  i++;
//get time
  memset(sub_buffer, 0, 50);
  buf_i = 0;
  while(buffer[i] != '|'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  sscanf(sub_buffer, "%d", &time);
  i++;
//get sensor_type
  memset(sub_buffer, 0, 50);
  buf_i = 0;
  while(buffer[i] != '|'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  sscanf(sub_buffer, "%d", &sensor_type);
  i++;
//get driver_library
  memset(sub_buffer, 0, 50);
  buf_i = 0;
  while(buffer[i] != '*'){
    sub_buffer[buf_i] = buffer[i];
    i++;
    buf_i++;
  }
  sscanf(sub_buffer, "%d", &driver_library);
  dummy_data.x = x;
  dummy_data.y = y;
  dummy_data.z = z;
  dummy_data.time = time;
  dummy_data.sensor_type = sensor_type;
  dummy_data.driver_library = driver_library;
}

int main(int argc , char * argv[]){

  int listenSocketFD, establishedConnectionFD, portNumber, charsRead, readLen;
  socklen_t sizeOfClinetInfo;
  struct sockaddr_in serverAddress, clientAddress;
  char buffer[BUF_SIZE];

  memset((char *)&serverAddress, '\0', sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORTNUMBER);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocketFD < 0)
    error("ERROR opening socket");
  if(bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    error("ERROR on binding");

  listen(listenSocketFD , 1);
  printf("Listening for display_client.....\n");

  sizeOfClinetInfo = sizeof(clientAddress);
  establishedConnectionFD = accept(listenSocketFD,(struct sockaddr *)&clientAddress, &sizeOfClinetInfo );
  printf("Accepting.....\n" );
  if(establishedConnectionFD < 0)
    error("ERROR on accept");

  memset(buffer, '\0', BUF_SIZE);

  charsRead = recv(establishedConnectionFD, buffer, 4 ,0);
  if(charsRead < 0)
    error("ERROR reading from socket");
  if(strcmp(buffer, "disc") == 0)
    printf("Connected. Reading from display_client.....\n");
  else {
    fprintf(stderr, "Error connecting. Exiting...\n");
    exit(1);
  }
  charsRead = send(establishedConnectionFD, "1", 1 ,0);

  while(1){
    readLen = 0;
    memset(buffer, '\0', BUF_SIZE);
    do{
      charsRead = recv(establishedConnectionFD, &buffer[readLen], BUF_SIZE, 0);
      if(charsRead < 0)
        error("ERROR reading from socket");
      readLen += charsRead;
    }while(buffer[readLen-1] != '*');

    to_data(buffer);
    printf("x: %lf  y: %lf z: %lf\n",dummy_data.x, dummy_data.y, dummy_data.z);

    send(establishedConnectionFD, "1", 1 ,0);
  }

  close(establishedConnectionFD);

  close(listenSocketFD);

  return 0;
}
