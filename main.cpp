#include "mbed.h"
#include "TextLCD_CC.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);

InterruptIn exit_button(D6,PullUp);    //console button

InterruptIn left_up(D7,PullUp);     //left controller buttons
InterruptIn left_down(D8,PullUp);

InterruptIn right_up(D10,PullUp);   //right controller buttons
InterruptIn right_down(D11,PullUp);


Thread buttons;

Semaphore button_sem(0,1);      //semaphore to use with buttons


void arrow_change_func();
void poll_buttons();


void up_release();
void down_release();
void exit_release(); 

bool up = false;
bool down = false;
bool wait = false;
bool exit_key = false;

void main_menu_func();


// main() runs in its own thread in the OS
int main()
{
    buttons.start(poll_buttons);
  
    main_menu_func();
    arrow_change_func();
    
    while (true) {
        arrow_change_func();
    };
}

void up_release(){
    button_sem.release();
    up = true;
    
}
void down_release(){
    button_sem.release();
    down = true;
   
}


void exit_release(){
    button_sem.release();
    exit_key = true;
}

void arrow_change_func(){
    
    while (wait == false){
        button_sem.acquire();
        wait = true;

        if (up == true){
        lcd.cls(); //clears the lcd screen
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf(">Singleplayer"); //displays the select option for "Flying Ace"
        lcd.locate(0,1);//set cursor on row 2
        lcd.printf(" Multiplayer"); //displays the select option for "Combat Ace"
        
        
        }

        else{
        if (down == true){
            lcd.cls(); //clears the lcd screen
            lcd.locate(0,0); //set cursor on row number 1 
            lcd.printf(" Singleplayer"); //displays the select option for "Flying Ace"
            lcd.locate(0,1);//set cursor on row 2
            lcd.printf(">Multiplayer"); //displays the select option for "Combat Ace"
            
            }
    
        }
        wait = false;
        up = false;
        down = false;
    }
    
}

void main_menu_func(){
    lcd.cls(); //clears the lcd screen
    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("   Flying Ace\n"); //displays the message Hello World on the LCD
    thread_sleep_for(2000);

    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf(">Singleplayer"); //displays the select option for "Flying Ace"
    lcd.locate(0,1);//set cursor on row 2
    lcd.printf(" Multiplayer"); //displays the select option for "Combat Ace"
}

void poll_buttons(){
    left_up.fall(up_release);
    left_down.fall(down_release);

    exit_button.fall(exit_release);

    right_up.fall(up_release);
    right_down.fall(down_release);
}
