#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "include/log.h"

/* daemonify the process */  
static void skeleton_daemon() {
    pid_t pid;
    /* Fork off the parent process */
    pid = fork();
    
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    if (pid > 0)        /* parent process: ignore */
        exit(EXIT_SUCCESS);
    
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    /* Fork off for the second time*/
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Set new file permissions */
    umask(0);
    
    /* Change the working directory to the root directory */
    chdir("/");
    
    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close (x);
    }
    
    /* Open the log file */
    if (logger_init("/var/log/timeral.log")) {
        exit(EXIT_FAILURE);
    }  
}

int main(int argc, char *argv[]) {
    // cultivate the daemon environment
    skeleton_daemon();
     
    
    

    // int tty = 120;
    // int delay = 3;

    // while (tty > 0) {
    //     sleep(delay);
    //     tty -= delay;
    // }

    if (logger_close()) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}