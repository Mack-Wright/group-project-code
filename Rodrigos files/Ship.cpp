#include "Ship.h"
#include "Constants.h"

Ship::Ship(int player)
    : player{player}
    , x{0}
    , y{0}
    , destroyed{0}
{
}

void Ship::moveUp() {
    y = 0;
}

void Ship::moveDown() { 
    y = 1;
}

int Ship::getX() {
    return x;
}

int Ship::getY() {
    return y;
}

void Ship::setSpriteAddress() {
    if (destroyed) spriteAddress = DESTROYED_ADDRESS;
    else if (player == 1) spriteAddress = P1_ADDRESS;
    else if (player == 2) spriteAddress = P2_ADDRESS;
}

bool Ship::isDestroyed() {
    return destroyed;
}

void Ship::destroy() {
    destroyed = 1;
}

void Ship::draw() {
    lcd.locate(x, y);
    if (destroyed) lcd.putc(DESTROYED_ADDRESS - 1);
    else if (player == 1) lcd.putc(P1_ADDRESS - 1);
    else if (player == 2) lcd.putc(P2_ADDRESS - 1);
}