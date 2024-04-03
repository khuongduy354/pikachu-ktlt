#pragma once

#include "Astar.h"
#include "board.h"
#include "utils.h"
#include "playSound.h"
#include <string>

class GameManager {
  Board B;   // Board representation (for rendering)
  char **b;  // char board representation (for pathfinding)

  // selected pair
  std::pair<Cell *, Cell *> selected_pair{NULL, NULL};

  // suggest pair
  std::pair<Cell *, Cell *> suggest_pair{NULL, NULL};

  // cursor index
  VECI c_idx;

  // pathfinder
  AstarGrid pathfinder{NULL, 0,0}; 


 public: 
  bool cleared = false;
  int buffer_score = 0;
  GameManager(GameConfig &config);
  ~GameManager();

  // draw board with console
  void displayBoard();
  void displayScore(int stage, int score, std::string uname);
  void BackGround();

  // scramble board;
  void scramble();

  // draw suggest line, true if suggest path available, false otherwise
  bool suggestPath();

  // move cursor 1 step toward dir
  void moveCursor(VECI dir);

  // get cell based on position
  Cell *getCell(VECI pos);

  // check if 2 selected cells match
  void checkForMatching();

  // select a cell
  void pickCell(); 

  bool checkBoardCleared();

  // pick two valid pair, if not scramble 
  void updateSuggestPair();
};