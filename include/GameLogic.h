//
// Created by tomer on 02/11/17.
//
using namespace std;

#ifndef HOMEWORK_GAMELOGIC_H
#define HOMEWORK_GAMELOGIC_H
#include <list>
#include "Cell.h"
#include "Player.h"
#include "Board.h"

class GameLogic {
    public:
        virtual list<Cell> getOptions(Player* p,  Board * b) = 0 ;
        virtual void executeChoose(Player *p, Cell c, Board * b) = 0;
        GameLogic ();
        virtual void printBoard(Board * b);
        virtual char getWinner(Board * b) = 0;
        virtual ~GameLogic();

protected:
        // Board b;

        //   Board* b_;
};


#endif //HOMEWORK_GAMELOGIC_H
