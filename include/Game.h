//
// Created by tomer on 02/11/17.
//

#ifndef HOMEWORK_GAME_H
#define HOMEWORK_GAME_H
#include "Player.h"
#include "GameLogic.h"
using namespace std;
#include <list>
class Game {
    private:
        Player *xPlayer_;//x player.
        Player *oplayer_;//o player.
        GameLogic *gameLogic_;//game logic.
        Board* b_; //game board.
        bool isExsit (list<Cell> ls,Cell c);
        int remote;
        char *firstStart();
    public:
        void printMoves(list<Cell> l, char xORo);
        void run();
        Game(int size);
     ~Game();
};


#endif //HOMEWORK_GAME_H
