/*
 * Functional FreeRTOS example based on the book's Example004/main.c.
 * This variant is adapted for the WIN32-MingW simulator project.
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Task configuration from the original example. */
#define mainEXAMPLE_TASK_STACK_DEPTH    1000U
#define mainTASK_1_PRIORITY             ( tskIDLE_PRIORITY + 1 )
#define mainTASK_2_PRIORITY             ( tskIDLE_PRIORITY + 2 )
#define mainPRINT_DELAY_MS              pdMS_TO_TICKS( 250UL )

/*-----------------------------------------------------------*/

static void prvTaskFunction( void * pvParameters );
static void prvPrintString( const char * pcString );

/* Strings passed into each task as task parameters. */
static char pcTextForTask1[] = "Task 1 is running\r\n";
static char pcTextForTask2[] = "Task 2 is running\r\n";

/*-----------------------------------------------------------*/

void main_functional_example( void )
{
    BaseType_t xTask1Created;
    BaseType_t xTask2Created;

    printf( "\r\nStarting functional task example (Example004).\r\n\r\n" );

    xTask1Created = xTaskCreate( prvTaskFunction,
                                 "Task 1",
                                 mainEXAMPLE_TASK_STACK_DEPTH,
                                 ( void * ) pcTextForTask1,
                                 mainTASK_1_PRIORITY,
                                 NULL );

    xTask2Created = xTaskCreate( prvTaskFunction,
                                 "Task 2",
                                 mainEXAMPLE_TASK_STACK_DEPTH,
                                 ( void * ) pcTextForTask2,
                                 mainTASK_2_PRIORITY,
                                 NULL );

    if( ( xTask1Created == pdPASS ) && ( xTask2Created == pdPASS ) )
    {
        vTaskStartScheduler();
    }
    else
    {
        printf( "Failed to create one or more tasks.\r\n" );
        fflush( stdout );
    }

    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvTaskFunction( void * pvParameters )
{
    const char * pcTaskName = ( const char * ) pvParameters;

    for( ; ; )
    {
        prvPrintString( pcTaskName );
        vTaskDelay( mainPRINT_DELAY_MS );
    }
}
/*-----------------------------------------------------------*/

static void prvPrintString( const char * pcString )
{
    portENTER_CRITICAL();
    {
        printf( "%s", pcString );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
