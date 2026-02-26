#include "kernel.h"

TCB tasks[MAX_TASKS];
int current_task = 0;
int task_count = 0;


void scheduler(void) 
{
    current_task = (current_task + 1) % task_count;
}