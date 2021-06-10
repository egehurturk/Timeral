#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define RELEASE 0

#include "include/log.h"

int i;

/* daemon the process */  
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

    /* Open the log file */
    printf("INFO: logger file destination: %s\n", F_DEST);

    if (logger_init(D_TRACE, F_DEST) != 0) {
        fprintf(stderr, "error: Cannot initialize logger.\n");  
    } 
    /* Close all open file descriptors */
    int x;
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[]) {
    // cultivate the daemon environment
    skeleton_daemon();

    log_info("%s", "starting execution");

    int tty = 120;
    int delay = 3;

    while (tty >= 0) {
        sleep(delay);
        log_info("value of tty: %d", tty);
        tty -= delay;
    }
	int ret = logger_close();
    if (ret) 
        return EXIT_FAILURE;

#if !RELEASE
    sleep(30);
    ret = logger_destroy();
    if (ret)
        return EXIT_FAILURE;
#endif
    return 0;
}