/* 
 * File:   map.c
 * Author: root
 *
 * Created on May 6, 2018, 8:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

unsigned char at(int y, int x) {
    unsigned char row = map.rows[y];
    return (row & (0b00000001 << x)) >> x;
}

void set(int y, int x, unsigned char value) {
    if (value == 0) {
        map.rows[y] &= ~(0b00000001 << x);
    } else {
        map.rows[y] |= (0b00000001 << x);    
    }
}

char isFullySet(int y) {
    return map.rows[y] == 0b11111111;
}

void moveRowsDown(int y) {
    for (int i = y; i > 0; --i) {
        map.rows[i] = map.rows[i - 1];
    }
    map.rows[0] = 0;
}
