/* 
 * File:   tetrisLogic.h
 * Author: root
 *
 * Created on May 6, 2018, 4:37 PM
 */
#include "global.h"
#ifndef TETRISLOGIC_H
#define	TETRISLOGIC_H

int currentX = WIDTH / 2;
int currentY = 0;
char currentShape[4][4];
char hasCurrentShape = 0;


void initMap();
void play();
char hasGameEnded();
void rotate();
void moveLeft();
void moveRight();

#endif	/* TETRISLOGIC_H */

