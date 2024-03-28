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
    cls();
    game.displayBoard();

    char kb;
    // cin >> kb;

    // if (kb == 'w' || kb == 's' || kb == 'a' || kb == 'd') {
    //   VECI dir = mapCharToPairDir(kb);
    //   game.moveCursor(dir);
    // }
    // if (kb == 'p') {
    //   game.pickCell();
    // }
    Sleep(10 / 6);
  }
}