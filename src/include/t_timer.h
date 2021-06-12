#ifndef TIMERAL_T_TIMER_H
#define TIMERAL_T_TIMER_H

#include <time.h>
#include <stdio.h>
#include "arg.h"

extern struct _argument_info* arg_inf;

/* delay: stop the execution for the specified miliseconds */
void delay(int ms);

/* display: print a formatted timer */
void display(void); 

#endif // TIMERAL_T_TIMER_H
