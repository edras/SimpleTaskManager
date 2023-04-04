/*
 * File:   app.c
 * Author: Dr. Edras Pacola
 *
 * Created on 23. January 2023, 12:48
 */

#include "mcc_generated_files/system/system.h"
#include "app.h"
#include "tasks.h"

/* private variable */
uint8_t counter = 0;

void toggleLed(void)
{
    LED_Toggle();
}

void printCounter(void)
{
    printf("%d\r\n", counter++);
}

void printWelcome(void)
{
    printf("\033[2J");      //Clear screen
    printf("\033[0;0f");    //return cursor to 0,0
    printf("\033[?25l");    //disable cursor
    
    printf("------------------------------------------------------------------\r\n");
    printf("Simple Task Manager example                                       \r\n");
    printf("------------------------------------------------------------------\r\n");
    printf("\r\n");
}

