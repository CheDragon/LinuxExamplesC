#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  struct addrinfo hints, *res;
  int n, sock, err;
  char buffer[256];


  if(argc < 3){
      printf("Please provide address and port. For example: ./client localhost 3000\n");

      return 1;
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_INET;

  if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0){
    printf("Cannot get address from hints: %s\n", strerror(errno));

    return 1;
  }

  if(connect(sock, res->ai_addr, res->ai_addrlen) != 0){
    printf("Problem connection to host: %s\n", strerror(errno));

    return 1;
  }

  do{
    memset(buffer, 0, 256);
    printf("Enter the same message for server:\n");
    fgets(buffer, 256, stdin);
    n = write(sock, buffer, 256);
  }while(n > 0);

  return 0;
}
