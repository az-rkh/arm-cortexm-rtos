#include <stdint.h>

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

static void systick_handler(void)
{

}

int main(void)
{
    uart_puts("RTOS kernel booted!\n");
    while (1);
}