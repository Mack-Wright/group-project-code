#pragma once
#include "mbed.h"
#include "TextLCD_CC.h"

class Obstacle {
    private:
        int x, y;
        
        int spriteAddress;
    public:
        Obstacle(int x);

        void writeSprites();

        void randPos();
        
        int getX();
        int getY();

        void move();
        void draw();

};