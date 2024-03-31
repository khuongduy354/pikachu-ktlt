#include <iostream>

#include "game.h"
#include "utils.h"

using std::cin;

int main() {
  srand((time(nullptr)));

  // Default config
  GameConfig config = {4, 5, 4, {2, 4, 6, 8}};
  GameManager game = GameManager(config);
  game.start_timer();

  while (true) {    
    // HANDLE game finish 
    bool cleared = game.cleared;  
    if(cleared){  
      // TODO: shrink timer here (increase difficulty)
      game = GameManager(config);  
      game.start_timer();
    };

    // HANDLE TIMEOUT 
    int time_left = game.time_left;
    if(time_left == 0){
      //TODO: add game over here 

    }
    // TODO: game.displayDashboard();


    game.displayBoard();

    VECI inp = getConsoleInput();
    if (inp.first == -2 && inp.second == -2) {
      // ENTER
      game.pickCell();
    } else {
      game.moveCursor(inp);
    }
  }
}