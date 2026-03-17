#include <stdint.h>
#include "kernel.h"

#define UART0_DR ((volatile int32_t *) 0x4000C000)
#define UART0_FR ((volatile uint32_t *) 0x4000C018)

#define SYSTICK_CTRL ((volatile uint32_t *) 0xE000E010)
#define SYSTICK_RELOAD ((volatile uint32_t *) 0xE000E014)
#define SYSTICK_CURRENT ((volatile uint32_t *) 0xE000E018)
#define SYSTICK_CALIB ((volatile uint32_t *) 0xE000E01C)


static void uart_puts(const char *s)
{
    while (*s) {
        while (*UART0_FR & (1 << 5));
        *UART0_DR = *s++;
    }
}

void systick_handler(void)
{
    ticks++;
    *ICSR |= (1 << 28);
}

void create_task(TCB *task, void (*entry)(void))
{
    /* sp starts at the top of the stack, grows down */
    task->sp = &task->stack[128 - 16]; /* 16 registers, sp points to the bottom of the saved frame */

    /* hardware exception frame (pushed for exception entry) */
    task->stack[128 - 1] = 0x01000000; /* xPSR: thumb bit required */
    task->stack[128 - 2] = (uint32_t) entry; /* Program Counter. start here when task runs */
    task->stack[128 - 3] = 0xFFFFFFFD; /* LR: return to thread mode using PSP */
    task->stack[128 - 4] = 0;
    task->stack[128 - 5] = 0;
    task->stack[128 - 6] = 0;
    task->stack[128 - 7] = 0;
    task->stack[128 - 8] = 0;
}

void task_a(void)
{
    while (1) {
        uart_puts("task A\n");
        task_sleep(500);
    }
}

void task_b(void)
{
    while (1) {
        uart_puts("task B\n");
    }
}

int main(void)
{
    uart_puts("RTOS kernel booted!\n");

    create_task(&tasks[0], task_a);
    create_task(&tasks[1], task_b);
    task_count = 2;

    *SYSTICK_RELOAD = 16000000 / 1000 - 1;
    *SYSTICK_CURRENT = 0;
    *SYSTICK_CTRL = (1 << 2) | (1 << 1) | (1 << 0);

    kernel_start();
    while(1);
}