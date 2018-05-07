#include <stdio.h>
#include <stdlib.h>
#include "tetrisLogic.h"
#include "map.h"

#define NUMBER_OF_SHAPES 7
#define SHAPE_HOLDER_HEIGHT 2
#define SHAPE_HOLDER_WIDTH 4

unsigned char shapes[NUMBER_OF_SHAPES][8] = {
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
       0,1,1,0,
       0,1,1,0
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
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
            currentShape[i][j] = 0;
        }
    }
    
    int index = rand() % NUMBER_OF_SHAPES;
    char* shape = shapes[index];
    int centerY = (CURRENT_BLOCK_HEIGHT - SHAPE_HOLDER_HEIGHT) / 2;
    int centerX = (CURRENT_BLOCK_WIDTH - SHAPE_HOLDER_WIDTH) / 2;
    for (int i = 0; i < SHAPE_HOLDER_HEIGHT; ++i) {
        for (int j = 0; j < SHAPE_HOLDER_WIDTH; ++j) {
            currentShape[i + centerY][j + centerX] = shape[i * SHAPE_HOLDER_WIDTH + j];
        }
    }
    hasCurrentShape = 1;
}

char findFirstRowWithValue() {
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
            if (currentShape[i][j]) {
                return i;
            }
        }
    }
    return 0;
}

void findCoordinates() {
    currentY = findFirstRowWithValue() * -1;
    currentX = (WIDTH - CURRENT_BLOCK_WIDTH) / 2;    
}

char hasCollision() {
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
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
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
            if (currentShape[i][j]) {
                char mapCoordinateX = currentX + j;
                char mapCoordinateY = currentY + i;
                set(mapCoordinateY, mapCoordinateX, 1);
            }
        }
    }
}

void rotateRight() {
    char newShape[CURRENT_BLOCK_HEIGHT][CURRENT_BLOCK_WIDTH];
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
            newShape[j][CURRENT_BLOCK_WIDTH - 1 - i] = currentShape[i][j];
        }
    }
    for (int i = 0; i < CURRENT_BLOCK_HEIGHT; ++i) {
        for (int j = 0; j < CURRENT_BLOCK_WIDTH; ++j) {
            currentShape[i][j] = newShape[i][j];
        }
    }
}

void destroyRowIfNeeded() {
    for (int i = currentY; i < currentY + CURRENT_BLOCK_HEIGHT && i < HEIGHT; ++i) {
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