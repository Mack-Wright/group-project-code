#include "mbed.h"
#include "TextLCD_CC.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);

InterruptIn left_up(D7,PullUp);     //left controller buttons
InterruptIn left_down(D8,PullUp);


Thread button_function;
Semaphore button_sem(0,1);      //semaphore to use with buttons


void arrow_change_func();
void up_release();
void down_release();
void enter_release();
void exit_release(); 

bool up = false;
bool down = false;
bool enter = false;
bool exit_key = false;

void main_menu_func();

// main() runs in its own thread in the OS
int main()
{
    button_function.start(arrow_change_func);
    
    left_up.fall(up_release);

    left_down.fall(down_release);
    
    main_menu_func();
    
    while (true) {};
}

void up_release(){
    button_sem.release();
    up = true;
}
void down_release(){
    button_sem.release();
    down = true;
}
void enter_release(){
    button_sem.release();
    enter = true;
}
void exit_release(){
    button_sem.release();
    exit_key = true;
}

void arrow_change_func(){
    button_sem.acquire();
    if (up == true){
        lcd.cls(); //clears the lcd screen
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf("> Flying Ace"); //displays the select option for "Flying Ace"
        lcd.locate(0,1);//set cursor on row 2
        lcd.printf("  Combat Ace"); //displays the select option for "Combat Ace"
        up = false;
    }

    if (down == true){
        lcd.cls(); //clears the lcd screen
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf("  Flying Ace"); //displays the select option for "Flying Ace"
        lcd.locate(0,1);//set cursor on row 2
        lcd.printf("> Combat Ace"); //displays the select option for "Combat Ace"
        down = false;
    }
}

void main_menu_func(){
    lcd.cls(); //clears the lcd screen
    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("   Gaming Ace\n"); //displays the message Hello World on the LCD
    thread_sleep_for(2000);

    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("> Flying Ace"); //displays the select option for "Flying Ace"
    lcd.locate(0,1);//set cursor on row 2
    lcd.printf("  Combat Ace"); //displays the select option for "Combat Ace"
}