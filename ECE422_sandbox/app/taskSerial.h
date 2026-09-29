#ifndef TASK_SERIAL_H
#define TASK_SERIAL_H

#include <stdbool.h>

/* Create the queue and task that print LED state changes. */
bool taskSerial_init( void );

/* Send one LED state value to the serial task. */
void taskSerial_sendLedState( bool ledOn );

#endif /* TASK_SERIAL_H */
