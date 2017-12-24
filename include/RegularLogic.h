//
// Created by tomer on 02/11/17.
//

#ifndef HOMEWORK_REGULARGAME_H
#define HOMEWORK_REGULARGAME_H
using namespace std;
#include <list>
#include "GameLogic.h"
#include "Board.h"
class RegularLogic: public GameLogic {
    public:
    list<Cell> getOptions(Player* p, Board * b);// return array of cells
    void executeChoose(Player *p, Cell c, Board * b);
    ~RegularLogic();
    RegularLogic();
   // void printBoard();
   char getWinner(Board * b);
    private:
       // Board b;
        bool checkIfOption(int i, int j, short moveInRow, short moveIncol, char xORo, Board * board); //moveInRow is 0/1/-1 which means which direction to check.
        bool isInRange (int i, int j, Board * board);
        void flipCells (char xORo, Cell c, Board * board);
        bool flipAllNeeded (char xORo, int i, int j, int whereX, int whereY, Board * board);
        char getOpposit (char c);
        bool isExsit (list<Cell> ls ,Cell c);

    };


#endif //HOMEWORK_REGULARGAME_H
