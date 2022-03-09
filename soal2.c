#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){
	pid_t child_id;
	int status;

	child_id = fork();

	if (child_id < 0){
		exit(EXIT_FAILURE);
	}

	if (child_id == 0) {
		char *argv[] = {"mkdir", "-p", "wlan_log", NULL};
		execv("/bin/mkdir", argv);
	} else {
		while((wait(&status)) > 0);
		char *argv[] = {"bash", "soal2.sh", NULL};
		execv("/bin/bash", argv);
	}

}
