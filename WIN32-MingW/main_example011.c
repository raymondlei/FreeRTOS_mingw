/*
 * Functional FreeRTOS example based on the book's Example011/main.c.
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
} DataSource_t;

typedef struct
{
    uint8_t ucValue;
    DataSource_t eDataSource;
} Data_t;

static void prvSenderTask( void * pvParameters );
static void prvReceiverTask( void * pvParameters );
static void prvPrintString( const char * pcString );
static void prvPrintStringAndNumber( const char * pcString,
                                     uint8_t ucNumber );

static QueueHandle_t xExample011Queue = NULL;

static const Data_t xStructsToSend[ 2 ] =
{
    { 100U, eSender1 },
    { 200U, eSender2 }
};

/*-----------------------------------------------------------*/

void main_example011( void )
{
    BaseType_t xSender1Created;
    BaseType_t xSender2Created;
    BaseType_t xReceiverCreated;

    printf( "\r\nStarting FreeRTOS Example011 queue structure demo.\r\n\r\n" );

    xExample011Queue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Data_t ) );

    if( xExample011Queue != NULL )
    {
        xSender1Created = xTaskCreate( prvSenderTask,
                                       "Sender1",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xStructsToSend[ 0 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xSender2Created = xTaskCreate( prvSenderTask,
                                       "Sender2",
                                       mainTASK_STACK_DEPTH,
                                       ( void * ) &xStructsToSend[ 1 ],
                                       mainSENDER_TASK_PRIORITY,
                                       NULL );
        xReceiverCreated = xTaskCreate( prvReceiverTask,
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
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( mainQUEUE_WAIT_MS );

    for( ; ; )
    {
        xStatus = xQueueSendToBack( xExample011Queue, pvParameters, xTicksToWait );

        if( xStatus != pdPASS )
        {
            prvPrintString( "Could not send to the queue.\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void prvReceiverTask( void * pvParameters )
{
    Data_t xReceivedStructure;
    BaseType_t xStatus;

    ( void ) pvParameters;

    for( ; ; )
    {
        if( uxQueueMessagesWaiting( xExample011Queue ) != mainQUEUE_LENGTH )
        {
            prvPrintString( "Queue should have been full!\r\n" );
        }

        xStatus = xQueueReceive( xExample011Queue, &xReceivedStructure, 0U );

        if( xStatus == pdPASS )
        {
            if( xReceivedStructure.eDataSource == eSender1 )
            {
                prvPrintStringAndNumber( "From Sender 1 = ", xReceivedStructure.ucValue );
            }
            else
            {
                prvPrintStringAndNumber( "From Sender 2 = ", xReceivedStructure.ucValue );
            }
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
                                     uint8_t ucNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s%u\r\n", pcString, ( unsigned int ) ucNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
