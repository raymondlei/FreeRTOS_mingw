/*
 * Functional FreeRTOS example based on the book's Example013/main.c.
 * This variant is adapted for the WIN32-MingW simulator project.
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* The periods assigned to the one-shot and auto-reload timers. */
#define mainONE_SHOT_TIMER_PERIOD       pdMS_TO_TICKS( 3333UL )
#define mainAUTO_RELOAD_TIMER_PERIOD    pdMS_TO_TICKS( 500UL )

/*-----------------------------------------------------------*/

static void prvOneShotTimerCallback( TimerHandle_t xTimer );
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );
static void prvPrintStringAndNumber( const char * pcString,
                                     TickType_t xNumber );

/*-----------------------------------------------------------*/

void main_example013( void )
{
    TimerHandle_t xAutoReloadTimer;
    TimerHandle_t xOneShotTimer;
    BaseType_t xTimer1Started;
    BaseType_t xTimer2Started;

    printf( "\r\nStarting FreeRTOS Example013 timer demo.\r\n\r\n" );

    /* Create the one-shot software timer. */
    xOneShotTimer = xTimerCreate( "OneShot",
                                  mainONE_SHOT_TIMER_PERIOD,  //in milliseconds
                                  pdFALSE,
                                  NULL,
                                  prvOneShotTimerCallback );

    /* Create the auto-reload software timer. */
    xAutoReloadTimer = xTimerCreate( "AutoReload",
                                     mainAUTO_RELOAD_TIMER_PERIOD,  //in milliseconds
                                     pdTRUE,
                                     NULL,
                                     prvAutoReloadTimerCallback );

    if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
    {
        /* Start both timers before starting the scheduler. */
        xTimer1Started = xTimerStart( xOneShotTimer, 0U );
        xTimer2Started = xTimerStart( xAutoReloadTimer, 0U );

        if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
        {
            vTaskStartScheduler();
        }
        else
        {
            printf( "Failed to start one or more software timers.\r\n" );
            fflush( stdout );
        }
    }
    else
    {
        printf( "Failed to create one or more software timers.\r\n" );
        fflush( stdout );
    }

    /* The scheduler only returns if its required resources could not be created. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
    ( void ) xTimer;
    prvPrintStringAndNumber( "One-shot timer callback executing", xTaskGetTickCount() );
}
/*-----------------------------------------------------------*/

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    ( void ) xTimer;
    prvPrintStringAndNumber( "Auto-reload timer callback executing", xTaskGetTickCount() );
}
/*-----------------------------------------------------------*/

static void prvPrintStringAndNumber( const char * pcString,
                                     TickType_t xNumber )
{
    portENTER_CRITICAL();
    {
        printf( "%s: %llu\r\n", pcString, ( uint64_t ) xNumber );
        fflush( stdout );
    }
    portEXIT_CRITICAL();
}
