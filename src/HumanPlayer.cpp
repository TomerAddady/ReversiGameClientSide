//
// Created by tomer on 31/10/17.
//
#include <iostream>
using namespace std;
#include "../include/HumanPlayer.h"
#include "../include/GameLogic.h"
HumanPlayer :: HumanPlayer(char xORo) {
    this->xORo_ = xORo;
}

/**
 * @return the chosen cell.
 */
Cell HumanPlayer :: chooseMove (GameLogic * gL, Board * b) {
    int r,c;
    cout << "please enter row col" << endl;
    cin >>r >>c ;
    while (true) {
        if (cin.fail()) {
            cin.clear(); // clears error flags
            cin.ignore();
            cout << "Not legal input. please enter row col" << endl;
            cin >> r >> c;
        } else {
            break;
        }
    }
    Cell re = Cell(r - 1,c - 1);
    return re;
}
/**
 * @return the player team.
 */
char HumanPlayer :: getTeam() {
    return this->xORo_;
}

void HumanPlayer::oppMove(Cell move) {

}
