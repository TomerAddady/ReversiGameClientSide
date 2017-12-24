//
// Created by tomer on 25/11/17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"
using namespace std;
TEST(Board_test, score_test) {
    Board* b = new Board(8);
    EXPECT_EQ(b->getScore(), 0);
    delete(b);
}

TEST(Board_test, insert_and_get_value_test) {
    Board * b = new Board(8);
    b->insertValue(7, 7, 'X');
    EXPECT_EQ(b->getValueAt(7, 7), 'X');
    b->insertValue(7,7,'O');
    EXPECT_EQ(b->getValueAt(7, 7), 'O');
    delete(b);
}

TEST(Board_test, get_board_size_test) {
    Board * b = new Board (8);
    EXPECT_EQ(b->getSize(), 8);
    Board * b2 = new Board (2);
    EXPECT_EQ(b2->getSize(), 2);
    Board * b3 = new  Board (5);
    EXPECT_EQ(b3->getSize(), 5);
    delete(b);
    delete(b2);
    delete(b3);
}
TEST(Board_test, copy_board_test) {
    Board  * src = new Board(8);
    Board * dst = src->copyBoard();
    int i;
    int j;
    for (i = 0; i < src->getSize(); i++) {
        for ( j = 0; j < src->getSize() ; j++) {
            EXPECT_EQ(src->getValueAt(i, j), dst->getValueAt(i , j));
        }
    }
    delete(src);
    delete(dst);
}
TEST(Board_test, get_winner_of_board_test) {
    Board * b = new Board(8);
    EXPECT_EQ(b->getWinner(), 'T'); // if tie
    b->insertValue(7,7,'X');
    EXPECT_EQ(b->getWinner(), 'X'); // if X won
    b->insertValue(7,7,'O');
    b->insertValue(1,1,'O');
    EXPECT_EQ(b->getWinner(), 'O'); // if O won
    delete(b);
}


class BoardClassTest {



};