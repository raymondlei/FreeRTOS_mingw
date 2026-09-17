/*
 * Functional FreeRTOS example based on the book's Example010/main.c.
 * This variant is adapted for the WIN32-MingW simulator project.
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* Queue configuration from the original example. */
#define mainQUEUE_LENGTH             ( 5U )
#define mainSENDER_TASK_STACK_DEPTH  ( 1000U )
#define mainRECEIVER_TASK_PRIORITY   ( tskIDLE_PRIORITY + 2 )
#define mainSENDER_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define mainRECEIVE_WAIT_MS          ( 100UL )

/*-----------------------------------------------------------*/

static void prvSenderTask( void * pvParameters );
static void prvReceiverTask( void * pvParameters );
static void prvPrintString( const char * pcString );
static void prvPrintStringAndNumber( const char * pcString,
                                     int32_t lNumber );

static QueueHandle_t xExample010Queue = NULL;

/*-----------------------------------------------------------*/

void main_example010( void )
{
    BaseType_t xSender1Created;
    BaseType_t xSender2Created;
    BaseType_t xReceiverCreated;

    printf( "\r\nStarting FreeRTOS Example010 queue demo.\r\n\r\n" );

    xExample010Queue = xQueueCreate( mainQUEUE_LENGTH, sizeof( int32_t ) );

    if( xExample010Queue != NULL )
    {
        xSender1Created = xTaskCreate( prvSenderTask,
                                       "Sender1",
                                       mainSENDER_TASK_STACK_DEPTH,
                                       ( void * ) ( intptr_t ) 100,
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xSender2Created = xTaskCreate( prvSenderTask,
                                       "Sender2",
                                       mainSENDER_TASK_STACK_DEPTH,
                                       ( void * ) ( intptr_t ) 200,
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xReceiverCreated = xTaskCreate( prvReceiverTask,
                                        "Receiver",
                                        mainSENDER_TASK_STACK_DEPTH,
                                        NULL,
                                        mainRECEIVER_TASK_PRIORITY,
                                        NULL );

        if( ( xSender1Created == pdPASS ) &&
            ( xSender2Created == pdPASS ) &&
            ( xReceiverCreated == pdPASS ) )
        {
            vTaskStartScheduler();
        }
        else
        {
            prvPrintString( "Failed to create one or more tasks.\r\n" );
        }
    }
    else
    {
        prvPrintString( "Failed to create the queue.\r\n" );
    }

    /* The scheduler only returns if its required resources could not be created. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvSenderTask( void * pvParameters )
{
    const int32_t lValueToSend = ( int32_t ) ( intptr_t ) pvParameters;
    BaseType_t xStatus;

    for( ; ; )
    {
        xStatus = xQueueSendToBack( xExample010Queue, &lValueToSend, 0U );

        if( xStatus != pdPASS )
        {
            prvPrintString( "Could not send to the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvReceiverTask( void * pvParameters )
{
    int32_t lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( mainRECEIVE_WAIT_MS );

    ( void ) pvParameters;

    for( ; ; )
    {
        if( uxQueueMessagesWaiting( xExample010Queue ) != 0U )
        {
            prvPrintString( "Queue should have been empty!\r\n" );
        }

        xStatus = xQueueReceive( xExample010Queue, &lReceivedValue, xTicksToWait );

        if( xStatus == pdPASS )
        {
            prvPrintStringAndNumber( "Received = ", lReceivedValue );
        }
        else
        {
            prvPrintString( "Could not receive from the queue.\r\n" );
        }
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
/*-----------------------------------------------------------*/

static void prvPrintStringAndNumber( const char * pcString,
                                     int32_t lNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s%ld\r\n", pcString, ( long ) lNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
