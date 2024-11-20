/*
 * Timer types and macros.
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

typedef struct Timer {
  uint8_t counter;
  uint8_t duration;
} Timer;

#define update_timer(t) ((--(t).counter) == 0)
#define reset_timer(t) (t).counter = (t).duration

#endif
