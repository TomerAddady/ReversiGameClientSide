//
// Created by tomer on 24/10/17.
//tomer addady
//207162678
//

#ifndef HOMEWORK_BOARD_H
#define HOMEWORK_BOARD_H


class Board {
    private:
        int length_;
        char ** board_;

public:
        Board(int len );
        int getSize();
        char getValueAt(int r, int c);
        void PrintBoard();
        void FreeBoard();
        //void insertValue(int r, int c, char val);
        int insertValue(int r, int c, char val);
        char getWinner();
        ~Board();
         int getScore();
         Board* copyBoard();

    };


#endif //HOMEWORK_BOARD_H
