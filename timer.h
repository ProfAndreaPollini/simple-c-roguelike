//
// Created by profa on 17/04/2024.
//

#ifndef EXAMPLE_TIMER_H
#define EXAMPLE_TIMER_H

#include <stdbool.h>

typedef struct Timer {
    float time;
    float start;
    float end;
    bool loop;
} Timer;

Timer *timer_create(float start, float end, bool loop);
void timer_update(Timer *timer, float delta);
bool timer_expired(Timer *timer);
void timer_destroy(Timer *timer);

#endif //EXAMPLE_TIMER_H
