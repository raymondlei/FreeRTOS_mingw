/*
 * Functional FreeRTOS example based on the attached Example016/main.c.
 * This variant is adapted for the WIN32-MingW simulator project.
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#define mainQUEUE_LENGTH             ( 3U )
#define mainTASK_STACK_DEPTH         ( 1000U )
#define mainSENDER_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2 )
#define mainRECEIVER_TASK_PRIORITY   ( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_WAIT_MS            ( 100UL )

/*-----------------------------------------------------------*/

typedef enum
{
    eSender1,
    eSender2
} Example016DataSource_t;

typedef struct
{
    uint8_t ucValue;
    Example016DataSource_t eDataSource;
} Example016Data_t;

static void prvExample016SenderTask( void * pvParameters );
static void prvExample016ReceiverTask( void * pvParameters );
static void prvExample016PrintString( const char * pcString );
static void prvExample016PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber );

static QueueHandle_t xExample016Queue = NULL;

static const Example016Data_t xExample016StructsToSend[ 2 ] =
{
    { 100U, eSender1 },
    { 200U, eSender2 }
};

/*-----------------------------------------------------------*/

void main_example016( void )
{
    BaseType_t xSender1Created;
    BaseType_t xSender2Created;
    BaseType_t xReceiverCreated;

    printf( "\r\nStarting FreeRTOS Example016 queue structure demo.\r\n\r\n" );

    xExample016Queue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Example016Data_t ) );

    if( xExample016Queue != NULL )
    {
        xSender1Created = xTaskCreate( prvExample016SenderTask,
                                       "Sender1",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample016StructsToSend[ 0 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xSender2Created = xTaskCreate( prvExample016SenderTask,
                                       "Sender2",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample016StructsToSend[ 1 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xReceiverCreated = xTaskCreate( prvExample016ReceiverTask,
                                        "Receiver",
                                        mainTASK_STACK_DEPTH,
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
            prvExample016PrintString( "Failed to create one or more tasks.\r\n" );
        }
    }
    else
    {
        prvExample016PrintString( "Failed to create the queue.\r\n" );
    }

    /* The scheduler only returns if its required resources could not be created. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvExample016SenderTask( void * pvParameters )
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( mainQUEUE_WAIT_MS );

    for( ; ; )
    {
        xStatus = xQueueSendToBack( xExample016Queue, pvParameters, xTicksToWait );

        if( xStatus != pdPASS )
        {
            prvExample016PrintString( "Could not send to the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample016ReceiverTask( void * pvParameters )
{
    Example016Data_t xReceivedStructure;
    BaseType_t xStatus;

    ( void ) pvParameters;

    for( ; ; )
    {
        if( uxQueueMessagesWaiting( xExample016Queue ) != mainQUEUE_LENGTH )
        {
            prvExample016PrintString( "Queue should have been full!\r\n" );
        }

        xStatus = xQueueReceive( xExample016Queue, &xReceivedStructure, 0U );

        if( xStatus == pdPASS )
        {
            if( xReceivedStructure.eDataSource == eSender1 )
            {
                prvExample016PrintStringAndNumber( "From Sender 1 = ", xReceivedStructure.ucValue );
            }
            else
            {
                prvExample016PrintStringAndNumber( "From Sender 2 = ", xReceivedStructure.ucValue );
            }
        }
        else
        {
            prvExample016PrintString( "Could not receive from the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample016PrintString( const char * pcString )
{
    portENTER_CRITICAL();
    {
        printf( "%s", pcString );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvExample016PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s%u\r\n", pcString, ( unsigned int ) ucNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
