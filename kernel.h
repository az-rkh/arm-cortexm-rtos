#include <stdint.h>

#define MAX_TASKS 3
#define TASK_READY 0
#define TASK_SLEEPING 1

extern int current_task;
extern int task_count;
extern int kernel_started;

typedef struct {
    uint32_t *sp;
    uint32_t stack[128];
    uint8_t state;
    uint32_t wake_tick;
} TCB;
extern TCB tasks[MAX_TASKS];
void create_task(TCB *task, void (*entry)(void));

void scheduler(void);
void kernel_start(void);