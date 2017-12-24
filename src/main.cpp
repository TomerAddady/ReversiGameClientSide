//
//tomer addady
//207162678
//tomer dayan
//209372499
//
 
#include <iostream>
#include "../include/Board.h"
#include "../include/Game.h"
#include "../include/Client.h"
#include "../include/RemotePlayer.h"

//#include <gtest/gtest.h>
//#include <gmock/gmock.h>

int main(int argc, char ** argv) {

    Game * g = new Game(8);
    g->run();
    delete(g);

}

