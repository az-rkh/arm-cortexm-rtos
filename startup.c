#define SRAM_START (0x20000000U)
#define SRAM_SIZE (64U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)


#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;


extern int main(void);

void default_handler(void)
{
    while (1);
}

void reset_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mm_fault_handler(void) __attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));


__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,
    (uint32_t *)&reset_handler,
    (uint32_t *)&nmi_handler,
    (uint32_t *)&hard_fault_handler,
    (uint32_t *)&mm_fault_handler,
    (uint32_t *)&bus_fault_handler,
    (uint32_t *)&usage_fault_handler,
    0, 0, 0, 0,
    (uint32_t *)&svcall_handler,
    (uint32_t *)&debug_monitor_handler,
    0,
    (uint32_t *)&pendsv_handler,
    (uint32_t *)&systick_handler,
};


void reset_handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;
    
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;
    
    main();

    while(1);
}