/* 
 * File:   inputHandler.c
 * Author: root
 *
 * Created on May 6, 2018, 4:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "inputHandler.h"

#define LEFT_BIT_INDEX 0
#define RIGHT_BIT_INDEX 1
#define TURN_BIT_INDEX 2

int lastButtonStates[3];

int lastRead = 0;

unsigned char readInput() {
    char leftBit = PORTEbits.RE0;
    char rightBit = PORTEbits.RE1;
    char turnBit = PORTEbits.RE2;
    char result = NO_INPUT; // just pressed result
    char pressedKey = NO_INPUT; // holding it
    
    if (leftBit == 0) {
        pressedKey = LEFT;
        if (lastButtonStates[LEFT_BIT_INDEX] != leftBit) {
            result = LEFT;
        }
    }
    if (rightBit == 0) {
        pressedKey = RIGHT;
        if (lastButtonStates[RIGHT_BIT_INDEX] != rightBit) {
            result = RIGHT;
        }
    }
    if (turnBit == 0) {
        pressedKey = TURN;
        if (lastButtonStates[TURN_BIT_INDEX] != turnBit) {
            result = TURN;
        }
    }
    
    lastButtonStates[LEFT_BIT_INDEX] = leftBit;
    lastButtonStates[RIGHT_BIT_INDEX] = rightBit;
    lastButtonStates[TURN_BIT_INDEX] = turnBit;
    
    if (result != NO_INPUT) {
        lastRead = 0;
        return result;
    }
    ++lastRead;
    if (pressedKey != NO_INPUT && lastRead > 30) {
        lastRead = 0;
        return pressedKey;
    }
    
    
    return NO_INPUT;
}

