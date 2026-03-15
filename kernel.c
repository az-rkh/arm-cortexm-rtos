#include "kernel.h"

TCB tasks[MAX_TASKS];
int current_task = 0;
int task_count = 0;
int kernel_started = 0;

void scheduler(void) 
{
    current_task = (current_task + 1) % task_count;
}

void task_sleep(uint32_t ms)
{
    tasks[current_task].state = TASK_SLEEPING;
    tasks[current_task].wake_tick;
}

void kernel_start(void)
{
    *((volatile uint32_t *)0xE000ED20) |= (0xFF << 16);

    current_task = MAX_TASKS - 1;

    // copy MSP to PSP — valid initial stack, will be discarded
    __asm volatile (
        "MRS R0, MSP\n"
        "MSR PSP, R0\n"
    );

    // switch to PSP
    __asm volatile (
        "MRS R0, CONTROL\n"
        "ORR R0, R0, #2\n"
        "MSR CONTROL, R0\n"
        "ISB\n"
    );

}