#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "socket_data.h"
#define NUM_DUMMY_DATA 100
#define BUF_SIZE 500
#define PORTNUMBER 14221

static SensorData *dummy_data;

void
error(const char *msg)
{
  perror(msg);
  exit(1);
}

void
dummy_generator()
{
  int i;
  dummy_data = malloc(NUM_DUMMY_DATA*sizeof(SensorData));
  for(i = 0; i < NUM_DUMMY_DATA; i++){
    dummy_data[i].x = i * 0.01;
    dummy_data[i].y = i * -0.02;
    dummy_data[i].z = i * 0.03;
    dummy_data[i].time = 0;
    dummy_data[i].sensor_type = i%3;
    dummy_data[i].driver_library = i%3;
  }

}

void toString(SensorData *data, char *buffer)
{
  int i = 0;
  int index = 0;
  char subString[50] = {0};
  memset(buffer, 0, BUF_SIZE);
//x
  sprintf(subString, "%lf", data->x);

  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '|';
  index++;
//y
  memset(subString, 0, 50);
  i = 0;

  sprintf(subString, "%lf", data->y);
  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '|';
  index++;
//z
  memset(subString, 0, 50);
  i = 0;
  sprintf(subString, "%lf", data->z);
  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '|';
  index++;
//time
  memset(subString, 0, 50);
  i = 0;

  sprintf(subString, "%d", data->time);
  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '|';
  index++;
//sensor_type
  memset(subString, 0, 50);
  i = 0;

  sprintf(subString, "%d", data->sensor_type);
  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '|';
  index++;
//driver_library
  memset(subString, 0, 50);
  i = 0;

  sprintf(subString, "%d", data->sensor_type);
  while(subString[i] != 0){
    buffer[index] = subString[i];
    i++;
    index++;
  }
  buffer[index] = '*';
}

void
send_data(SensorData *data, int socketFD, char *buffer)
{
  int charsWritten = 0;

  toString(data, buffer);

  charsWritten = send(socketFD, buffer, strlen(buffer), 0);
  if(charsWritten < 0)
    error("CLIENT: ERROR writing to socket");
  if(charsWritten < strlen(buffer))
    printf("CLIENT: WARNING: Not all data written to socket!\n");
}


int
main(int argc, char *argv[])
{

  int socketFD, portNumber, charsWritten, charsRead, i;
  struct sockaddr_in serverAddress;
  struct hostent* serverHostInfo;
  char buffer[BUF_SIZE];

  dummy_generator();

  //pretty printing
  // for(i = 0; i < NUM_DUMMY_DATA; i++){
  //   toString(&dummy_data[i], buffer);
  //   printf("\r%s%%", buffer);
  //   fflush(stdout);
  //   usleep(100000);
  // }
  // printf("\n");

  memset((char *)&serverAddress, '\0', sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORTNUMBER);
  serverHostInfo = gethostbyname("localhost");
  if(serverHostInfo == NULL){
    fprintf(stderr, "CLINET: ERROR, no such host\n");
    exit(0);
  }
  memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)serverHostInfo->h_addr, serverHostInfo->h_length);
  socketFD = socket(AF_INET, SOCK_STREAM, 0);
  if(socketFD < 0)
    error("CLIENT: ERROR opening socket");
  printf("Connecting to display_server....\n");
  if(connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    error("CLIENT: ERROR connecting");

  charsWritten = send(socketFD, "disc", 4 , 0);
  if(charsWritten < 0)
    error("CLINET: ERROR writing to socket");
  if(charsWritten < 4)
    printf("CLIENT: WARNING: Not all data written to socket!\n");

  char check[2] = "0\0";
  charsWritten = recv(socketFD, check, 1, 0); // if read 0, wrong server
  if(charsWritten < 0)
    error("CLINET: ERROR reading from socket");
  if(check[0] == '0'){
    printf("Error connecting to display_server\n");
    exit(1);
  }
  printf("Connected to display_server, sending data....\n");

  for(i = 0; i < NUM_DUMMY_DATA; i++){
    send_data(&dummy_data[i], socketFD, buffer);
    check[0] = '0';
    do {
      charsWritten = recv(socketFD, check, 1, 0);
    } while(check[0] != '1');
  }

  close(socketFD);

  free(dummy_data);

  return 0;
}
