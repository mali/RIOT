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
 * @brief       xtimer that test xtimer support
 *
 * @author      Laurent Navet <laurent.navet@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "periph/gpio.h"
#include "periph/timer.h"
#include "arduino_pinmap.h"
#include "thread.h"
#include "xtimer.h"

#define TIMER_SPEED           (10000ul) /* try to run with 1MHz */


char stack[THREAD_STACKSIZE_MAIN];

int nbpulses;

static void timer_callback(void *arg, int chan)
{
    nbpulses++;
}

void start_timer(int num)
{
    nbpulses = 0;
    timer_init(TIMER_DEV(num), TIMER_SPEED, timer_callback, NULL);
    timer_set(TIMER_DEV(num), 1, 1000);
    timer_start(TIMER_DEV(num));
}

void * thread_one(void *arg)
{
    gpio_init(ARDUINO_PIN_2, GPIO_OUT);
    puts("Led 2 On ");
    gpio_set(ARDUINO_PIN_2);
    return NULL;
}

int main(void)
{
    int i=0;
    puts("Starting xtimer example !");

    puts("Starting Timer...");

    while(i++ < 50){
        xtimer_sleep(8000);
	printf("nbpulses : %d \n", i);
    };

    puts("Ending Blink example !");
    return 0;
}
