/* 
 * File:   timer.h
 * Author: root
 *
 * Created on May 6, 2018, 8:38 PM
 */

#ifndef TIMER_H
#define	TIMER_H

typedef struct {
    unsigned int firstByte;
    unsigned int secondByte;
} Timer;

void initTimer(Timer* timer);
char isExpired(Timer* timer, unsigned char a);
void update(Timer* timer);

#endif	/* TIMER_H */

