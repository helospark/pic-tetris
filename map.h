#include "global.h"

#ifndef MAP_H
#define	MAP_H

typedef struct {
    unsigned char rows[HEIGHT]; // WIDTH is implicitly 8
} Map;

Map map;

unsigned char mapValueAt(int y, int x);
void setMapValue(int y, int x, unsigned char value);
char isRowFilledCompletely(int y);
void moveRowsDown(int y);

#endif	/* MAP_H */

