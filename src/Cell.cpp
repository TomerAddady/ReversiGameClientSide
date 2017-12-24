//
// Created by tomer on 31/10/17.
//
#include <iostream>
#include <cstring>
#include "../include/Cell.h"
using namespace std;
/**
 * constractor.
 * @param r row.
 * @param c col.
 */
Cell ::Cell(int r, int c) : row_(r) , col_(c) {
    this->col_ = c;
    this->row_ = r;
}
/**
 * @return col of the cell.
 */
int Cell::getCol() const {
    return this->col_;
}
/**
 * @return row of the cell.
 */
int Cell::getRow() const {
    return this->row_;
}
/**
bool Cell:: operator == ( Cell & c1) {
    if (this->getCol() == c1.getCol() && c1.getRow() == this->getRow()) {
        return true;
    }
    return false;
}*/
bool Cell :: operator == (Cell &c1) const {
    if (this->getCol() == c1.getCol() && c1.getRow() == this->getRow()) {
        return true;
    }
    return false;
}


/**
 * print the cell.
 */
void Cell :: printCell() {
    cout << "(" <<  this->row_ + 1 << "," << this->col_ + 1<<") ";
}

/**
 * Convert a cell to string.
 * @return char* that its the cell.
 */
char* Cell::makeString() {

    char f[4096] = "";
    int fist = this->row_ + 1;
    int sec = this->col_ + 1;
    int digit;
    char zero = '0';
    char one = '1';
    char two = '2';
    char three = '3';
    char four = '4';
    char five = '5';
    char six = '6';
    char seven = '7';
    char eight = '8';
    char nine = '9';
    char comma = ',';
    while (sec != 0) {
        digit = sec % 10;
        if (digit == 0) { strncat(f ,&(zero) , 1);}
        if (digit == 1) { strncat(f ,&(one) , 1);}
        if (digit == 2) { strncat(f ,&(two) , 1);}
        if (digit == 3) { strncat(f ,&(three) , 1);}
        if (digit == 4) { strncat(f ,&(four) , 1);}
        if (digit == 5) { strncat(f ,&(five) , 1);}
        if (digit == 6) { strncat(f ,&(six) , 1);}
        if (digit == 7) { strncat(f ,&(seven) , 1);}
        if (digit == 8) { strncat(f ,&(eight) , 1);}
        if (digit == 9) { strncat(f ,&(nine) , 1);}
        sec = sec / 10;
    }
    strncat(f ,&(comma) , 1);

    while (fist != 0) {
        digit = fist % 10;
        if (digit == 0) { strncat(f ,&(zero) , 1);}
        if (digit == 1) { strncat(f ,&(one) , 1);}
        if (digit == 2) { strncat(f ,&(two) , 1);}
        if (digit == 3) { strncat(f ,&(three) , 1);}
        if (digit == 4) { strncat(f ,&(four) , 1);}
        if (digit == 5) { strncat(f ,&(five) , 1);}
        if (digit == 6) { strncat(f ,&(six) , 1);}
        if (digit == 7) { strncat(f ,&(seven) , 1);}
        if (digit == 8) { strncat(f ,&(eight) , 1);}
        if (digit == 9) { strncat(f ,&(nine) , 1);}
        fist = fist / 10;
    }
    char tosent[strlen(f)];
    int i =0;
    for (i = 0; i < strlen(f); ++i) {
        tosent[strlen(f) - i - 1] = f[i];
    }
    int x = this->row_ + 1;
    int y = this->col_ + 1;
    //strcpy(stringCell , tosent);
    char *send = new char(strlen(tosent));
    strcpy(send , tosent);
    return send;
}
/**
 * Def constarcot.
 */
Cell::Cell() {}
char* Cell::getStringCell() {
    return stringCell;
}