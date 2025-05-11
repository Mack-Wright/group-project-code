#include "CombatAce.h"
#include "Constants.h"

CombatAce::CombatAce(int playerNumber)
    : ship{1}
    , obstacle{15}
    //, o2{7}
    //, o3{11}
    //, o4{15}
    , score{0}
    , gameOver{0}
{   
    writeSprites();
    startGameloop();
}

void CombatAce::writeSprites() {
    lcd.writeCustomCharacter(P1_SPRITE, P1_ADDRESS);
    lcd.writeCustomCharacter(P2_SPRITE, P2_ADDRESS);
    lcd.writeCustomCharacter(DESTROYED_SPRITE, DESTROYED_ADDRESS);
    lcd.writeCustomCharacter(OBSTACLE_UP_SPRITE, OBSTACLE_UP_ADDRESS);
    lcd.writeCustomCharacter(OBSTACLE_DOWN_SPRITE, OBSTACLE_DOWN_ADDRESS);
}

void CombatAce::startGameloop() {
    render();

    updater.attach(callback(this, &CombatAce::update), chrono::milliseconds(1000/UPS));

    updateThread.start(callback(this, &CombatAce::updateThreadFunc));
    renderThread.start(callback(this, &CombatAce::renderThreadFunc));
    btnThread.start(callback(this, &CombatAce::btnThreadFunc));
}

void CombatAce::update() {
    updateSemaphore.release();
}

void CombatAce::render() {
    lcd.cls();
    renderSemaphore.release();
}

void CombatAce::updateThreadFunc() {
    // Obstacle obstacles[4] = {o1, o2, o3, o4};
    while (!ship.isDestroyed()) {
        updateSemaphore.acquire();
        obstacle.move();
            if (obstacle.getX() == ship.getX()) {
                if (obstacle.getY() == ship.getY()) {
                    ship.destroy();
                    render();
                    gameOver = 1;
                } else {
                    score++;
                }
            }
        /*
        for (Obstacle obstacle : obstacles) {
            obstacle.move();
            if (obstacle.getX() == ship.getX()) {
                if (obstacle.getY() == ship.getY()) {
                    ship.destroy();
                    render();
                    gameOver = 1;
                } else {
                    score++;
                }
            }
        }
        */
        render();
    }
}

void CombatAce::renderThreadFunc() {
    // Obstacle obstacles[4] = {o1, o2, o3, o4};
    bool resume = 1;
    while (resume) {
        renderSemaphore.acquire();
        obstacle.draw();
        /*
        for (Obstacle obstacle : obstacles) {
            obstacle.draw();
        }
        */

        ship.draw();

        lcd.locate(14,0);
        if (score < 10) lcd.printf("0%d", score);
        else lcd.printf("%d", score);

        if (ship.isDestroyed()) resume = 0;
    }
}

void CombatAce::btnThreadFunc() {
    bool resume = 1;
    while (resume) {
        btnSemaphore.acquire();

        if (direction == UP) {
            ship.moveUp();
        } else if (direction == DOWN) {
            ship.moveDown();
        }

        if (ship.isDestroyed()) resume = 0;
    }
}

int CombatAce::getScore() {
    return score;
}

bool CombatAce::isGameOver() {
    return gameOver;
}