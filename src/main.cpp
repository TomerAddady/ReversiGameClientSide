//
//tomer addady
//207162678
//tomer dayan
//209372499
//
 
#include <iostream>
#include <fstream>
#include "../include/Board.h"
#include "../include/Game.h"
#include "../include/Client.h"
#include "../include/RemotePlayer.h"

//#include <gtest/gtest.h>
//#include <gmock/gmock.h>

int main(int argc, char ** argv) {
    ifstream configFile;
    configFile.open("../configuration_for_client.txt");// optional!
    //Game *g;
    try {
        Game *g = new Game(8);
        delete (g);
    } catch (const char * msg) {
       // delete (g);
        cout << "server closed! try to run again later!" << endl;
    }

}

