//
// Created by tomer on 28/11/17.
//
using namespace std;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/RegularLogic.h"
#include "../include/HumanPlayer.h"
#include "../include/Cell.h"
TEST(RegularLogic_test, execute_choose_test) {
    Board * b = new Board (8);
    RegularLogic * lg = new RegularLogic();
    Player * p = new HumanPlayer('X');
    Player * p1 = new HumanPlayer('O');
    int i;
    lg->executeChoose(p, Cell(2, 3), b);
    EXPECT_EQ(b->getValueAt(3,3), 'X');
    //lg->executeChoose(p, Cell(5, 3), b);
    lg->executeChoose(p1, Cell(5, 3), b);
    lg->executeChoose(p1, Cell(1, 3), b);
    for (i = 1; i < 6; i++) {
        EXPECT_EQ(b->getValueAt(i,3), 'O');
    }
    lg->executeChoose(p, Cell(6, 3), b);
    lg->executeChoose(p, Cell(0, 3), b);
    for (i = 0; i < 7; i++) {
        EXPECT_EQ(b->getValueAt(i,3), 'X');
    }
    lg->executeChoose(p, Cell(5, 2), b);
    EXPECT_EQ(b->getValueAt(5,2), 'X');
    EXPECT_EQ(b->getValueAt(4,3), 'X');
    EXPECT_EQ(b->getValueAt(3,4), 'X');
    delete(b);
    delete(p);
    delete(p1);
    delete(lg);
}
TEST(RegularLogic_test, get_options_test) {
    Board * b = new Board (8);
    RegularLogic * lg = new RegularLogic();
    Player * p = new HumanPlayer('X');
    Player * p1 = new HumanPlayer('O');
    list <Cell> s;
    list <Cell>cmp;
    s = lg->getOptions(p, b);
    EXPECT_EQ(s.size(), 4);
    lg->executeChoose(p, Cell(5, 4), b);
    s = lg->getOptions(p1, b);
    EXPECT_EQ(s.size(), 3);
    cmp.push_back(Cell(5, 3));
    cmp.push_back(Cell(5, 5));
    cmp.push_back(Cell(3, 5));
    int mone = 0;
    /**
     * check if option from all directions arrived.
     */
    for (list<Cell>::iterator it = s.begin(); it != s.end(); ++it) {
        for (list<Cell>::iterator it1 = cmp.begin(); it1 != cmp.end(); ++it1) {
            if (it->getRow() == it1->getRow() && it->getCol() == it1->getCol()) {
                mone++;
            }
        }
    }
    EXPECT_EQ(mone, 3);
}


