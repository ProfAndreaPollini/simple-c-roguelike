//
// Created by profa on 17/04/2024.
//
#include "timer.h"

#include <stdlib.h>


Timer *timer_create(float start, float end, bool loop) {
    Timer *timer = (Timer*) malloc(sizeof(Timer));
    timer->start = start;
    timer->end = end;
    timer->time = start;
    timer->loop = loop;
    return timer;
}

void timer_destroy(Timer *timer) {
    free(timer);
}

void timer_update(Timer *timer, float delta) {
    timer->time += delta;

}

bool timer_expired(Timer *timer) {
    bool expired = timer->time > timer->end;
    if (timer->end < timer->start) {
        expired = timer->time < timer->end;
    }

    if (expired && timer->loop) {
        timer->time = timer->start;
    }

    return expired;
}

