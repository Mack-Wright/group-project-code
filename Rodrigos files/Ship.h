#pragma once
#include "mbed.h"
#include "TextLCD_CC.h"

class Ship {

    private:
        int player;

        int x, y;

        int spriteAddress;

        bool destroyed;

    public:
        Ship(int player);

        void moveUp();
        void moveDown();

        int getX();
        int getY();
        
        void setSpriteAddress();

        bool isDestroyed();
        void destroy();

        void draw();
};
