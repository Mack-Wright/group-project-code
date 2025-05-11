#include "Obstacle.h"
#include "Constants.h"

Obstacle::Obstacle(int x) 
    : x{x}
{  
    srand(time(0));
    randPos();
}

void Obstacle::randPos() {
    y = rand() % 2;
}

int Obstacle::getX() {
    return x;
}

int Obstacle::getY() {
    return y;
}

void Obstacle::move() {
    --x;
    if (x<0) {
        x = 15;
        randPos();
    }
}

void Obstacle::draw() {
    lcd.locate(x, y);
    if (y == 1) {
        lcd.putc(OBSTACLE_DOWN_ADDRESS - 1);
    } else {
        lcd.putc(OBSTACLE_UP_ADDRESS - 1);
    }
}