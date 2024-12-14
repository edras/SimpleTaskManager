 /*
 * MAIN - Simple Task Manager
 * 
 * @file main.c
 * 
 * @brief This is an example implementation of the Simple Task Manager.
 *
 * @version 1.0.0
*/

#include "mcc_generated_files/system/system.h"
#include "tasks.h"
#include "app.h"

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable(); 
    
    // Register Task_synch to be called every 1ms
    Timer0_OverflowCallbackRegister(Task_synch);

    // Register tasks to be executed
    // time_to_start, repeat_time, function
    Task_register(0, LED_TOGGLE_TIME, toggleLed);
    Task_register(0, 0, printWelcome);
    
    // when registering a task, you get an index for the task
    uint8_t counterTask = Task_register(5000, PRINT_COUNTER_TIME, printCounter);
    
    //with the index, you can modify the task execution rate, i.e., each 2s
    Task_modify(counterTask, 2000);
    
    //or delete the task
    Task_delete(counterTask);
    
    // start the counter after 2s and repeat each 1s 
    Task_register(5000, PRINT_COUNTER_TIME, printCounter);
    
    while(1)
    {
        Task_execute();
    }    
}