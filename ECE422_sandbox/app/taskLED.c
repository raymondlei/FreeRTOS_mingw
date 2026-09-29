/*
 * FreeRTOS task that toggles the simulated LED and reports its state to the
 * serial task once per second.
 * The LED is simulated: its state is sent to another task instead of driving
 * a physical GPIO pin.
 */

#include "taskLED.h"

#include "FreeRTOS.h"
#include "task.h"

#include "taskSerial.h"

/*-----------------------------------------------------------*/

#define taskLED_TASK_PRIORITY       ( tskIDLE_PRIORITY + 1U )
#define taskLED_TASK_STACK_DEPTH    configMINIMAL_STACK_SIZE
#define taskLED_TOGGLE_PERIOD       pdMS_TO_TICKS( 1000U )

/*-----------------------------------------------------------*/

static void prvLedTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* Create the task that controls the simulated LED state. */
bool taskLED_init( void )
{
	/* Report whether the LED task was successfully allocated and created. */
	/* xTaskCreate arguments are: function, name, stack, parameter, priority, handle. */
	return xTaskCreate( prvLedTask,
						"LED",
						taskLED_TASK_STACK_DEPTH,
						NULL,
						taskLED_TASK_PRIORITY,
						NULL ) == pdPASS;
}

/* Toggle the LED state and publish it once per second. */
static void prvLedTask( void * pvParameters )
{
	/* DelayUntil keeps a regular period even if the task takes some time to run. */
	TickType_t xLastWakeTime = xTaskGetTickCount();
	bool ledOn = false;

	( void ) pvParameters;

	/* Keep toggles aligned to the intended period rather than task runtime. */
	for( ; ; )
	{
		/* Send the simulated LED state to the serial task for reporting. */
		ledOn = !ledOn;
		taskSerial_sendLedState( ledOn );
		/* This task sleeps here and gives other ready tasks time to run. */
		vTaskDelayUntil( &xLastWakeTime, taskLED_TOGGLE_PERIOD );
	}
}
