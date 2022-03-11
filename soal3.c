#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

void delete(pid_t pid){
    DIR *dir;
    struct dirent *dp;
    char path[1000];

    dir = opendir("/tmp/trash/");

    if(!dir) return;

    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){

            // Construct new path from our base path
            strcpy(path, "/tmp/trash/");
            strcat(path, "/");
            strcat(path, dp->d_name);

            if(strcmp(dp->d_name, "stop.trash") == 0){
                // kill process
                kill(pid, SIGKILL);
                return;
            }else{
                remove(path);
                return;
            }
        }
    }
    
}

int main() {


    pid_t pid, sid; 

    pid = fork();

    //printf("%d", pid); // get pid

    if (pid < 0) {
      exit(EXIT_FAILURE);
    }


    if (pid > 0) {
      exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
      exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
      exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
      // Tulis program kalian di sini
      //system("echo \"Hai\" >> /home/wahid/sisop/modul2/latihan/test.txt");
        
        delete(pid);

        sleep(7);
    }
}
