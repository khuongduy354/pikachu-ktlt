#pragma once

#include "Astar.h"
#include "board.h"
#include "utils.h"

class GameManager {
  Board B;

  // selected pair
  std::pair<Cell *, Cell *> selected_pair{NULL, NULL};

  // cursor index
  VECI c_idx;

  // pathfinder
  Astar::AstarGrid *pathfinder = NULL;

 public:
  GameManager(GameConfig config);

  // draw board with console
  void displayBoard();

  // move cursor 1 step toward dir
  void moveCursor(VECI dir);

  // get cell based on position
  Cell *getCell(VECI pos);

  VECI getCoorFromCell(Cell c) { return VECI{c.i, c.j}; };

  // check if 2 selected cells match
  void checkForMatching();

  // select a cell
  void pickCell();
};