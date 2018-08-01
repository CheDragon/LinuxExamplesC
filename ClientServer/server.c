#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LOGFILE "/tmp/logfile"
#define FIFOFILE "/tmp/fifo"


int main(int argc, char **argv) {
  int sock, newsock, n, x, portno, clilength, logfile, fifofd;
  char buffer[255];
  struct sockaddr_in server_socket, client_socket;

  if( argc < 2 ){
    printf("Please provide a port: for exampe ./server 3000\n");
    return 1;
  }

  portno = atoi(argv[1]);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  server_socket.sin_family = AF_INET;
  server_socket.sin_addr.s_addr = INADDR_ANY;
  server_socket.sin_port = htons(portno);

  if( bind(sock, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0 ){
    printf("Error in bind: %s\n", strerror(errno));
    return 1;
  }


  for(;;){
    listen(sock, 5);
    clilength = sizeof(client_socket);

    printf("Now accepting connections in port: %d\n", portno);
    newsock = accept(sock, (struct sockaddr *)&client_socket, &clilength);
    if(newsock < 0){
      printf("Error in accepting a connection: %s\n", strerror(errno));
      return 1;
    }


    if(fork() == 0){
      do{
        memset(buffer, 0, 256);
        n = read(newsock, buffer, 256);

        if(n > 0){
          printf("Client sends a message: %s\n", buffer);
          logfile = open(LOGFILE, O_WRONLY | O_APPEND | O_CREAT, 0777);
          write(logfile, buffer, 255);
          close(fifofd);
        }
      }while(n > 0);
    }
  }

  close(newsock);
  close(sock);

	return 0;
}
