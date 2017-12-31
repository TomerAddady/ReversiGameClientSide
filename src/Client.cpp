//
// Created by tomer on 05/12/17.
//

#include "../include/Client.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

Client::Client(const char *serverIP1, int serverPort1): serverIP(serverIP) , serverPort(serverPort) ,
                                                        clientSocket(0) {
    serverIP = serverIP1;
    serverPort = serverPort1;
    connectToServer();
}

void Client::connectToServer() {
    clientSocket = socket(AF_INET , SOCK_STREAM ,0 );
    if (clientSocket == -1) {
        throw "Error";
    }
    struct in_addr address;
    if (!inet_aton(serverIP , &address)) {
        throw "Cant parse IP adress";
    }
    struct hostent *server;
    server = gethostbyaddr((const void *)&address , sizeof(address) , AF_INET);
    if (server == NULL) {
        throw "Host";
    }

    struct sockaddr_in  serverAddress;
    bzero((char * )&address , sizeof(address));

    serverAddress.sin_family = AF_INET;
    memcpy((char * )&serverAddress.sin_addr.s_addr , (char*)server->h_addr , server->h_length);

    serverAddress.sin_port = htons(serverPort);
    if (connect(clientSocket , (struct sockaddr *)&serverAddress , sizeof(serverAddress)) == -1) {
        throw "Error";
    }
}

void Client::sendMove(char *move) {
    int n = write(clientSocket , move , 255);//sizeof(move));
    delete(move);
    if (n == -1) {
        throw "Error";
    }
}

char* Client::getMove() {
    char move[255];
    int n = read(clientSocket , move , 255);

    char *buff = new char(sizeof(move));
    strcpy(buff , move);
    return buff;
}

