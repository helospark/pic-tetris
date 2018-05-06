/* 
 * File:   map.h
 * Author: root
 *
 * Created on May 6, 2018, 7:29 PM
 */

#include "global.h"

#ifndef MAP_H
#define	MAP_H

typedef struct {
    unsigned char rows[HEIGHT]; // WIDTH is explicitly 8
} Map;

Map map;

unsigned char at(int y, int x);
void set(int y, int x, unsigned char value);
char isFullySet(int y);
void moveRowsDown(int y);

#endif	/* MAP_H */

