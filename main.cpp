#include <iostream>

#include "game.h"
#include "utils.h"

using std::cin;

int main() {
  srand((time(nullptr)));

  // Default config
  GameConfig config = {4, 5, 4, {2, 4, 6, 8}};
  GameManager game = GameManager(config);

  while (true) {
    system("cls");
    game.displayBoard();
    VECI dir = getConsoleInput();
    if (dir.first == -2 && dir.second == -2)
      game.pickCell();
    else
      game.moveCursor(dir); 
  }
}