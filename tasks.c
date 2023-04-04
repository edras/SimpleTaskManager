/*
 * File:   tasks.c
 * Author: Dr. Edras Pacola
 *
 * Created on January 19, 2023, 11:49 AM
 */

#include <xc.h>
#include <stddef.h>
#include "tasks.h"

#define MAX_TASKS 10

typedef struct {
    uint16_t delay;
    uint16_t reload;
    uint8_t trigger;
    void (*taskHandler)(void);
} Task;

Task tasks[MAX_TASKS];

/**
 * Task Synchronization
 * 
 * This function should be called each 1 millisecond.
 * Each registered Task has a delay counter and a reload value. 
 * By calling Task_synch, delay of each Task will be decreased, 
 * and when reaching zero, the trigger flag of the Task is set to 1
 * and delay receives the reload value.
 */
void Task_synch(void)
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler)
        {
            if(tasks[i].delay > 0) tasks[i].delay--;
            if(tasks[i].delay == 0)
            {
                tasks[i].delay = tasks[i].reload;
                tasks[i].trigger = 1;
            }            
        }
    }
}

/**
 * Task Register
 * 
 * This function should be called to register a new Task.
 * Tasks will be executed after "delay" has run out and 
 * the task will be repeated at a "repeat" rate. This function
 * returns the index of the Task or TASK_FULL if it is not
 * possible to add more tasks.
 * 
 * @param delay     The time to wait up to the execution of the Task
 * @param reload    The repeat rate of the Task, i.e.: each 1000 ms
 * @param task      The function callback pointer to be called as "task"
 * @return          The Task index or TASK_FULL
 */
uint8_t Task_register(uint16_t delay, uint16_t reload, void (* task)(void))
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler == NULL)
        {
            tasks[i].delay = delay;
            tasks[i].reload = reload;
            tasks[i].trigger = 0;
            tasks[i].taskHandler = task;
            return i;
        }
    }
    return TASK_FULL;
}

/**
 * Task Delete
 * 
 * Remove the Task from the queue and inhibit task the next task execution
 * 
 * @param task_idx  The index of the task (obtained after task registering).
 */
void Task_delete(uint8_t task_idx)
{
    if(task_idx < MAX_TASKS)
    {
        tasks[task_idx].taskHandler = NULL;
        tasks[task_idx].trigger = 0;        
    }        
}

/**
 * Task Modify
 * 
 * Modify the repeat rate of the task
 * 
 * @param task_idx  The index of the task (obtained after task registering).
 * @param reload    The new repeat rate in milliseconds
 */
void Task_modify(uint8_t task_idx, uint16_t reload)
{
    if(task_idx < MAX_TASKS)
    {
        tasks[task_idx].reload = reload;
    }        
}

/**
 * Task Execute
 * 
 * This function should be called frequently so the triggered tasks may be executed.
 * The function runs through over the queue of tasks and if the trigger flat is set,
 * the function callback pointer is called if it is a valid one. 
 * If reload is zero, the task will not be repeated and is erased from the queue.
 */
void Task_execute(void)
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler && tasks[i].trigger)
        {
            tasks[i].trigger = 0;
            // if we have a valid function pointer, call the function
            if(tasks[i].taskHandler)
            {
                tasks[i].taskHandler();
            }            
            // if it is a single-run task, erase the function pointer
            if(tasks[i].reload == 0)
            {
                tasks[i].taskHandler = NULL;
            }
        }
    }    
}