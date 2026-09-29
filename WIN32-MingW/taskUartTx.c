/*
 * Win32 platform driver that mocks a UART TX peripheral: bytes written to
 * the simulated TX register are drained by this background task and
 * printed to the terminal, the way a real UART would shift them out onto
 * its TX pin.
 */

#include "taskUartTx.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* The queue stands in for the UART's TX holding register/FIFO. */
#define taskUARTTX_QUEUE_LENGTH       8U
#define taskUARTTX_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2U )
#define taskUARTTX_TASK_STACK_DEPTH   ( configMINIMAL_STACK_SIZE * 2U )

static QueueHandle_t xUartTxQueue;  // Holds bytes waiting to be "transmitted" to the terminal

static void prvUartTxTask( void * pvParameters );

/* Create the queue and background task that drain the simulated UART TX register. */
bool taskUartTx_init( void )
{
	BaseType_t xTaskCreated;

	xUartTxQueue = xQueueCreate( taskUARTTX_QUEUE_LENGTH, sizeof( uint8_t ) );
	if( xUartTxQueue == NULL )
	{
		return false;
	}

	xTaskCreated = xTaskCreate( prvUartTxTask,
								"UartTx",
								taskUARTTX_TASK_STACK_DEPTH,
								NULL,
								taskUARTTX_TASK_PRIORITY,
								NULL );
	if( xTaskCreated != pdPASS )
	{
		/* Release the queue if its consumer could not be created. */
		vQueueDelete( xUartTxQueue );
		xUartTxQueue = NULL;
		return false;
	}

	return true;
}

/* Write one byte into the simulated TX register, like a driver's UART write call. */
void UART_tx( uint8_t ucByte )
{
	if( xUartTxQueue != NULL )
	{
		/* Do not block the caller if the TX FIFO is momentarily full. */
		( void ) xQueueSend( xUartTxQueue, &ucByte, 0U );
	}
}

/* Drain the simulated TX register and print each byte as if shifted out on the wire. */
static void prvUartTxTask( void * pvParameters )
{
	uint8_t ucByte;

	( void ) pvParameters;

	for( ; ; )
	{
		if( xQueueReceive( xUartTxQueue, &ucByte, portMAX_DELAY ) == pdPASS )
		{
			putchar( ( int ) ucByte );
			fflush( stdout );
		}
	}
}
