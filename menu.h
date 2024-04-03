#include <fstream>
#include <iostream>
#include <string>

#include "board.h"

using namespace std;
class Menu {
  public:
  int selected = 0;
  // std::string menu_template;
  std::string uname; 
  bool enter_game=false;
  bool show_leaderboard = false; 

  void moveSelected();
  void press();
  void highlightSelected();
  void showScreen(); 
  void showMenu();

  // section other than main menu
  void gameTitle();
  void getPlayerInfor();
  void LeaderBoard();
  void endGame(int score);
};
