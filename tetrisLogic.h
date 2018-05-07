#include "global.h"
#ifndef TETRISLOGIC_H
#define	TETRISLOGIC_H

int currentX;
int currentY;
char currentShape[CURRENT_BLOCK_HEIGHT][CURRENT_BLOCK_WIDTH];
char hasCurrentShape = 0;


void initTetris();

void updateTetris();

char hasGameEnded();

void rotateCurrentShape();

void moveCurrentShapeLeft();

void moveCurrentShapeRight();

#endif	/* TETRISLOGIC_H */

