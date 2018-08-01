#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv){
  int result;
  char *path;

  path = getenv("PATH");
  if(path != NULL){
    printf("Path: %s\n", path);
  } else {
    printf("Path not found\n");
  }

  result = execvp("ls", argv);
  printf("Should not be here! Error");

  return 1;
}
