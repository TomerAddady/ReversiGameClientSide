//
// Created by tomer on 24/11/17.
//

#ifndef HOMEWORK_IOEPLAYER_H
#define HOMEWORK_IOEPLAYER_H
#include "Cell.h"
#include "Player.h"


class IOEPlayer: public Player  {
    public:
        IOEPlayer(char xORo);
       // ~IOEPlayer();
        Cell chooseMove(GameLogic * gL, Board * b);
        //  Cell chooseMove();
        char getTeam();
    protected:
        char xORo_;
};


#endif //HOMEWORK_IOEPLAYER_H
