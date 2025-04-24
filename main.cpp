#include "mbed.h"
#include "TextLCD_CC.h"


InterruptIn exit_button(D6,PullUp);    //console button

InterruptIn left_up(D7,PullUp);     //left controller buttons
InterruptIn left_down(D8,PullUp);
InterruptIn left_enter(D9,PullUp);

InterruptIn right_up(D10,PullUp);   //right controller buttons
InterruptIn right_down(D11,PullUp);
InterruptIn right_enter(D12,PullUp);

Thread button_function;

Semaphore button_sem(0,1);      //semaphores to use with buttons

void sem_release();
void token_release();

void up_release();
void down_release();
void enter_release();
void exit_release();

bool up = false;
bool down = false;
bool enter = false;
bool exit_key = false;

// main() runs in its own thread in the OS
int main()
{
    button_function.start(token_release);

    left_up.fall(up_release);
    right_up.fall(up_release);

    left_down.fall(down_release);
    right_down.fall(down_release);

    left_enter.fall(enter_release);
    right_enter.fall(enter_release);

    exit_button.fall(exit_release);


    while (true){};
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

void token_release(){

}