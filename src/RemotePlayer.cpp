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
int RemotePlayer::receiveFromSocket(int sock) {
    int bytes;
    char *buffer;
    buffer = client.getMove();
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
    } else if (strcmp(buffer , "close") == 0) {
        cout << "Error occur . Please try later .. \n";
        strcpy(bufferCurrentAns , " ");
        firstPlayer = 1;
        return -1;
    }
    else {
        //currect_name = 1;
        strcpy(bufferCurrentAns , buffer);
    }
    delete (buffer);
    return 1;
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
 * Constractor by ex5 , sending the current action by command line.
 *
 */
RemotePlayer::RemotePlayer() {
    //first show the little menu !
    char *send_server = little_menu();

    //current name is variable that check if the name of the game current , when become 1 - not ava.
    currect_name = 0;
    //first player initialize.
    firstPlayer = -1;
    ifstream configFile;
    configFile.open("../configuration_for_client.txt");// optional!

    //get the ip and port from txt.
    string ipAdd;
    configFile >> ipAdd;
    int port;
    configFile >> port;
    const char *serverIP = ipAdd.c_str();
    cout << port << " --- " << ipAdd << endl;

    /*
     * We see a lot of new clients in this function
     * Each client mean new connection between us and the server
     * in the server , we can see after we get the answer we want ,
     * the connection is closing.
     * That means we need to re - open the conncection and we do it by client = CLient()
     */
    client = Client(serverIP , port);
    cout << "Connected to server ." << endl;

    //client = Client("127.0.0.1" , 9000);

    if (strcmp(send_server , "list_games") == 0) {
        char * ans = "list_games";
        while (true) {
            //if we want something differ then list games exit.
            if (strcmp(ans , "list_games") != 0) {
                sendToSocket(ans);
                break;
            } else {
                sendToSocket("list_games");
                show_list();
            }
            //new connection and get from little menu.
           // try {
                client = Client(serverIP , port);
           // } catch (const char * msg) {
              //  break;
           //     return ;
           // }


            ans = little_menu();
        }
    } else { sendToSocket(send_server); }
    //in this while we wait till the server get a game name available.
    //when he does , he continue. remember , available name game is when current_name differ than 0.
    receiveFromSocket(sock);
    while (true){
        if (currect_name == 0) {
            client = Client(serverIP , port);
            char *s;
            while (true) {
                s = little_menu();
                if (strcmp(s , " ")!= 0) {
                    //in case the client want to see list of games.
                    if (strcmp(s , "list_games") == 0) {
                        sendToSocket(s);
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
    //now wait untill we get if the player is first or second.
    //there is a chance that we get garbage so its in the while !
    while (true) {
        if (firstPlayer == -1) {
            receiveFromSocket(sock);
        } else { break; }
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

    if (strcmp(bufferCurrentAns , " ") == 0) {
        Cell re = Cell(-300,-300);
        return re;
    }

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
    if (c.getRow() == -200 || c.getRow() == -300) {
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
/**
 * Function that get from the server games name and print them.
 */
void RemotePlayer::show_list() {
    cout << "Current games: \n";
    while (true){
        int res = receiveFromSocket(sock);
        if (res == -1) {
            break;
        }
        //char *c = bufferCurrentAns;
        if (strcmp(bufferCurrentAns , "endLoop") == 0) {
            break;
        }

        cout<< bufferCurrentAns << endl;
    }
    cout << " " << endl;
}
/**
 * Function that represent little menu.
 * @return - answer in this menu.
 */
char* RemotePlayer::little_menu() {
    //the options.
    cout << "1) start a game , press - 1\n";
    cout << "2) join a game , press - 2\n";
    cout << "3) seeing a list of games , press - 3\n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        //if we want to play new game.
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
        //if we want to join a game.
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
        //if we want to print a list of game are playing now.
        char  * s = "list_games";
        return s;
    } else {
        cout << "Invalid option , please try again\n";
        return " ";
    }
}