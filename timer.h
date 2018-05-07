#ifndef TIMER_H
#define	TIMER_H

// two byte counter on a single byte computer
typedef struct {
    unsigned int firstByte;
    unsigned int secondByte;
} Timer;

void initTimer(Timer* timer);

char hasTimerExpired(Timer* timer, unsigned char a);

void updateTimer(Timer* timer);

#endif	/* TIMER_H */

