#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv) {

	pid_t child;
	int i;
	int status;
	int sleeping;

	printf("Forking 10 children\n");

	for(i=0;i<10;i++) {
		child = fork();

    if(child == 0) {
			srand(time(NULL));
			sleeping = rand() % 10 + 10;
			printf("Child number %d and I sleep for %d. \n", i, sleeping);
			sleep(sleeping);
			if (sleeping % 2 == 0) {
				exit(EXIT_SUCCESS);
			} else {
				exit(EXIT_FAILURE);
			}
	  }
    sleep(1);
	}
  for(i=0;i<10;i++) {
    printf("Waiting for a child\n");
    child = wait(&status);
    printf("Child %d died, status %d\n", child, status);
  }
  return 0;
}
