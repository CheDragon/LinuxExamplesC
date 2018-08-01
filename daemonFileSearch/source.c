#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

#define DAEMON_NAME "File check daemon"
#define LOG_FACILITY LOG_DAEMON
#define LOG_LEVEL LOG_ERR

#define WATCHED_FILE "/home/rene/Documents/IoT/Linux/daemonFileSearch/fileSearched.txt"

void demonize(){
	pid_t child;

	child = fork();
	if(child > 0){
		printf("Daemon running...\n");
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
	FILE * fileCheck;
	pid_t pid, ppid;
	int i = 0;
	int fileFound = 0;

	pid = getpid();
	ppid = getppid();

	openlog(DAEMON_NAME, LOG_PID, LOG_FACILITY);

	syslog(LOG_LEVEL, "Going daemon, pid = %d, parent pid %d\n", pid, ppid);

	demonize();

	ppid = getppid();

	do{
		syslog(LOG_LEVEL, "Checking for file\n");
		fileCheck = fopen (WATCHED_FILE,"r");
		sleep(1);
	}while( fileCheck == NULL );

	if( !unlink(WATCHED_FILE) ){
		syslog(LOG_LEVEL, "Found and deleted %s\n", WATCHED_FILE);
	} else {
		syslog(LOG_LEVEL, "Error deleting %s\n", WATCHED_FILE);
	}

	syslog(LOG_LEVEL, "Turning off\n");

	return 0;
}
