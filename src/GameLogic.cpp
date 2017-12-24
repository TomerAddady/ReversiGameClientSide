//
// Created by tomer on 02/11/17.
//

#include "../include/GameLogic.h"
GameLogic :: GameLogic()  {
    //this->b_ = new Board( size);
}
GameLogic :: ~GameLogic() {
  //  delete[](this->b);
}
/**
 * printing the board
 */
void GameLogic ::printBoard(Board * b)  {
    b->PrintBoard();
}