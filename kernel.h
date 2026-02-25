#include <stdint.h>

typedef struct {
    uint32_t *sp;
    uint32_t stack[128];
} TCB;
