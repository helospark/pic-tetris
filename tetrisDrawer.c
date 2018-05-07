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
} RowData;

// Mapping of column in PORTB
// Means, that PORTB4 sets the first column, PORTB5 second, etc.
const unsigned char COLS[] = {4, 5, 3, 6, 0, 2, 1, 7};

// Mapping of the rows, ex. PORTC3 sets the first row, etc.
const RowData ROWS[] = {
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
// Multiplexing works by setting the value for the columns in PORTB, then turn on a single columns
// Repeat for all rows fast
// Using interrupts instead of update->render would clear up the display flickering a bit
// but this method seems fine most of the time
void turnOnARow(int rowIndex, unsigned char* shape) {
    unsigned char rowValue = 0;
    for (int i = 0; i < WIDTH; ++i) {
        rowValue |= (mapValueAt(rowIndex, i) & 1) << COLS[i];
    }
    if (shape != NULL) {
        for (int i = 0; i < CURRENT_BLOCK_WIDTH && (currentX + i) < WIDTH; ++i) {
            rowValue |= (shape[i] & 1) << COLS[currentX + i];
        }
    }
    clearAll(); // we could also remember the last row turned on, but simpler this way
    PORTB = rowValue;
    RowData rowData = ROWS[rowIndex];
    unsigned char result = 0b00000001 << rowData.index;
    unsigned char type = rowData.registerType;
    // Rows are splitted to separate ports, because of the limitation of the number
    // of bits per port.
    // Bits are inverted, since a LED is turned on if the bit is 0 on row 1 on column.
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

void drawMap() {
    for (int i = 0; i < HEIGHT; ++i) {
        unsigned char* shapeRow = NULL;
        if (hasCurrentShape && i >= currentY && i < currentY + CURRENT_BLOCK_HEIGHT) {
            shapeRow = currentShape[i - currentY];
        }
        turnOnARow(i, shapeRow);
    }
    __delay_us(400); // Make last row light up well
    PORTB = 0;
}