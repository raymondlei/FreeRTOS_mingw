#ifndef TASK_UART_TX_H
#define TASK_UART_TX_H

#include <stdbool.h>
#include <stdint.h>

/* Create the task and queue that mock a UART TX register draining to the terminal. */
bool taskUartTx_init( void );

/* Non-blocking UART TX register write: queues one byte for the background task to transmit. */
void UART_tx( uint8_t ucByte );

#endif /* TASK_UART_TX_H */
