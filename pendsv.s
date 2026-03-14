.syntax unified
.cpu cortex-m3
.thumb

.global pendsv_handler
.type pendsv_handler, %function

pendsv_handler:
    MRS R0, PSP /* 1. get current task's stack pointer */
    STMDB R0!, {R4-R11} /* 2. save r4-r11 onto current task's stack */

    /* 3. save PSP into tasks[current_task].sp */
    LDR R1, =tasks
    LDR R2, =current_task
    LDR R2, [R2]

    /* each TCB is (1 + 128) * 4 = 516 bytes */
    MOV R3, #516
    MUL R2, R2, R3
    ADD R1, R1, R2
    STR R0, [R1]

    PUSH {LR}
    BL scheduler
    POP {LR}

    /* 4. call scheduler() to update current_task */
    /* already called from SysTick so skip here */


    /* 5. load next task's sp into R0 */
    LDR R1, =tasks
    LDR R2, =current_task
    LDR R2, [R2]
    MOV R3, #516
    MUL R2, R2, R3
    ADD R1, R1, R2
    LDR R0, [R1]

    /* restore r4-r11 from next task's stack */
    LDMIA R0!, {R4-R11}

    /* 7. set PSP to next task's stack pointer */
    MSR PSP, R0

    /* return - CPU auto-restores r0-r3,r12,LR,PC,xPSR */
    BX LR