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

    // configFile.open("/home/tomer/CLionProjects/fromTomerMail/done/homeWork/ex3/configuration_for_client.txt");
    /*
    string ipAdd;
    configFile >> ipAdd;
    int port;
    configFile >> port;
    const char *serverIP = ipAdd.c_str();
    Client client = Client(serverIP , port);
    client.sendMove("start");
*/
    Game * g = new Game(8);
    g->run();
    delete(g);

}

