#include "mbed.h"
#include "TextLCD_CC.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);

InterruptIn exit_button(D6,PullUp);    //console button

InterruptIn left_up(D8,PullUp);     //left controller buttons
InterruptIn left_down(D9,PullUp);


Semaphore button_sem(0,1);

void button_func();
void main_menu_func();

void up_callback();
void down_callback();

bool up_button = false;
bool down_button = false;

int main(){

    left_up.fall(up_callback);
    left_down.fall(down_callback);

    main_menu_func();

    while(true){
        button_func();
    }
}


void up_callback(){
    up_button = true;
    button_sem.release();
}

void down_callback(){
    down_button = true;
    button_sem.release();
}

void main_menu_func(){
    lcd.cls(); //clears the lcd screen
    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("   Flying Ace\n"); //displays the message Hello World on the LCD
    thread_sleep_for(2000);

    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("> Singleplayer"); //displays the select option for "Flying Ace"
    lcd.locate(0,1);//set cursor on row 2
    lcd.printf("  Multiplayer"); //displays the select option for "Combat Ace"
}

void button_func(){
    button_sem.acquire();

    if (up_button == true){
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf("> Singleplayer"); //displays the select option for "Flying Ace"
        lcd.locate(0,1);//set cursor on row 2
        lcd.printf("  Multiplayer"); //displays the select option for "Combat Ace"
    }
    else{
        if(down_button == true){
            lcd.locate(0,0); //set cursor on row number 1 
            lcd.printf("  Singleplayer"); //displays the select option for "Flying Ace"
            lcd.locate(0,1);//set cursor on row 2
            lcd.printf("> Multiplayer"); //displays the select option for "Combat Ace"
        }
    }
    up_button = false;
    down_button = false;
}