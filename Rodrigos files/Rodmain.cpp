#include "mbed.h"
#include "CombatAce.h"
#include "Constants.h"
#include "Ship.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);

char P1_SPRITE[8] = {0x0,0x18,0xc,0x1b,0x1b,0xc,0x18,0x0};
char P2_SPRITE[8] = {0x0,0x18,0xc,0x1b,0x1b,0xc,0x18,0x0};
char DESTROYED_SPRITE[8] = {0x4,0x1b,0x15,0xe,0xe,0x15,0x1b,0x4};
char OBSTACLE_UP_SPRITE[8] = {0x1f,0x1f,0xe,0x4,0x15,0x1f,0xe,0x4};
char OBSTACLE_DOWN_SPRITE[8] = {0x4,0xe,0x1f,0x15,0x4,0xe,0x1f,0x1f};

Ticker updater;
Ticker renderer;

Semaphore updateSemaphore(0,1);
Semaphore renderSemaphore(0,1);
Semaphore btnSemaphore(0,1);

InterruptIn lu(D6, PullUp), ld(D7, PullUp), exitBtn(D8, PullUp), ru(D10, PullUp), rd(D11, PullUp); 

Direction direction = UP;

void upPressed() {
    btnSemaphore.release();
    direction = UP;
}

void downPressed() {
    btnSemaphore.release();
    direction = DOWN;
}

int main() {
    CombatAce game(1);
    
    lu.fall(&upPressed);
    ld.fall(&downPressed);
    ru.fall(&upPressed);
    rd.fall(&downPressed);
    
    while (1) {
        if (game.isGameOver()) {
            thread_sleep_for(1000);
            lcd.cls();
            lcd.printf("   Game Over!\n   Score: %d", game.getScore());
            delete &game;
        }
    }
}