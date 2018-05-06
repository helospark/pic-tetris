#include "timer.h"

void initTimer(Timer* timer) {
    timer->firstByte = 0;
    timer->secondByte = 0;
}

char isExpired(Timer* timer, unsigned char a) {
    return timer->secondByte >= a;
}

void update(Timer* timer) {
    timer->firstByte += 1;
    if (timer->firstByte >= 100) {
        timer->secondByte += 1;
        timer->firstByte = 0;
    }
}

