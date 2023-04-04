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
    
    Timer0_OverflowCallbackRegister(Task_synch);

    Task_register(0, LED_TOGGLE_TIME, toggleLed);
    Task_register(0, 0, printWelcome);
    Task_register(1000, PRINT_COUNTER_TIME, printCounter);
    
    while(1)
    {
        Task_execute();
    }    
}