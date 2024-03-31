#pragma once

#include "Astar.h"
#include "board.h"
#include "utils.h"

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
  AstarGrid *pathfinder = NULL; 


 public: 
  bool cleared = false;
  int timeout_seconds; // seconds to solve this puzzle
  int time_left; // remaining time
  GameManager(GameConfig config);

  void start_timer();
  // draw board with console
  void displayBoard();

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