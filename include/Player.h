//
// Created by tomer on 31/10/17.
//

#ifndef HOMEWORK_PLAYER_H
#define HOMEWORK_PLAYER_H
/*#ifndef PLAYER_H
#define PLAYER_H*/
#include "Cell.h"
#include "Board.h"
//#include "GameLogic.h"
//#include <GameLogic.h>

class GameLogic;


class Player {
    public:
      //  virtual  Cell chooseMove() = 0;

     virtual  Cell chooseMove(GameLogic *gL, Board * b) = 0;
        virtual char getTeam() = 0;
    virtual void oppMove(Cell move) { }
    protected:
        char xORo_;

};


#endif //HOMEWORK_PLAYER_H
