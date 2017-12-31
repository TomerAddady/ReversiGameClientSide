//
// Created by tomer on 05/12/17.
//

#ifndef HOMEWORK_CLIENT_H
#define HOMEWORK_CLIENT_H

class Client {
public:
    Client(const char *serverIP , int serverPort);

    Client();

    void connectToServer();

    void sendMove(char *move);
    char* getMove();

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //HOMEWORK_CLIENT_H
