//
// Created by tomer on 29/11/17.
//
#include <iostream>
//#include <algorithm>
#include "../include/ConsolePainter.h"
using  namespace std;



int ConsolePainter:: printMenu() {
    char r;
    cout << "Welcome to Reversi!" << endl;
    cout << "Choose an opponent type:" << endl;
    cout << "if you want to play against the comuter press y if not press other key "<< endl;
    cout << "1. a human local player" << endl;
    cout << "2. an AI player" << endl;
    cout << "3. a remote player" << endl;
    cin >>r;
    if (r == '1') {
        return 1;
    }
    if (r == '2') {
        return 2;
    } if (r == '3') {
        return 3;
    }
    return 0;
}

//char HumanPlayer :: getTeam() {
