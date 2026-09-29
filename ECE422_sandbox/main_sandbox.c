#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "app_main.h"
#include "taskLED.h"
#include "taskSerial.h"
#include "taskUartRx.h"
#include "taskUartTx.h"

/*
 * This function is the application entry point selected by the Win32 demo.
 * It creates all application objects before handing control to FreeRTOS.
 */
/* Initialize the sandbox tasks and start the FreeRTOS scheduler. */
void main_sandbox( void )
{
    /* One false result prevents the scheduler from starting after a failure. */
    bool status = false;
    
    printf( "\r\nStarting ECE422 LED and serial task demo.\r\n\r\n" );
    fflush( stdout );

    /* Initialize the queue/task example, LED task, timer example, and mock UART RX/TX tasks. */
    status = taskSerial_init();
    status &= taskLED_init();
    status &= app_main_init();
    status &= taskUartTx_init();
    status &= taskUartRx_init();
    
    if( status )
    {
        /* FreeRTOS now chooses which ready task should run. */
        vTaskStartScheduler();
    }

    printf( "Failed to create the sandbox tasks.\r\n" );
    fflush( stdout );

    /* Reaching here normally means that a required kernel object failed. */
    for( ; ; )
    {
    }
}
