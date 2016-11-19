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
 * @brief       test arduino adc capability
 *
 * @author      Laurent Navet <laurent.navet@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "periph/gpio.h"
#include "periph/timer.h"
#include "periph/adc.h"
#include "arduino_pinmap.h"
#include "thread.h"

#define TIMER_SPEED           (62500ul)  /* try to run at 62500 Hz */
#define TIMER_TIMEOUT         (100000ui) /* Timeout */

#define ADC_PIN			ADC_CHAN_4	/* ADC Pin number */


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
 /*   if(timer_set(TIMER_DEV(num), channel, timeout) == 0) {
     } else {
        puts("timer set failed !");
     }*/
    timer_set(TIMER_DEV(num), channel, timeout);
    timer_start(TIMER_DEV(num));
}


int main(void)
{
    puts("::Starting ADC example...\n");
    nbpulses = 0;

    start_timer(0,1,TIMER_TIMEOUT);

    if(adc_init(ADC_PIN) == -1) {
	    puts("adc init failed !\n");
    }

    while(1){
     if(toggle == 0) {
       toggle = 1;
       printf("Value[ADC%d] = %d \n", ADC_PIN, adc_sample(ADC_PIN, 0));
       start_timer(0,1,TIMER_TIMEOUT);
     }
    }

    puts("Ending ADC example !");
    return 0;
}
