/* 
 * File:   test.c
 * Author: black
 *
 * Created on May 20, 2017, 10:34 AM
 */
#define _XTAL_FREQ 16000000

#include <stdio.h>
#include <stdlib.h>


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

unsigned long value = 10;

#define PORTA_TYPE 0
#define PORTB_TYPE 1
#define PORTC_TYPE 2
#define PORTD_TYPE 3
#define PORTE_TYPE 4

const unsigned char COLS[] = {4,5,3,6,0,2,1,7};

typedef struct {
    unsigned char registerType;
    unsigned char index;
} Register;

// 4,6,1,7,
const Register ROWS[] = {
    {PORTC_TYPE, 3},
    {PORTA_TYPE, 0},
    {PORTA_TYPE, 1},
    {PORTD_TYPE, 1},
    {PORTD_TYPE, 7},
    {PORTD_TYPE, 0},
    {PORTC_TYPE, 2},
    {PORTD_TYPE, 6},
    {PORTD_TYPE, 4},
    {PORTC_TYPE, 4},
    {PORTD_TYPE, 3},
    {PORTC_TYPE, 6},
    {PORTD_TYPE, 2},
    {PORTC_TYPE, 7},
    {PORTD_TYPE, 5},
    {PORTC_TYPE, 5}
};

int delay = 30;

void turnOnPixel(int x, int y) {
    unsigned char colIndex = COLS[y];
    PORTB = 0b00000001 << colIndex;
    Register reg = ROWS[x];
    unsigned char result = 0b00000001 << reg.index;
    unsigned char type = reg.registerType;
    switch (type) {
        case PORTA_TYPE:
            PORTA = ~result;
            break;
        case PORTB_TYPE:
            PORTB = ~result;
            break;
        case PORTC_TYPE:
            PORTC = ~result;
            break;
        case PORTD_TYPE:
            PORTD = ~result;
            break;
    }
}

void clearAll() {
    PORTB = 0b00000000;
    PORTA = 0b11111111;
    PORTC = 0b11111111;
    PORTD = 0b11111111;
//    PORTE = 0b11111111;
}

int xC = 4;
int yC = 8;

void readBit() {
    int value = PORTEbits.RE0;
    if (value == 0) {
        --xC;
        if (xC < 0) {
            xC = 7;
        }
    }
    value = PORTEbits.RE2;
    if (value == 0) {
        ++yC;
        if (yC > 15) {
            yC = 15;
        }
    }
    value = PORTEbits.RE1;
    if (value == 0) {
        xC++;
        if (xC > 7) {
            xC = 0;
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
//    OSCCON = 0b11110000;
//    OSCTUNE = 0b11111111;
    ADCON1 = 0b11110111;
    
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0b00000111;
    
    PORTA = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
//    PORTE = 0b00000000;
    
    PORTB = 0b11111111;
    
    while (1) {
//        for (int i = 0; i < 16; ++i) {
//            for (int j = 0; j < 8; ++j) {
//                turnOnPixel(i, j);
//                __delay_ms(delay);
                readBit();
                turnOnPixel(yC, xC);
                __delay_ms(100);
                clearAll();
//            }
//        }
//        PORTA = 0b11111111;
//        PORTC = 0b11111111;
//        PORTD = 0b11111111;
//        PORTE = 0b11111111;

    }
    return (EXIT_SUCCESS);
}

