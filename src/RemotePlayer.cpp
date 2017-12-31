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
    cout << "buffer is: "<<buffer << endl;
    if (bytes < 0) {
        perror("error reading in receive from socket");
    }
    if (strcmp(buffer , "first")==0) {
        currect_name = 1;
        firstPlayer = 0;
    }
    else if (strcmp(buffer , "second")==0) {
        currect_name = 1;

        firstPlayer = 1;
    }
    else if (strcmp(buffer , "waiting")==0) {
        currect_name = 1;

        cout << "Waiting for other player to join .." << endl;
    } else if (strcmp(buffer , "-1") == 0) {
        cout << "Name not available , try another one\n";
    }
    else {
        currect_name = 1;

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

RemotePlayer::RemotePlayer(char *send_server){
    currect_name = 0;
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
    cout << send_server<<endl;

    if (strcmp(send_server , "list_games") == 0) {
        //show_list();
        char *ans = "list_games";
        while (true) {
            if (strcmp(ans , "list_games") != 0) {
                sendToSocket(ans);
                break;
            } else {
                sendToSocket("list_games");
                show_list();
            }
            client = Client(serverIP , port);
            ans = little_menu();
        }
    } else { sendToSocket(send_server); }

    cout << "Connected to server ." << endl;
    //in the first time we recieve the ans could be waiting or answer.
    while (currect_name != 0){
        if (currect_name == 0) {
            client = Client(serverIP , port);
            char *s;
            while (true) {
                s = little_menu();
                if (strcmp(s , " ")!= 0) {
                    if (strcmp(s , "list_games") == 0) {
                        show_list();
                    } else {
                        break;
                    }
                    client = Client(serverIP , port);
                }
            }
            sendToSocket(s);
        } else { break; }
        receiveFromSocket(sock);
    }
    cout << "*****************" << endl;
    while (true) {
        if (firstPlayer == -1) {
            receiveFromSocket(sock);
        } else { break; }
    }
    cout << "--------------------" << endl;

    cout << firstPlayer;
    //at the first time , the server give an answer different the x,y so it effect it.
    if (firstPlayer == 0) {
        this->xORo_ = 'O';
    }
    if (firstPlayer == 1) {
        this->xORo_ = 'X';
    }

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

void RemotePlayer::show_list() {
    while (true){
        receiveFromSocket(sock);
        //char *c = bufferCurrentAns;
        if (strcmp(bufferCurrentAns , "endLoop") == 0) { break; }

        cout<< bufferCurrentAns << endl;
    }
}

char* RemotePlayer::little_menu() {
    cout << "1) start a game , press - 1\n";
    cout << "2) join a game , press - 2\n";
    cout << "3) seeing a list of games , press - 3\n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "Enter the name of the game you want to create :\n";
        char *gameNamge = new char();
        char *s = "start ";
        cin >> gameNamge;
        char * toSend = new char(sizeof(s) + sizeof(gameNamge));
        strcpy(toSend , s);
        strcat(toSend , gameNamge);
        delete(gameNamge);
        return toSend;
    } else if (choice == 2) {
        cout << "Enter the name of the game you want to join :\n";
        char *s = "join ";
        char *gameNamge = new char();
        cin >> gameNamge;
        char * toSend = new char(sizeof(s) + sizeof(gameNamge));
        strcpy(toSend , s);
        strcat(toSend , gameNamge);
        delete(gameNamge);
        return toSend;
    } else if (choice == 3) {
        char *s = "list_games";
        return s;
    } else {
        cout << "Invalid option , please try again\n";
        return " ";
    }
}