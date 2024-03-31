#include <iostream>

#include "game.h"
#include "utils.h"

int main() {
  srand((time(nullptr)));

  //Default config
  GameConfig config = {8, 8, 1, {64}};
  GameManager game = GameManager(config);
  // game.start_timer(); 
  setCursor(false);
  resizeWindow(400, 400);
  std::string name = "Quynh";
  ;
  while (true) {
    game.displayBoard();
    game.BackGround(); 
    game.displayScore();
    VECI dir = getConsoleInput();
    if (dir.first == -2 && dir.second == -2)
      game.pickCell();
    else
      game.moveCursor(dir);   
    Sleep(1000/60);
  }


                                  

return 0;
}