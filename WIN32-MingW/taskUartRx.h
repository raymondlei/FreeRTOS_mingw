#ifndef TASK_UART_RX_H
#define TASK_UART_RX_H

#include <stdbool.h>
#include <stdint.h>

/* Create the queue that buffers simulated UART RX bytes. */
bool taskUartRx_init( void );

/* Non-blocking UART RX register read: dequeues one byte, or returns 0 if none is waiting. */
uint8_t UART_rx( void );

/* Feed one captured key press into the simulated UART RX path; called from main.c's keyboard ISR. */
void taskUartRx_notifyKeyPress( int xKeyPress );

#endif /* TASK_UART_RX_H */
