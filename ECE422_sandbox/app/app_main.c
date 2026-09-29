/*
 * FreeRTOS software timer example that reports periodic timer callbacks on
 * the console. A software timer is managed by FreeRTOS's timer service task;
 * it does not create a new task for each timer.
 */

#include "app_main.h"

#include <stdint.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/*-----------------------------------------------------------*/

/* pdMS_TO_TICKS converts milliseconds into the configured tick units. */
#define appAUTO_RELOAD_TIMER_PERIOD    pdMS_TO_TICKS( 1000U )

/*-----------------------------------------------------------*/

static void prvPrintTimerEvent( const char * pcMessage );

/*-----------------------------------------------------------*/

/* Report each auto-reload timer expiration. */
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
	/* This example does not need data stored in the timer handle. */
	( void ) xTimer;
	/* Timer callbacks run in the FreeRTOS timer service task. */
	prvPrintTimerEvent( "Auto-reload timer" );
}

/*-----------------------------------------------------------*/

/* Create and start the sandbox software timer. */
bool app_main_init( void )
{
	TimerHandle_t xAutoReloadTimer;

	/* Create the timer before the scheduler starts. */
	/* pdTRUE makes this an auto-reload timer instead of a one-shot timer. */
	xAutoReloadTimer = xTimerCreate( "Periodic",
									 appAUTO_RELOAD_TIMER_PERIOD,
									 pdTRUE,
									 NULL,
									 prvAutoReloadTimerCallback );

	if( xAutoReloadTimer == NULL )
	{
		/* The timer service cannot report events without this timer. */
		return false;
	}

	/* Queue the start command; the timer service task processes it later. */
	return ( xTimerStart( xAutoReloadTimer, 0U ) == pdPASS );
}

/*-----------------------------------------------------------*/

/* Print a timer event and its current FreeRTOS tick count. */
static void prvPrintTimerEvent( const char * pcMessage )
{
	/* Keep each console message intact when other tasks are active. */
	/* The tick count is FreeRTOS time, not necessarily wall-clock time. */
	printf( "[Timer] %s callback at tick %llu\r\n",
			pcMessage,
			( uint64_t ) xTaskGetTickCount() );
	fflush( stdout );
}

/*-----------------------------------------------------------*/
