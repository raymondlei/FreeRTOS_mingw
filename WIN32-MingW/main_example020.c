/*
 * Functional FreeRTOS example based on the attached Example020/main.c.
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
} Example020DataSource_t;

typedef struct
{
    uint8_t ucValue;
    Example020DataSource_t eDataSource;
} Example020Data_t;

static void prvExample020SenderTask( void * pvParameters );
static void prvExample020ReceiverTask( void * pvParameters );
static void prvExample020PrintString( const char * pcString );
static void prvExample020PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber );

static QueueHandle_t xExample020Queue = NULL;

static const Example020Data_t xExample020StructsToSend[ 2 ] =
{
    { 100U, eSender1 },
    { 200U, eSender2 }
};

/*-----------------------------------------------------------*/

void main_example020( void )
{
    BaseType_t xSender1Created;
    BaseType_t xSender2Created;
    BaseType_t xReceiverCreated;

    printf( "\r\nStarting FreeRTOS Example020 queue structure demo.\r\n\r\n" );

    xExample020Queue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Example020Data_t ) );

    if( xExample020Queue != NULL )
    {
        xSender1Created = xTaskCreate( prvExample020SenderTask,
                                       "Sender1",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample020StructsToSend[ 0 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xSender2Created = xTaskCreate( prvExample020SenderTask,
                                       "Sender2",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xExample020StructsToSend[ 1 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xReceiverCreated = xTaskCreate( prvExample020ReceiverTask,
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
            prvExample020PrintString( "Failed to create one or more tasks.\r\n" );
        }
    }
    else
    {
        prvExample020PrintString( "Failed to create the queue.\r\n" );
    }

    /* The scheduler only returns if its required resources could not be created. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvExample020SenderTask( void * pvParameters )
{
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( mainQUEUE_WAIT_MS );

    for( ; ; )
    {
        xStatus = xQueueSendToBack( xExample020Queue, pvParameters, xTicksToWait );

        if( xStatus != pdPASS )
        {
            prvExample020PrintString( "Could not send to the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample020ReceiverTask( void * pvParameters )
{
    Example020Data_t xReceivedStructure;
    BaseType_t xStatus;

    ( void ) pvParameters;

    for( ; ; )
    {
        if( uxQueueMessagesWaiting( xExample020Queue ) != mainQUEUE_LENGTH )
        {
            prvExample020PrintString( "Queue should have been full!\r\n" );
        }

        xStatus = xQueueReceive( xExample020Queue, &xReceivedStructure, 0U );

        if( xStatus == pdPASS )
        {
            if( xReceivedStructure.eDataSource == eSender1 )
            {
                prvExample020PrintStringAndNumber( "From Sender 1 = ", xReceivedStructure.ucValue );
            }
            else
            {
                prvExample020PrintStringAndNumber( "From Sender 2 = ", xReceivedStructure.ucValue );
            }
        }
        else
        {
            prvExample020PrintString( "Could not receive from the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvExample020PrintString( const char * pcString )
{
    portENTER_CRITICAL();
    {
        printf( "%s", pcString );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvExample020PrintStringAndNumber( const char * pcString,
                                               uint8_t ucNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s%u\r\n", pcString, ( unsigned int ) ucNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
