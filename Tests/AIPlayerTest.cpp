//
// Created by tomer on 28/11/17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/IOEPlayer.h"
#include "../include/RegularLogic.h"
#include "../include/HumanPlayer.h"


using namespace std;

TEST(AI_test, get_team_test) {
    Player * p1 = new IOEPlayer('O');
    EXPECT_TRUE(p1->getTeam() == 'O');
    EXPECT_FALSE(p1->getTeam() == 'X');

}

TEST(AI_test, choose_move_test) {
    Player * p1 = new IOEPlayer('O');
    Board * b = new Board (8);
    Player * p = new HumanPlayer('X');
    RegularLogic * lg = new RegularLogic();

    lg->executeChoose(p, Cell(2, 3), b);
    Cell c = p1->chooseMove(lg, b);
    lg->executeChoose(p1, c, b);
    Cell c1 (2, 2);
    EXPECT_TRUE(c == c1);

    lg->executeChoose(p, Cell(4, 5), b);
    c = p1->chooseMove(lg, b);
    cout << c.getRow() << " , " << c.getCol() << endl;
    Cell c2 (5, 5);
    EXPECT_TRUE(c == c2);

    lg->executeChoose(p, Cell(6, 5), b);
    c = p1->chooseMove(lg, b);
    cout << c.getRow() << " , " << c.getCol() << endl;
    Cell c3 (6, 6);
    EXPECT_TRUE(c == c2);
}
