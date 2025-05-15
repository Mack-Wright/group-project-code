#pragma once
#include "TextLCD_CC.h"

const int UPS = 3;

extern char P1_SPRITE[8];
extern char P2_SPRITE[8];
extern char DESTROYED_SPRITE[8];
extern char OBSTACLE_UP_SPRITE[8];
extern char OBSTACLE_DOWN_SPRITE[8];

const int P1_ADDRESS = 1;
const int P2_ADDRESS = 2;
const int DESTROYED_ADDRESS = 3;
const int OBSTACLE_UP_ADDRESS = 4;
const int OBSTACLE_DOWN_ADDRESS = 5;

extern TextLCD lcd;

extern Ticker updater;
extern Ticker renderer;
extern Semaphore updateSemaphore;
extern Semaphore renderSemaphore;
extern Semaphore btnSemaphore;

extern InterruptIn left_up;
extern InterruptIn left_down;
extern InterruptIn console_button;
extern InterruptIn right_up;
extern InterruptIn right_down; 

enum Direction {
    UP, 
    DOWN
};

extern Direction direction;