#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//This creates a fifo file and logfile at /tmp

#define LOGFILE "/tmp/logfile"
#define FIFOFILE "/tmp/fifo"

void daemonize(){
	pid_t pid;

	pid = fork();

	if(pid < 0){
		printf("Cannot create a new process: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(pid > 0)
		exit(EXIT_SUCCESS);

	if(setsid() < 0){
		printf("Cannot create a new session: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(chdir("/") < 0){
		printf("Cannot change working directory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int main(int argc, char **argv) {
	int fifofd, n, logfile;
	char buffer[255];

	daemonize();

	logfile = open(LOGFILE, O_WRONLY | O_APPEND | O_CREAT, 0777);
	n = mkfifo(FIFOFILE, 0777);

	for(;;){
		fifofd = open(FIFOFILE, O_RDONLY);
		do {
			memset(buffer, 0, 255);
			n = read(fifofd, buffer, 255);
			if(n > 0){
				write(logfile, buffer, 255);
			}
		}while(n > 0);

		close(fifofd);
	}

	return 0;
}
