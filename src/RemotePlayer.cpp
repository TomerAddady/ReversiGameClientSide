//
// Created by tomer on 05/12/17.
//

#include "../include/RemotePlayer.h"


#include <fstream>
#include <cstdlib>
#include "../include/RemotePlayer.h"
#include "../include/Client.h"

/**
 * Function that recieve from socket.
 * @param sock - the sock we send.
 */
void RemotePlayer::receiveFromSocket(int sock) {
    int bytes;
    char *buffer;
    buffer = client.getMove();
    if (bytes < 0) {
        perror("error reading in receive from socket");
    }
    if (strcmp(buffer , "first")==0) {
        firstPlayer = 0;
    }
    else if (strcmp(buffer , "second")==0) {
        firstPlayer = 1;
    }
    else if (strcmp(buffer , "waiting")==0) {
        cout << "Waiting for other player to join .." << endl;
    }
    else {
        strcpy(bufferCurrentAns , buffer);
    }
    delete(buffer);
}
/**
 * Function that send the move.
 * @param sock - the socket .
 * @param data - the move.
 * @param sin - the socket.
 */
void RemotePlayer::sendToSocket(char *data) {
    client.sendMove(data);
}
/**
 * Constractor.
 * the ip adress is our adress , the port is random. Need to change it because we have two players.
 */
RemotePlayer ::RemotePlayer() : client(client) {
    //first player initialize.
    firstPlayer = -1;

    ifstream configFile;
    configFile.open("../configuration_for_client.txt");// optional!

     // configFile.open("/home/tomer/CLionProjects/fromTomerMail/done/homeWork/ex3/configuration_for_client.txt");
    string ipAdd;
    configFile >> ipAdd;
    int port;
    configFile >> port;
    const char *serverIP = ipAdd.c_str();

    client = Client(serverIP , port);
    //client = Client("127.0.0.1" , 9000);

    cout << "Connected to server ." << endl;
    //in the first time we recieve the ans could be waiting or answer.
    receiveFromSocket(sock);
    if (firstPlayer == -1) {
        receiveFromSocket(sock);
    }

    //at the first time , the server give an answer different the x,y so it effect it.
    if (firstPlayer == 0) {
        this->xORo_ = 'O';
    }
    if (firstPlayer == 1) {
        this->xORo_ = 'X';
    }

}
/**
 * Choose move by the recieve from function.
 * @param gl - the game logic.
 * @param b - the board.
 * @return - the cell means the move.
 */
Cell RemotePlayer::chooseMove(GameLogic *gl, Board *b) {
    //in choose move , the answer from the server in buffercurrnetans.
    char x[4096] = "";
    char y[4096] = "";
    int comma = 0;
    int i = 0;
    receiveFromSocket(sock);

    for(i = 0; i < strlen(bufferCurrentAns); i++) {
        // if (bufferCurrentAns[i] == NULL) { break; }
        if (bufferCurrentAns[i] == ',') {
            comma = 1;
            continue;
        }
        if (comma == 0) {
            strncat(x, &bufferCurrentAns[i] , 1);
        } else {
            strncat(y, &bufferCurrentAns[i] , 1);
        }
    }
    //the number is in the char.
    int r = atoi(x);
    int c = atoi(y);
    Cell re = Cell(r -1,c - 1);
    this->currentMove = re;
    return re;
}
/**
 * Oponnent move , we sent it to the server.
 * @param c - the move.
 */
void RemotePlayer::oppMove(Cell c) {
    if (c.getRow() == -200) {
        char *s = new char(20);
        strcpy(s , "END");
        sendToSocket(s);
        //end communicate with the server.
        close(sock);
    }
    if (c.getRow() == -100) {
        char *s = new  char (20);//"ERROR";
        strcpy(s , "no_available_moves");

        sendToSocket(s);

    } else {
        char *s = c.makeString();
        //strcpy(s , c.makeString());
        sendToSocket(s);
    }
}

/**
 * Our last move.
 * @return - the cell of the last move.
 */
Cell RemotePlayer::lastMove() {
    return this->currentMove;
}
/**
 * Get the team of the player.
 * @return char means x or o .
 */
char RemotePlayer::getTeam() {
    return xORo_;
}
/**
 * Destructor.
 */
RemotePlayer::~RemotePlayer() {
//    close(sock);
}