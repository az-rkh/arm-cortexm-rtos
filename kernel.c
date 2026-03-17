#include "kernel.h"

TCB tasks[MAX_TASKS];
int current_task = 0;
int task_count = 0;
int kernel_started = 0;
volatile uint32_t ticks = 0;

void scheduler(void) 
{
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].state == TASK_SLEEPING && ticks >= tasks[i].wake_tick){
            tasks[i].state = TASK_READY;
        }
    }

    int next = (current_task + 1) % task_count;
    while (tasks[next].state != TASK_READY) {
        next = (next + 1) % task_count;
    }
    current_task = next;
}

void task_sleep(uint32_t ms)
{
    tasks[current_task].state = TASK_SLEEPING;
    tasks[current_task].wake_tick = ticks + ms;
    *ICSR |= (1 << 28);
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