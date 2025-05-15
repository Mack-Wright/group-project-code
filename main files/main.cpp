#include "mbed.h"
#include "FlyingAce.h"
#include "Constants.h"
#include "Ship.h"
#include "prototypes.h"

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

InterruptIn left_up(D8, PullUp), left_down(D9, PullUp),
console_button(D6, PullUp), right_up(D10, PullUp), right_down(D11, PullUp); 
Thread game;    //  separate thread for console button func

int main(){

    game.start(game_func);
    
    console_button.fall(selection_func);    //  polling buttons

    left_up.fall(up_callback);
    left_down.fall(down_callback);

    right_up.fall(up_callback);
    right_down.fall(down_callback);


    main_menu_func();
    button_func(); 
    
    while(true){ 
    }
}