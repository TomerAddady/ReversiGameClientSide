//
// Created by tomer on 31/10/17.
//

#ifndef HOMEWORK_CELL_H
#define HOMEWORK_CELL_H
using namespace std;
#include <iostream>
#include <list>
using namespace std;
#include <iostream>
#include <list>

class Cell {
private:
    int row_;
    int col_;
    char stringCell[4096];
public:
    //    bool operator == (Cell & c1);
    bool operator == (Cell &c1) const;
    int getRow() const ;
    int getCol() const ;
    char *getStringCell();
    Cell(int r, int c);

    Cell();

    void printCell();

    char* makeString();
};





#endif //HOMEWORK_CELL_H
