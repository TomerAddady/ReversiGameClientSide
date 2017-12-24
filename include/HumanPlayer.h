//
// Created by tomer on 31/10/17.
//

#ifndef HOMEWORK_HUMANPLAYER_H
#define HOMEWORK_HUMANPLAYER_H
#include "Cell.h"
#include "Player.h"

class HumanPlayer: public Player {
    public:
        HumanPlayer(char xORo);
        Cell chooseMove(GameLogic *gL, Board * b);
       //  Cell chooseMove();
        char getTeam();
        void oppMove(Cell move);
    protected:
        char xORo_;

};


#endif //HOMEWORK_HUMANPLAYER_H
