# Simple Task Manager

This project demonstrates the use of Simple Task Manager. It is not intended to be a real scheduler nor a RTOS,
but a way to handle tasks that are called repeatedly after a specific delay has run out. 
This module does not handle cases where the function called blocks the execution or has consumed time and overlapped
other time slots from other registered functions.

## Software Architecture
A task module was implemented where the task_synch function should be called every 1 millisecond.

```
Timer0_OverflowCallbackRegister(Task_synch);
```

Tasks are registered, modified, or deleted as needed. Tasks are configured to be executed at a specific repeat rate or only once
by defining the values of DELAY and REPEAT_RATE. 

Task_register(DELAY, REPEAT_RATE, function_pointer);

```
Task_register(0,    200,  func_one);    // func_one() will be executed immediately and after every 200 milliseconds
Task_register(1000, 0,    func_two);    // func_two() will be executed after 1 second, and only once.
Task_register(1000, 1000, func_three);  // func_three() will be executed after 1 second, and after every 1s again.
```

To execute the Task module, insert the Task_execute function at the main loop:

```
    while(1)
    {
        Task_execute();
        ...
```

