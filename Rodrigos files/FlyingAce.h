#pragma once
#include "mbed.h"
#include "Constants.h"
#include "Ship.h"
#include "Obstacle.h"


class FlyingAce {
    private:
        Ship ship;
        Obstacle obstacle; //, o2, o3, o4;
        Thread updateThread, renderThread, btnThread;
        int score;
        bool gameOver;
    public:

        FlyingAce(int playerNumber);
        
        void writeSprites();
        void startGameloop();

        void update();
        void render();

        void updateThreadFunc();
        void renderThreadFunc();
        void btnThreadFunc();

        int getScore();
        bool isGameOver();
};