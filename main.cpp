#include <iostream>

#include "game.h"
#include "menu.h"
#include "utils.h"

int main() {
  srand((time(nullptr)));
  int FPS = 60;
  setCursor(false);

  // initialize menu
  Menu menu = Menu();
  bool cleared_menu = false;

  // initialize game with first config
  GameConfig configs[3] = {
      {4, 4, 6, {2, 2, 2, 2, 4, 4}},
      {6, 6, 15, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4}},
      {8, 8, 25, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                  2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2}}};
  GameConfig start_config = configs[0];
  GameManager game = GameManager(start_config);
  int stage = 1;
  int score = 0;

  while (true) {
    // Show menu if haven't entered game
    if (!menu.enter_game) {
      menu.showScreen();

      // get menu keyboard input
      VECI dir = getConsoleInput();

      if (dir.first == -2 && dir.second == -2) {
        // enter
        menu.press();
      } else if (dir.second != 0 || dir.first != 0) {
        // move
        menu.moveSelected();
      }
      menu.showScreen();
      continue;
    } else if (!cleared_menu) {
      // clear menu once when enter game
      cleared_menu = true;
      system("cls");
    };

    // Game: stage clear, move to new game
    if (game.cleared) {
      system("cls");
      // update score at end of stage
      game.saveFile(menu.uname, stage, score);

      // pick suitable config based on stage
      GameConfig new_config = configs[0];
      if (stage > 2) {
        new_config = configs[1];
      } else if (stage > 5) {
        new_config = configs[2];
      }

      game = GameManager(new_config);
      stage++;
    }

    game.displayBoard();
    if (stage > 5) {
      // only apply background to 8x8, which appears at stage 5+
      game.BackGround();
    }
    game.displayScore(stage, score, menu.uname);
 

    // handle input
    int key = _getch();
    VECI dir = parseInput(key); 

    if (dir.first == -2 && dir.second == -2) { 
      // input is enter
      game.pickCell();
      score += game.buffer_score;
      game.buffer_score = 0;
    } else if (dir.first == 0 && dir.second == 0) { 
      // if input is not a direction or enter, handle differently
      // if pressed f , suggest path
      if (key == 'F' || key == 'f') {
        game.suggestPath(); // highlight suggest cells
        Sleep(1000);
      }
      if (key == KEY_ESC) { 
        exit(0);
      }
    } else { 
      // input is direction
      game.moveCursor(dir);
    }
  }

  return 0;
}