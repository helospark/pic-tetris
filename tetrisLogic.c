#include <stdio.h>
#include <stdlib.h>
#include "tetrisLogic.h"
#include "map.h"

#define NUMBER_OF_SHAPES 7;

unsigned char shapes[][8] = {
    {
       0,1,0,0,
       1,1,1,0
    },
    {
       1,1,1,1,
       0,0,0,0
    },
    {
       1,1,0,0,
       0,1,1,0
    },
    {
       0,1,1,0,
       1,1,0,0
    },
    {
       1,1,0,0,
       1,1,0,0
    },
    {
       1,1,1,0,
       0,0,1,0
    },
    {
       1,1,1,0,
       1,0,0,0
    }
};


int lastUpdated;
int currentDelay;
char gameOver;

void initMap() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            set(i,j,0);
        }
    }
    gameOver = 0;
    lastUpdated = 0;
    currentDelay = 50;
    hasCurrentShape = 0;
}

char chooseShape() {
    int index = rand() % NUMBER_OF_SHAPES;
    char* shape = shapes[index];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentShape[i][j] = shape[i * 4 + j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        currentShape[2][i] = 0;
        currentShape[3][i] = 0;
    }
    hasCurrentShape = 1;
}

void findCoordinates() {
    currentY = 0;
    currentX = WIDTH / 2;    
}

char hasCollision() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentShape[i][j]) {
                char mapCoordinateX = currentX + j;
                char mapCoordinateY = currentY + i;
                if (mapCoordinateX < 0 || mapCoordinateX >= WIDTH) {
                    return 1;
                }
                if (mapCoordinateY < 0 || mapCoordinateY >= HEIGHT) {
                    return 1;
                }
                if (at(mapCoordinateY,mapCoordinateX)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void addShapeToMap() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentShape[i][j]) {
                char mapCoordinateX = currentX + j;
                char mapCoordinateY = currentY + i;
                set(mapCoordinateY, mapCoordinateX, 1);
            }
        }
    }
}

void rotateRight() {
    char newShape[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            newShape[j][3 - i] = currentShape[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentShape[i][j] = newShape[i][j];
        }
    }
}

void destroyRowIfNeeded() {
    for (int i = currentY; i < currentY + 4 && i < HEIGHT; ++i) {
        if (isFullySet(i)) {
            moveRowsDown(i);
            --currentDelay;
        }
    }
}

void play() {
    ++lastUpdated;
    if (lastUpdated > currentDelay) {
        if (!hasCurrentShape) {
            chooseShape();
            findCoordinates();
            if (hasCollision()) {
                gameOver = 1;
            }
            return;
        } else {
            ++currentY;
            if (hasCollision()) {
                --currentY;
                addShapeToMap();
                destroyRowIfNeeded();
                hasCurrentShape = 0;
            }
        }
        lastUpdated = 0;
    }
}

void moveLeft() {
    --currentX;
    if (hasCollision()) {
        ++currentX;
    }
}

void moveRight() {
    ++currentX;
    if (hasCollision()) {
        --currentX;
    }
}

void rotate() {
    rotateRight();
    if (hasCollision()) {
        for (int i = 0; i < 3; ++i) {
            rotateRight(); // restore shape
        }
    }
}

char hasGameEnded() {
    return gameOver;
}