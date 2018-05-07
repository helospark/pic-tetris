#include <xc.h>
#include "inputHandler.h"

#define LEFT_BIT_INDEX 0
#define RIGHT_BIT_INDEX 1
#define ROTATE_BIT_INDEX 2

// Button pressed logic is inverted, since button pulls pin to ground
#define BUTTON_PRESSED_STATE 0

int lastButtonStates[3];

int lastRead = 0;

unsigned char readUserInput() {
    char leftBit = PORTEbits.RE0;
    char rightBit = PORTEbits.RE1;
    char rotateBit = PORTEbits.RE2;
    char justPressedResult = NO_INPUT;
    char pressedAndHoldingResult = NO_INPUT;
    
    if (leftBit == BUTTON_PRESSED_STATE) {
        pressedAndHoldingResult = LEFT;
        if (lastButtonStates[LEFT_BIT_INDEX] != leftBit) {
            justPressedResult = LEFT;
        }
    }
    if (rightBit == BUTTON_PRESSED_STATE) {
        pressedAndHoldingResult = RIGHT;
        if (lastButtonStates[RIGHT_BIT_INDEX] != rightBit) {
            justPressedResult = RIGHT;
        }
    }
    if (rotateBit == BUTTON_PRESSED_STATE) {
        pressedAndHoldingResult = ROTATE;
        if (lastButtonStates[ROTATE_BIT_INDEX] != rotateBit) {
            justPressedResult = ROTATE;
        }
    }
    
    lastButtonStates[LEFT_BIT_INDEX] = leftBit;
    lastButtonStates[RIGHT_BIT_INDEX] = rightBit;
    lastButtonStates[ROTATE_BIT_INDEX] = rotateBit;
    
    // if the user just pressed the button, act immediately
    if (justPressedResult != NO_INPUT) {
        lastRead = 0;
        return justPressedResult;
    }
    ++lastRead;
    
    // otherwise send it once per 20 updates
    if (pressedAndHoldingResult != NO_INPUT && lastRead > 30) {
        lastRead = 0;
        return pressedAndHoldingResult;
    }
    
    return NO_INPUT;
}

