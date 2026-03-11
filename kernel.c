#include "kernel.h"

TCB tasks[MAX_TASKS];
int current_task = 0;
int task_count = 0;


void scheduler(void) 
{
    current_task = (current_task + 1) % task_count;
}


void kernel_start(void)
{
    *((volatile uint32_t *)0xE00ED20) |= (0xFF << 16);

    __asm volatile ("MSR PSP, %0" :: "r" (tasks[0].sp));

    __asm volatile (
        "MRS R0, CONTROL\n"
        "ORR R0, R0, #2\n"
        "MSR CONTROL, R0\n"
        "ISB\n"
    );
}