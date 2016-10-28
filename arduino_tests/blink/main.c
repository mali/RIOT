/*
 * Copyright (C) 2016 Laurent Navet <laurent.navet@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Blink application that shows how to blink a led
 *
 * @author      iLaurent Navet <laurent.navet@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "periph/gpio.h"
#include "periph/timer.h"
#include "arduino_pinmap.h"
#include "thread.h"

#define TIMER_SPEED           (62500ul)  /* try to run at 62500 Hz */
#define TIMER_TIMEOUT         (100000ui) /* Timeout */


char stack[THREAD_STACKSIZE_MAIN];

/* Timer stuff */
volatile int nbpulses;
volatile int toggle = 1;

static void timer_callback(void *arg, int chan)
{
    nbpulses++;
    toggle = 0;
}

void start_timer(int num, int channel, unsigned int timeout)
{
    if(timer_init(TIMER_DEV(num), TIMER_SPEED, timer_callback, NULL) == 0) {
        } else {
        puts("timer init failed !");
        }
    if(timer_set(TIMER_DEV(num), channel, timeout) == 0) {
     } else {
        puts("timer set failed !");
     }
    timer_start(TIMER_DEV(num));
}


int main(void)
{
    puts("Starting Blink example !");
    nbpulses = 0;

    /* init gpio pins */
    gpio_init(ARDUINO_PIN_3, GPIO_OUT);
    gpio_set(ARDUINO_PIN_3);
    gpio_init(ARDUINO_PIN_2, GPIO_OUT);
    gpio_clear(ARDUINO_PIN_2);

    start_timer(0,1,TIMER_TIMEOUT);

    while(1){
     if(toggle == 0) {
       toggle = 1;
       printf("pulse : %d \n", nbpulses);
       if(nbpulses > 40) break;
       gpio_toggle(ARDUINO_PIN_3);
       if(nbpulses % 2) gpio_toggle(ARDUINO_PIN_2);
       start_timer(0,1,TIMER_TIMEOUT);
     }
    }

    puts("Ending Blink example !");
    return 0;
}
