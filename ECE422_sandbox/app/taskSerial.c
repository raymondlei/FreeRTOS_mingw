/*
 * FreeRTOS task that receives simulated LED state changes through a queue and
 * reports them on the console.
 * A queue is a first-in, first-out mailbox managed by the FreeRTOS kernel.
 */

#include "taskSerial.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "taskUartRx.h"
#include "taskUartTx.h"

/* The queue stores up to eight values, each with the size of a bool. */
#define taskSERIAL_QUEUE_LENGTH       8U
#define taskSERIAL_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2U )
#define taskSERIAL_TASK_STACK_DEPTH   ( configMINIMAL_STACK_SIZE * 2U )
#define taskSERIAL_UART_POLL_PERIOD   pdMS_TO_TICKS( 20U )

static QueueHandle_t xLedStateQueue;  // Queue handle for LED state updates

static void prvSerialTask( void * pvParameters );

/* Create the LED-state queue and its console task. */
bool taskSerial_init( void )
{
	BaseType_t xTaskCreated;

	/* Create the queue before starting the task that consumes it. */
	/* The returned handle is how this file refers to the queue later. */
	xLedStateQueue = xQueueCreate( taskSERIAL_QUEUE_LENGTH, sizeof( bool ) );
	if( xLedStateQueue == NULL )
	{
		return false;
	}

	xTaskCreated = xTaskCreate( prvSerialTask,
								"Serial",
								taskSERIAL_TASK_STACK_DEPTH,
								NULL,
								taskSERIAL_TASK_PRIORITY,
								NULL );
	if( xTaskCreated != pdPASS )
	{
		/* Release the queue if its consumer could not be created. */
		vQueueDelete( xLedStateQueue );
		xLedStateQueue = NULL;
		return false;
	}

	return true;
}

/* Queue an LED state update without delaying the LED task. */
void taskSerial_sendLedState( bool ledOn )
{
	if( xLedStateQueue != NULL )
	{
		/* The LED task must remain periodic, so do not block when the queue is full. */
		( void ) xQueueSend( xLedStateQueue, &ledOn, 0U );
	}
}

/* Wait for LED updates, print each one, and echo any pending UART RX byte. */
static void prvSerialTask( void * pvParameters )
{
	( void ) pvParameters;  // Unused parameter
	bool ledOn;
	uint8_t ucRxByte;

	for( ; ; )
	{
		/* Bound the wait so a pending UART RX byte is not left unanswered. */
		if( xQueueReceive( xLedStateQueue, &ledOn, taskSERIAL_UART_POLL_PERIOD ) == pdPASS )
		{
			printf( "[Serial] LED is %s\r\n", ledOn ? "ON" : "OFF" );
			fflush( stdout );
		}

		/* UART_rx() returns 0 when the RX FIFO has no byte waiting. */
		ucRxByte = UART_rx();
		if( ucRxByte != 0U )
		{
			/* Echo the received byte back out over the mock UART TX line. */
			UART_tx( ucRxByte );
		}
	}
}
