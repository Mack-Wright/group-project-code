#include "prototypes.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);

Semaphore button_sem(0,1);
Semaphore console_sem(0,1);

volatile bool up_button = false;
volatile bool down_button = false;
volatile bool singleplayer = true;
volatile bool multiplayer = false;
volatile bool gamemode_wait = false;

void up_callback(){         // up button callback
    up_button = true;
    button_sem.release();
}

void down_callback(){   //  down button callback
    down_button = true;
    button_sem.release();
}

void main_menu_func(){      //  displays the starting sequence
    lcd.cls(); //clears the lcd screen
    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("   Flying Ace\n"); //displays flying ace on the LCD
    thread_sleep_for(2000);

    lcd.locate(0,0); //set cursor on row number 1 
    lcd.printf("> SinglePlayer"); //displays the select option for "singleplayer"
    lcd.locate(0,1);//set cursor on row 2
    lcd.printf("  Multi-Player"); //displays the select option for "multiplayer"
}

void button_func(){     // moves arrow up and down
    while(gamemode_wait == false){
        button_sem.acquire();

        if (up_button == true){
            lcd.locate(0,0); //set cursor on row number 1 
            lcd.printf("> SinglePlayer"); //displays the select option for "singleplayer"
            lcd.locate(0,1);//set cursor on row 2
            lcd.printf("  Multi-Player"); //displays the select option for "multiplayer"
            singleplayer = true;
            multiplayer = false;
        }

        else{
            if(down_button == true){
                lcd.locate(0,0); //set cursor on row number 1 
                lcd.printf("  SinglePlayer"); //displays the select option for "singleplayer"
                lcd.locate(0,1);//set cursor on row 2
                lcd.printf("> Multi-Player"); //displays the select option for "multiplayer"
                multiplayer = true;
                singleplayer = false;
            }
        }
        up_button = false;
        down_button = false;
    }
}

void selection_func(){      // selects the gamemode when console button is pressed

    if (gamemode_wait == false){
        gamemode_wait = true;
    }
    else{
        gamemode_wait = false;
        

        // gamemode exit function
        // delete game...

    }
    console_sem.release();
}

void singleplayer_game(){   //  loads the singleplayer mode

    for (int i=0; i<=2;i++){    // repeats 3 times
        lcd.cls(); //clears the lcd screen
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf("  SinglePlayer\n"); //displays the message Hello World on the LCD
        lcd.locate(5,1);
        lcd.printf("Mode\n");
        thread_sleep_for(500);  
    }
}

void multiplayer_game(){    //  loads the multiplayer mode
    for (int i=0; i<=2;i++){    // repeats 3 times
        lcd.cls(); //clears the lcd screen
        lcd.locate(0,0); //set cursor on row number 1 
        lcd.printf("  Multi-Player\n"); //displays the message Hello World on the LCD
        lcd.locate(5,1);
        lcd.printf("Mode\n");
        thread_sleep_for(500);  
    }
}  

void game_func(){   //  launches the gamemode
    console_sem.acquire();
    if (singleplayer == true){
        singleplayer_game();
    }
    else{
        if (multiplayer == true){
            multiplayer_game();
        }
    }
}