/*
 * Win32 platform driver that mocks a UART RX peripheral. Keys captured by
 * main.c's keyboard interrupt handler are queued here exactly like a real
 * UART RX ISR filling its receive FIFO.
 * There is no dedicated RX task: like real UART hardware, reception is
 * interrupt-driven, not polled.
 */

#include "taskUartRx.h"

#include "FreeRTOS.h"
#include "queue.h"

/* The queue stores up to eight bytes, mirroring a small hardware RX FIFO. */
#define taskUARTRX_QUEUE_LENGTH   8U

static QueueHandle_t xUartRxQueue;  // Holds bytes captured from the keyboard, as if received over UART

/* Create the queue that buffers simulated UART RX bytes. */
bool taskUartRx_init( void )
{
	xUartRxQueue = xQueueCreate( taskUARTRX_QUEUE_LENGTH, sizeof( uint8_t ) );
	return xUartRxQueue != NULL;
}

/* Dequeue one byte, the way a driver would read the UART RX data register. */
uint8_t UART_rx( void )
{
	uint8_t ucByte = 0U;

	if( xUartRxQueue != NULL )
	{
		/* Leave ucByte at 0 if the RX FIFO has nothing waiting. */
		( void ) xQueueReceive( xUartRxQueue, &ucByte, 0U );
	}

	return ucByte;
}

/* Called from main.c's keyboard interrupt handler, in place of a UART RX ISR. */
void taskUartRx_notifyKeyPress( int xKeyPress )
{
	uint8_t ucByte = ( uint8_t ) xKeyPress;

	if( xUartRxQueue != NULL )
	{
		/* Do not block the interrupt handler if a consumer is not keeping up. */
		( void ) xQueueSend( xUartRxQueue, &ucByte, 0U );
	}
}
