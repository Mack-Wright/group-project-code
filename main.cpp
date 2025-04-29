#include "mbed.h"
#include "prototypes.h"

InterruptIn console_button(D6,PullUp);    //    console button

InterruptIn left_up(D8,PullUp);     //  left controller buttons
InterruptIn left_down(D9,PullUp);

Thread game;    //  separate thread for console button func

int main(){

    game.start(game_func);
    
    console_button.fall(selection_func);    //  polling buttons
    left_up.fall(up_callback);
    left_down.fall(down_callback);

    main_menu_func();
    button_func(); 
    
    while(true){ 
    }
}
