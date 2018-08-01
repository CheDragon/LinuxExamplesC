#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globalData = 0;

int service(int number){
  pid_t myPid;
  pid_t parentPid;

  myPid = getpid();
  parentPid = getppid();

  globalData++;

  printf("\nIn child service number %d, pid=%d, parent pid=%d, global data = %d\n", number, myPid, parentPid, globalData);

  sleep(8);

  myPid = getpid();
  parentPid = getppid();
  printf("\nafter sleep:");

  printf("In child service number %d, pid=%d, parent pid=%d, global data = %d\n", number, myPid, parentPid, globalData);
  return 0;
}


int main(int argc, char **argv){
  pid_t child;
  int i;

  for(i=0;i<10;i++){
    child=fork();
    if(child == 0){
      service(i);
      exit(EXIT_SUCCESS);
    }
    if(child < 0){
      printf("Problem creating a child\n");
      exit(EXIT_FAILURE);
    }
    printf("Main, created child %d, sleeping for a second.\n",i);
    sleep(1);
    printf("Main, after sleep, global data= %d\n", globalData);
  }

  printf("All children done, main exiting");
  return 0;

}
