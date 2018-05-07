// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "tetrisDrawer.h"
#include "tetrisLogic.h"
#include "inputHandler.h"

void initializeRegisters() {
    ADCON1 = 0b11110111; // All ports are digital
    
    // Make everything an output
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    // Except PORTE.
    // Note the other bits, as they are controlling an unrelated feature on 16f877a, that must be turned off
    TRISE = 0b00000111;
    
}

int main(int argc, char** argv) {
    Timer restartTimer; // wait with the restart

    initializeRegisters();
    initTimer(&restartTimer);
    initTetris();
    
    while (1) {
        updateTetris();
        unsigned char input = readUserInput();
        switch (input) {
            case LEFT:
                moveCurrentShapeLeft();
                break;
            case RIGHT:
                moveCurrentShapeRight();
                break;
            case ROTATE:
                rotateCurrentShape();
                break;
        }
        drawMap(hasCurrentShape, currentX, currentY, currentShape);
        if (hasGameEnded()) {
            updateTimer(&restartTimer);
            if (hasTimerExpired(&restartTimer, 3)) {
                initTetris();
                initTimer(&restartTimer);
            }
        }
    }
    return (EXIT_SUCCESS);
}

