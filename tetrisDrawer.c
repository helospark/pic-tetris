#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"
#include "tetrisLogic.h"
#include "map.h"

#define PORTA_TYPE 0
#define PORTB_TYPE 1
#define PORTC_TYPE 2
#define PORTD_TYPE 3
#define PORTE_TYPE 4

typedef struct {
    unsigned char registerType;
    unsigned char index;
} Register;

const unsigned char COLS[] = {4,5,3,6,0,2,1,7};

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

void clearAll() {
    PORTA = 0b11111111;
    PORTC = 0b11111111;
    PORTD = 0b11111111;
}

void turnOnARow(int rowIndex, unsigned char* shape, int shapeStart) {
    unsigned char rowValue = 0;
    for (int i = 0; i < WIDTH; ++i) {
        rowValue |= (at(rowIndex, i) & 1) << COLS[i];
    }
    if (shape != NULL) {
        for (int i = 0; i < CURRENT_BLOCK_WIDTH && (currentX + i) < WIDTH; ++i) {
            rowValue |= (shape[i] & 1) << COLS[currentX + i];
        }
    }
    clearAll();
    PORTB = rowValue;
    Register reg = ROWS[rowIndex];
    unsigned char result = 0b00000001 << reg.index;
    unsigned char type = reg.registerType;
    switch (type) {
        case PORTA_TYPE:
            PORTA = ~result;
            break;
        case PORTC_TYPE:
            PORTC = ~result;
            break;
        case PORTD_TYPE:
            PORTD = ~result;
            break;
    }
}

void drawMap(char hasShape, int currentX, int currentY, unsigned char shape[CURRENT_BLOCK_HEIGHT][CURRENT_BLOCK_WIDTH]) {
    
    for (int i = 0; i < HEIGHT; ++i) {
        unsigned char* shapeRow = NULL;
        if (hasShape && i >= currentY && i < currentY + CURRENT_BLOCK_HEIGHT) {
            shapeRow = shape[i - currentY];
        }
        turnOnARow(i, shapeRow, currentX);
    }
    __delay_us(400);
    PORTB = 0;
}