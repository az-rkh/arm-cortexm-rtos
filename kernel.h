#include <stdint.h>

#define MAX_TASKS 3

extern int current_task;
extern int task_count;

typedef struct {
    uint32_t *sp;
    uint32_t stack[128];
} TCB;

void create_task(TCB *task, void (*entry)(void));

void scheduler(void);