//
// Created by tomer on 24/10/17.
// tomer adday
// 207162678
//

#include "../include/Board.h"
#include <iostream>
using namespace std;




/**
 * Function that copy board to new board.
 * @return new board , exactly the same.
 */
Board* Board::copyBoard() {
    Board *new_board = new Board(length_);
    int i , j;
    for ( i = 0; i < this->length_; ++i) {
        for ( j = 0; j < this->length_; ++j) {
            if (this->board_[i][j] == 'X') {
                new_board->board_[i][j] = 'X';
            } else if (this->board_[i][j] == 'O') {
                new_board->board_[i][j] = 'O';
            } else {
                new_board->board_[i][j] = ' ';
            }
        }
    }

    return new_board;
}


/**
 * Function that return the x's - y's.
 * @return int - the x's - y's.
 */
int Board::getScore() {
    int i , j , count = 0;
    for ( i = 0; i < this->length_; ++i) {
        for ( j = 0; j < this->length_; ++j) {
            if (this->board_[i][j] == 'X') { count ++; }
            if (this->board_[i][j] == 'O') { count--; }
        }
    }
    return count;
}


Board :: Board(int len): length_(len) {
    this->length_ = len;
    this->board_ = new char* [len];
    //initialize the board
    for (int i = 0; i < this->length_; i++) {
        board_[i] = new char[len];
        for (int j = 0; j < this->length_; j++) {
            this->board_[i][j] = ' ';
        }
    }
    this->board_ [this->length_ / 2 - 1][this->length_ / 2 - 1] = 'O';
    this->board_ [this->length_ / 2 - 1][this->length_ / 2 ] = 'X';
    this->board_ [this->length_ / 2 ][this->length_ / 2 - 1] = 'X';
    this->board_ [this->length_ / 2][this->length_ / 2] = 'O';
}
/**
 * Board destractor.
 */
Board::~Board() {
    //cout << "banana22" << endl;
    for(int j = 0; j < this->length_; j++) {
        delete[](this->board_[j]);


    }
   // cout << "banana3" << endl;
    delete[](this->board_);
  //   delete(this->board_);

   // cout << "banana4" << endl;

}
/**
 * printng board.
 */
void Board:: PrintBoard() {
    //loop to print the first line of numbers
    for (int i = 0; i < this->length_; i++) {
        cout <<" | " <<+ i+1;
    }
    cout <<" |"<< endl;
    //loops to print the rest of the board
    for(int j = 0; j < this->length_; j++) {
        cout <<"----------------------------------"<< endl;
        cout <<j+1 << "|";
        for(int l = 0; l < this->length_; l++) {
            cout <<" " << board_[j][l] << " |";
        }
        cout << endl;
    }
    cout <<"----------------------------------"<< endl;

}

void Board::FreeBoard() {
    for(int j = 0; j < this->length_; j++) {
            delete[](this->board_[j]);
    }
    delete[](this->board_);
}
/**
 * inserting value to the board.
 * @param r row.
 * @param c col.
 * @param val  value.
 */
int  Board::insertValue(int r, int c, char val) {
    if (r < this->length_ && c < this->length_ && r >= 0 && c >= 0) { // if in range.
        this->board_[r][c] = val;
        return 1;
    }
    return 0;
    //  char x = board_[r][c];
    //char banana = 'f';
}
int  Board::getSize() {
    return this->length_;
}
/**
 * @param r row.
 * @param c col.
 * @return value of voard at r,c.
 */
char Board :: getValueAt(int r, int c) {
    char x = this->board_[r][c];
    return x;
}
char Board :: getWinner() {
    int xCount = 0 , oCount = 0;
    for (int i = 0; i < this->length_; i++) {
        for (int j = 0; j < this->length_; j++) {
            if(this->board_[i][j] == 'X') {
                xCount++;
            } else if (this->board_[i][j] == 'O') {
                oCount++;
            }
        }
    }
  //  cout << "x - " << xCount << "o - " << oCount << endl;
    if (xCount > oCount)
        return 'X';
    else if (oCount > xCount) {
        return 'O';
    } else {
        return 'T'; // tie draw.
    }
}
