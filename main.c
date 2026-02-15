#include <stdint.h>

#define UART0_DR ((volatile int32_t *) 0x4000C000)
#define UART0_FR ((volatile uint32_t *) 0x4000C018)


static void uart_puts(const char *s)
{
    while (*s) {
        while (*UART0_FR & (1 << 5));
        *UART0_DR = *s++;
    }
}

int main(void)
{
    uart_puts("RTOS kernel booted!\n");
    while (1);
}