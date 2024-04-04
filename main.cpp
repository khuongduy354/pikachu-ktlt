#include <iostream>

#include "game.h"
#include "menu.h"
#include "utils.h"

int main() {
  srand((time(nullptr)));
  // Show Menu
  Menu menu = Menu();

  // Default config
  // GameConfig config = {8, 8, 1, {64}};
  GameConfig configs[3] = {{4, 4, 6, {2, 2, 2, 2, 4, 4}}, {6, 6, 15, {2,2,2,2,2,2,2,2,2,2,4,4,4,4}}, {8, 8, 25, {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,2,2}}};
  GameConfig start_config = configs[0];
  GameManager game = GameManager(start_config);
  int FPS = 60;
  setCursor(false);
  // resizeWindow(400, 400);
  // std::string name = "Quynh";
  int stage = 1;
  int score = 0;

  bool cleared_menu = false;

  while (true) {
    // Sleep(1000 / FPS);
    if (!menu.enter_game) {
      menu.showScreen();

      VECI dir = getConsoleInput();

      if (dir.first == -2 && dir.second == -2) {
        // enter
        menu.press();
      } else if (dir.second != 0 || dir.first != 0) {
        menu.moveSelected();
      }

      menu.showScreen();
      continue;
    } else if (!cleared_menu) {
      cleared_menu = true; 
      system("cls");
    };

    // HANDLE staged cleared
    if (game.cleared) { 
      system("cls");   
      game.saveFile(menu.uname, stage, score);
      std::cout << "You cleared this stage";
      GameConfig new_config = configs[0];
      if(stage > 3 ){  
        new_config = configs[1];
      } else if(stage > 6){ 
        new_config = configs[2];
      }
      game = GameManager(new_config);
      stage++; 
    }

    game.displayBoard();
    if(stage > 6){
    game.BackGround();
    }
    game.displayScore(stage, score, menu.uname); 


    int key = _getch();

    VECI dir = parseInput(key);

    if (dir.first == -2 && dir.second == -2) {
      game.pickCell();
      score += game.buffer_score;
      game.buffer_score = 0;
    } else if (dir.first == 0 && dir.second == 0) {   
      // if pressed f , suggest path
      if(key == 'F' || key == 'f'){  
        game.suggestPath();
      }
    } else {
      game.moveCursor(dir);
    }
  }

  return 0;
}