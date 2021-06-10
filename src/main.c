#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "include/log.h"
#include "include/t_timer.h"

#define RELEASE 0
#define LS      99
#define STRT    100
#define RST     101
#define STP     102
#define DSP     103

struct _ArgumentInfo {
    float seconds;
    float minutes;
    float hours;
    int display_enabled;
    int stopwatch;
};

struct _ArgumentInfo* arg_inf;

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

static void print_usage(void) {
    printf("usage: timeral <command> [options] \n");
    printf("command should be one of: \n");
    printf("\to \"start\" (without quotation marks)\n");
    printf("\to \"stop\" (without quotation marks)\n");
    printf("\to \"ls\" (without quotation marks)\n");
    printf("\to \"reset\" (without quotation marks)\n");
    printf("\to \"display\" (without quotation marks)\n");
    printf("\n");
    printf("Options for start command: \n");
    printf("\to [-s|--seconds] [second_value] [-m|--minutes] [minute value] [-h|--hours] [hour value] [-d|--display]\n");
    printf("\t\to -s or --seconds followed by the value will set the timer's seconds duration. \n");
    printf("\t\to -m or --minutes followed by the value will set the timer's minutes duration. \n");
    printf("\t\to -h or --hours followed by the value will set the timer's hours duration. \n");
    printf("\t\to -d or --display to display the timer in the current terminal (as opposed to being a daemon), \n");
    printf("\t\to If any of the time indicators is not present, the timer will act as a stopwatch, which means that it will count up the seconds until it is stopped.\n");
    printf("Arguments for stop, display, and reset commands \n");
    printf("\to <ID>\n");
    printf("\t\to the ID is required to stop or reset the timer. IDs of timers can be retrieved by listing the active timers.\n");
    printf("\n\n");
    printf("Examples: \n");
    printf("$ timeral start -h 1 -m 30 -d\t\t\t	--> will start a 1 hours 30 minutes timer that is not a daemon timer (runs in background). \n");
    printf("$ timeral stop 34032\t\t\t		--> will stop the timer with the ID `34032`.\n");
    printf("$ timeral ls\t\t\t  			--> will list all active timers.\n");
    printf("$ timeral display 34032\t\t\t		--> will display the timer in the terminal.\n");
    printf("$ timeral reset 34032\t\t\t		--> will display the timer in the terminal.\n");
}

static int validate_args(int argc, char* argv[]) {
    arg_inf = malloc(sizeof(struct _ArgumentInfo));
    // validate the arguments for START command
    int s_present = 0, m_present = 0, h_present = 0, d_present = 0;
    if (argc == 2) 
        arg_inf->stopwatch = 1;
    for (int i = 2; i < argc; i++) {
        char *current = argv[i];
        if (strcmp(current, "--seconds") == 0 || strcmp(current, "-s") == 0)  {
            if (s_present >= 1) return 1;
            s_present++;
            arg_inf->seconds = atof(argv[++i]);
        }
        else if (strcmp(current, "-m") == 0 || strcmp(current, "--minutes") == 0) {
            if (m_present >= 1) return 1;
            m_present++;
            arg_inf->minutes = atof(argv[++i]);
        }
        else if (strcmp(current, "-h") == 0 || strcmp(current, "--hours") == 0) {
            if (h_present >= 1) return 1;
            h_present++;
            arg_inf->hours = atof(argv[++i]);
        }
        else if (strcmp(current, "-d") == 0 || strcmp(current, "--display") == 0) {
            if (d_present >= 1) return 1;
            arg_inf->display_enabled = ++d_present;
        } 
        else return 1;

    }
    return 0;
}

static int process_i(int argc, char *argv[]) {
    /* 
    general:
    $ timeral <COMMAND> <OPTIONS>

    start:
    $ timeral start [-s|--seconds] 
            [-m|--minutes] [-h|--hours] [-d|--display]
    Explanation:
        if start does not have any options, the program
        will act like a stopwatch. Else, it will count
        down the time.

    list daemon timers:
    $ timeral ls

    stop timers:
    $ timeral stop <ID>

    reset timers:
    $ timeral reset <ID>

    display timer:
    $ timeral display <ID>
    */
    if (argc <= 1)
        return 1;
    
    char *command = argv[1];

    if (strcmp(command, "start") == 0 && argc <= 9) {
        int code = validate_args(argc, argv);
        if (code)
            return 1;
        return STRT;
    } else if (strcmp(command, "ls") == 0 && argc == 2) {
        return LS;
    } else if (strcmp(command, "reset") == 0 && argc == 3) {
        return RST;
    } else if (strcmp(command, "stop") == 0 && argc == 3) {
        return STP;
    } else if (strcmp(command, "display") == 0 && argc == 3) {
        return DSP;
    } else {
        return 1;
    }
    return 0;
}



static int check_ID(char *ID) {
    return 1;
}

int main(int argc, char *argv[]) {
    int code = process_i(argc, argv);
    if (code == 1) {
        print_usage();
        return 1;
    }

    switch (code) {
    case LS: 
        /* list timers */
        printf("list is called...\n");
        break;
    case STP:
        if (check_ID(argv[2])) {
            /* do things */
        }
        printf("stop is called...\n");
        /* kill the process */
        break;
    case DSP:
        if (check_ID(argv[2])) {
            /* do things */
        }
        /* display the timer */
        printf("display is called...\n");
        break;
    case RST:
        if (check_ID(argv[2])) {
            /* do things */
        }
        /* reset the timer */
        printf("reset is called...\n");
        break;
    case STRT:
        printf("seconds: %.1f\n", arg_inf->seconds);
        printf("minutes: %.1f\n", arg_inf->minutes);
        printf("hours: %.1f\n", arg_inf->hours);
        printf("display enabled: %d\n", arg_inf->display_enabled);
        printf("stopwatch enabled: %d\n", arg_inf->stopwatch);
        /* start a timer */
        break;
    }

    // cultivate the daemon environment
    // skeleton_daemon();

    // log_info("%s", "starting execution");

   
	// int ret = logger_close();
    // if (ret) 
        // return EXIT_FAILURE;
    // return 0;
}





   			