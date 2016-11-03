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
 * @brief       Simple timer test
 *
 * @author      Laurent Navet <laurent.navet@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "periph/timer.h"
#define TIMER_SPEED           (62500ul) /* try to run with 1MHz */

#define TIMER_TIMEOUT         (100000ui)

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
    nbpulses = 0;
    puts("Starting Timer...");
    start_timer(0, 1, TIMER_TIMEOUT);

    while(1){
	if(toggle == 0) {
		toggle = 1;
		printf("pulse : %d \n", nbpulses);
		start_timer(0,1,TIMER_TIMEOUT);
	}

    }

    puts("Ending Blink example !");
    return 0;
}
