#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

#define DAEMON_NAME "My test Daemon"
#define LOG_FACILITY LOG_DAEMON
#define LOG_LEVEL LOG_ERR

void demonize(){
	pid_t child;

	child = fork();
	if(child > 0){
		printf("Done creating child. Exiting\n");
		exit(EXIT_SUCCESS);
	}
	if(child < 0){
		printf("Error creating child: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(setsid() < 0){
		printf("Error in creating session: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(chdir("/") < 0){
		printf("Can't set wworking directory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	umask(0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}


int main(int argc, char **argv) {
	pid_t pid, ppid;
	int i = 0;

	pid = getpid();
	ppid = getppid();

	openlog(DAEMON_NAME, LOG_PID, LOG_FACILITY);

	syslog(LOG_LEVEL, "Going daemon, pid = %d, parent pid %d\n", pid, ppid);

	demonize();

	ppid = getppid();

	for(i=0;i<10;i++){
		syslog(LOG_LEVEL, "Round [%d]: Daemon pid=%d, parent pid= %d\n", i, pid, ppid);
		sleep(1);
	}

	syslog(LOG_LEVEL, "Turning off\n");

	return 0;
}
