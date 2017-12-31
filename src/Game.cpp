//
// tomer addady - 207162678
// tomer dayan - 209372499
//
#include <iostream>
#include "../include/HumanPlayer.h"
#include "../include/IOEPlayer.h"
#include "../include/ConsolePainter.h"
#include "../include/Game.h"
#include "../include/RegularLogic.h"
#include "../include/RemotePlayer.h"

using  namespace std;

char* Game::firstStart() {
    cout << "1) For start a game , press - 1\n";
    cout << "2) For join a game , press - 2\n";
    cout << "3) For see a list of games , press - 3\n";
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

Game::Game(int size) {
    /** char r;
     cout << "if you want to play against the comuter press y if not press other key "<< endl;
     cin >>r;*/
    ConsolePainter *painter = new ConsolePainter ();
    int ans = painter->printMenu();
    remote = 0;
    if (ans == 2){//painter->printMenu() == 1) {
        this->gameLogic_ = new RegularLogic();
        this->b_ = new Board(size);
        this->oplayer_ = new IOEPlayer('O');
        //this->oplayer_ = new HumanPlayer('O');
        this->xPlayer_ = new HumanPlayer('X');
    } else if (ans == 3){

        //means that we play with server.
        this->gameLogic_ = new RegularLogic();
        this->b_ = new Board(size);

        char *send = "";
        while (true) {
            send = firstStart();
            if (strcmp(send , " ") != 0) { break; }
        }


        Player *c = new RemotePlayer(send);
        if (c->getTeam() == 'O') {
            remote = 1;
            this->oplayer_ = c;
            this->xPlayer_ = new HumanPlayer('X');

        } else {
            remote = 2;
            this->xPlayer_ = c;
            this->oplayer_ = new HumanPlayer('O');
        }
    } else if (ans == 1){
        this->gameLogic_ = new RegularLogic();
        this->b_ = new Board(size);
        //this->oplayer_ = new IOEPlayer('O');
        this->oplayer_ = new HumanPlayer('O');
        this->xPlayer_ = new HumanPlayer('X');
    }

    delete(painter);
}
Game :: ~Game() {
    delete(this->xPlayer_);
    delete(this->oplayer_);
    // cout << "banana" << endl;
    delete(this->gameLogic_);
    delete(this->b_);

    // cout << "banana5" << endl;

}
/**
 * run the game.
 */
void Game::run() {

    // while(this->gameLogic_->getOptions(this->xPlayer_) == 0) { // if no more possible moves
    //Cell  choise;
    bool flag = true;
    list<Cell> ls;

    ls = this->gameLogic_->getOptions(this->xPlayer_, this->b_);
    this->gameLogic_->printBoard(this->b_);
    while(!ls.empty() || !this->gameLogic_->getOptions(this->oplayer_, this->b_).empty()) { // if no more possible moves
        //ls = this->gameLogic_->getOptions(this->xPlayer_);
        if (remote != 2) {
            printMoves(ls, this->xPlayer_->getTeam());
        } else {
            if (ls.empty()) {
                printMoves(ls, this->xPlayer_->getTeam());
            } else {
                cout << "Waiting for another player's move .." << endl << "" << endl;
            }
        }
        if (!ls.empty()) {
            Cell choise = this->xPlayer_->chooseMove(this->gameLogic_, this->b_);
            // Cell choise = this->xPlayer_->chooseMove();
            if(remote != 2) {
                while (!isExsit(ls, choise)) {
                    if (remote != 2) {
                        cout << "NOT A Legall MOVE TRY AGAIN" << endl;
                        printMoves(ls, this->xPlayer_->getTeam());
                    }
                    choise = this->xPlayer_->chooseMove(this->gameLogic_, this->b_);
                    //choise = this->xPlayer_->chooseMove();
                }
            }
            this->gameLogic_->executeChoose(this->xPlayer_, choise, this->b_);
            this->gameLogic_->printBoard(this->b_);
            //print res
            cout << this->xPlayer_->getTeam() << " played: ";
            choise.printCell();
            cout <<""<< endl << endl;
            oplayer_->oppMove(choise);

        } else {
            //means no available moves.
            Cell choise (-100, -100);
            oplayer_->oppMove(choise);
            flag = false;
        }
        ls = this->gameLogic_->getOptions(this->oplayer_, this->b_);

        if (remote != 1) {
            printMoves(ls, this->oplayer_->getTeam());

        } else {
            cout << "Waiting for another player's move .. " << endl << "" << endl;
        }

        if (ls.empty() && !flag) { // if both lists are empty
            break;
        }
        flag = true;
        if(!ls.empty()) {
            Cell choise = this->oplayer_->chooseMove(this->gameLogic_, this->b_);
            //Cell choise = this->oplayer_->chooseMove();
            if (remote != 1) {
                while (!isExsit(ls, choise)) {
                    cout << "NOT A Legall MOVE TRY AGAIN" << endl;
                    printMoves(ls, this->oplayer_->getTeam());

                    choise = this->oplayer_->chooseMove(this->gameLogic_, this->b_);
                    // choise = this->oplayer_->chooseMove();

                }
            }
            this->gameLogic_->executeChoose(this->oplayer_, choise, this->b_);
            this->gameLogic_->printBoard(this->b_);
            //print res
            cout << this->oplayer_->getTeam() << " played: ";
            choise.printCell();
            cout <<""<< endl << endl;
            xPlayer_->oppMove(choise);

        } else {
            //means not available moves.
            Cell choise (-100, -100);
            xPlayer_->oppMove(choise);
        }

        ls = this->gameLogic_->getOptions(this->xPlayer_, this->b_);
    }
    if (remote != 0) {
        //means the game end.
        Cell choice(-200, -200);
        if (remote == 2) { xPlayer_->oppMove(choice); }
        if (remote == 1) { oplayer_->oppMove(choice); }
    }
    char res = this->gameLogic_->getWinner(this->b_);
    if(res == 'T') {
        cout << "Its a Draw" << endl;
    } else {
        cout <<res << ": you win!" << endl;
    }

}
/**
 * @param ls list to check.
 * @param c value to check if he exsit.
 * @return .
 */
bool Game :: isExsit (list<Cell> ls,Cell c) {
    if (!ls.empty()) {
        for (list<Cell>::iterator it = ls.begin(); it != ls.end(); ++it) {
            if (it->getRow() == c.getRow() && it->getCol() == c.getCol()) {
                return true;
            }
        }
    }
    return false;
}
/**
 * printing player optional moves.
 * @param l list of moves.
 * @param xORo player charcter.
 */
void Game ::printMoves(list<Cell> l, char xORo) {
    cout << xORo <<": Its your move."<< endl;
    cout  << "your possible moves: " ;
    if (l.empty()) {
        cout << "No possible moves. Play passes back to the other player. Press any key to continue" <<endl;
        //char dummy;
        // cin.clear(); // clears error flags
        cin.get();
        cin.clear(); // clears error flags
        cin.ignore();

        // system("read");
    } else {
        while (!l.empty()) {
            l.front().printCell();
            l.pop_front();
        }
        cout << endl;
    }
}
