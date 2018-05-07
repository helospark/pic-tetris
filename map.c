#include <stdio.h>
#include <stdlib.h>
#include "map.h"

unsigned char mapValueAt(int y, int x) {
    unsigned char row = map.rows[y];
    return (row & (0b00000001 << x)) >> x;
}

void setMapValue(int y, int x, unsigned char value) {
    if (value == 0) {
        map.rows[y] &= ~(0b00000001 << x);
    } else {
        map.rows[y] |= (0b00000001 << x);    
    }
}

char isRowFilledCompletely(int y) {
    return map.rows[y] == 0b11111111;
}

void moveRowsDown(int y) {
    for (int i = y; i > 0; --i) {
        map.rows[i] = map.rows[i - 1];
    }
    map.rows[0] = 0;
}
