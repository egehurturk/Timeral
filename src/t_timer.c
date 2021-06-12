#include "include/t_timer.h"

void delay(int ms) {
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock());
}

void display(void) {
    if (arg_inf->display_enabled) {
        printf("1.Start  2.Stop  3.Reset  4. End\n");       
        printf("***********************************\n");
        printf("            %d:%d:%d\n", arg_inf->hours, arg_inf->minutes, arg_inf->seconds);     
        printf("**********************************\n");
    }
}