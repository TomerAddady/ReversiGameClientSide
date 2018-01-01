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
    int close_game = 0;
    cout << "please enter row col | for exit press 0" << endl;
    cin >>r;
    if (r== 0) { r = -200; c = -200; }
    else {
        cin >> c;
        while (true) {
            if (cin.fail()) {
                cin.clear(); // clears error flags
                cin.ignore();
                if (r == 0 && c == 'jjjjj' && close_game == 0) {
                    close_game++;
                    r = -1;
                    c = -1;
                    break;
                } else { close_game = 0; }
                cout << "r is : " << r << endl;
                cout << "c is : " << c << endl;
                cout << "Not legal input. please enter row col" << endl;
                cin >> r >> c;
            } else {
                break;
            }
        }

        Cell re = Cell(r - 1, c - 1);
        return re;
    }

    return Cell(-200 , -200);
}
/**
 * @return the player team.
 */
char HumanPlayer :: getTeam() {
    return this->xORo_;
}

void HumanPlayer::oppMove(Cell move) {

}
