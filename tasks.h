/* 
 * File:   tasks.h
 * Author: Dr. Edras Pacola
 * Comments: Tasks running at defined period in milliseconds. How to use it:
 *    1. Call Task_synch each 1 ms
 *    2. Register the task at program beginning or when needed.
 *    3. Call Task_execute inside the main loop
 *    To register a task:
 *      a. define a delay to start the task. delay = 0 start task immediately.
 *      b. define a reload time to repeat the task. reload = 0 execute the task
 *         only once and the resources for the task are released.
 *      c. pass a function pointer with no parameter and now return as a task.
 *         i.e.: void doSomething(void)
 *      Example: execute doSomething immediately and repeat it each 50ms:
 *      - Task_register(0, 50, doSomething);
 *      Example: execute doSomething after 100 ms and repeat it each 200ms:
 *      - Task_register(100, 200, doSomething);
 *      Example: execute doSomething only once after 200 ms:
 *      - Task_register(200, 0, doSomething);
 * Revision history: 
 */

#ifndef TASKS_H
#define	TASKS_H

#include <xc.h> // include processor files - each processor file is guarded.  

// Error code return by Task_register if Task Manager queue is full
#define TASK_FULL 0xFF

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void Task_execute(void);
void Task_delete(uint8_t task_idx);
void Task_modify(uint8_t task_idx, uint16_t reload);
void Task_synch(void);
uint8_t Task_register(uint16_t delay, uint16_t reload, void (* task)(void));

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* TASKS_H */

