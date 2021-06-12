#ifndef TIMERAL_TIMER_LIST_H
#define TIMERAL_TIMER_LIST_H


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "t_timer.h"
#include "arg.h"

struct timer_list {
    struct _argument_info** data;
    int size;    
    int ptr;
};

void timer_list_create(struct timer_list* list, int size);
void timer_list_add(struct timer_list* list, struct _argument_info* data);
void timer_list_add(struct timer_list* list, struct _argument_info* data);

#endif // TIMERAL_TIMER_LIST_H
