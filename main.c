/* 
 * File:   test.c
 * Author: black
 *
 * Created on May 20, 2017, 10:34 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include "tetrisDrawer.h"
#include "tetrisLogic.h"
#include "inputHandler.h"

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
#include "timer.h"

int main(int argc, char** argv) {
    ADCON1 = 0b11110111;
    
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0b00000111;
    
    PORTA = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    
    PORTB = 0b11111111;
    
    Timer timer;
    initTimer(&timer);

    initMap();
    
    while (1) {
        play();
        unsigned char input = readInput();
        switch (input) {
            case LEFT:
                moveLeft();
                break;
            case RIGHT:
                moveRight();
                break;
            case TURN:
                rotate();
                break;
        }
        drawMap(hasCurrentShape, currentX, currentY, currentShape);
        if (hasGameEnded()) {
            update(&timer);
            if (isExpired(&timer, 3)) {
                initMap();
                initTimer(&timer);
            }
        }
    }
    return (EXIT_SUCCESS);
}

