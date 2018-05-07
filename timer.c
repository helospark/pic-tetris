#include "timer.h"

void initTimer(Timer* timer) {
    timer->firstByte = 0;
    timer->secondByte = 0;
}

char hasTimerExpired(Timer* timer, unsigned char a) {
    return timer->secondByte >= a;
}

void updateTimer(Timer* timer) {
    timer->firstByte += 1;
    if (timer->firstByte >= 255) {
        timer->secondByte += 1;
        timer->firstByte = 0;
    }
}

