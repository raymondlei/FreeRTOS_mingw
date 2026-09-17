/*
 * Functional FreeRTOS example based on the attached Example024/main.c.
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
} Example024DataSource_t;

typedef struct
{
    uint8_t ucValue;
    Example024DataSource_t eDataSource;
} Example024Data_t;

static void prvExample024SenderTask( void * pvParameters );
static void prvExample024ReceiverTask( void * pvParameters );
static void prvExample024PrintString( const char * pcString );
static void prvExample024PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber );

static QueueHandle_t xExample024Queue = NULL;

static const Example024Data_t xExample024StructsToSend[ 2 ] =
{
    { 100U, eSender1 },
    { 200U, eSender2 }
};

/*-----------------------------------------------------------*/

void main_example024( void )
{
    BaseType_t xSender1Created;
    BaseType_t xSender2Created;
    BaseType_t xReceiverCreated;

    printf( "\r\nStarting FreeRTOS Example024 queue structure demo.\r\n\r\n" );

    xExample024Queue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Example024Data_t ) );

    if( xExample024Queue != NULL )
    {
        xSender1Created = xTaskCreate( prvExample024SenderTask,
                                       "Sender1",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample024StructsToSend[ 0 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xSender2Created = xTaskCreate( prvExample024SenderTask,
                                       "Sender2",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample024StructsToSend[ 1 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xReceiverCreated = xTaskCreate( prvExample024ReceiverTask,
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
            prvExample024PrintString( "Failed to create one or more tasks.\r\n" );
        }
    }
    else
    {
        prvExample024PrintString( "Failed to create the queue.\r\n" );
    }

    /* The scheduler only returns if its required resources could not be created. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvExample024SenderTask( void * pvParameters )
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( mainQUEUE_WAIT_MS );

    for( ; ; )
    {
        xStatus = xQueueSendToBack( xExample024Queue, pvParameters, xTicksToWait );

        if( xStatus != pdPASS )
        {
            prvExample024PrintString( "Could not send to the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample024ReceiverTask( void * pvParameters )
{
    Example024Data_t xReceivedStructure;
    BaseType_t xStatus;

    ( void ) pvParameters;

    for( ; ; )
    {
        if( uxQueueMessagesWaiting( xExample024Queue ) != mainQUEUE_LENGTH )
        {
            prvExample024PrintString( "Queue should have been full!\r\n" );
        }

        xStatus = xQueueReceive( xExample024Queue, &xReceivedStructure, 0U );

        if( xStatus == pdPASS )
        {
            if( xReceivedStructure.eDataSource == eSender1 )
            {
                prvExample024PrintStringAndNumber( "From Sender 1 = ", xReceivedStructure.ucValue );
            }
            else
            {
                prvExample024PrintStringAndNumber( "From Sender 2 = ", xReceivedStructure.ucValue );
            }
        }
        else
        {
            prvExample024PrintString( "Could not receive from the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample024PrintString( const char * pcString )
{
    portENTER_CRITICAL();
    {
        printf( "%s", pcString );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvExample024PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s%u\r\n", pcString, ( unsigned int ) ucNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
