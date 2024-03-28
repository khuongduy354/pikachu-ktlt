#include "game.h"

#include <vector>
using std::vector;

GameManager::GameManager(GameConfig config) {
  this->B = generateBoard(config);
  c_idx = VECI{0, 0};
  this->B.c[0][0].state = 1;
  this->pathfinder =
      new Astar::AstarGrid(toCharBoard(this->B), config.m, config.n);
};

void GameManager::displayBoard() { showBoard(B); };

void GameManager::moveCursor(VECI dir) {
  // wrap around grid
  int ncell_i = (c_idx.first + dir.first) % B.config.m;
  int ncell_j = (c_idx.second + dir.second) % B.config.n;

  if (ncell_i < 0) ncell_i = B.config.m - 1;

  if (ncell_j < 0) ncell_j = B.config.n - 1;

  // previsous cell
  Cell *prev_cell = getCell(c_idx);
  // set cursor
  c_idx.first = ncell_i;
  c_idx.second = ncell_j;

  // highlight cell under cursor
  if (prev_cell != NULL) {
    // set active for next cell
    B.c[c_idx.first][c_idx.second].state = 1;

    // if prev cell is not picked, deactivate it
    if (prev_cell != selected_pair.first && prev_cell != selected_pair.second) {
      prev_cell->state = 0;
    }
  }
}

Cell *GameManager::getCell(VECI pos) {
  for (int i = 0; i < B.config.m; i++) {
    for (int j = 0; j < B.config.n; j++) {
      if (pos.first == i && pos.second == j) return &B.c[i][j];
    }
  }
  return NULL;
};

void GameManager::checkForMatching() {
  // must have 2 selected cell.
  if (selected_pair.first == NULL || selected_pair.second == NULL) return;

  //  setup astar
  Astar::Point start =
      Astar::VeciToPoint(getCoorFromCell(*selected_pair.first));
  Astar::Point end = Astar::VeciToPoint(getCoorFromCell(*selected_pair.second));
  vector<Astar::Point> *paths = pathfinder->find_path(start, end);

  selected_pair.first->state = 0;
  selected_pair.second->state = 0;

  // found
  if (paths != NULL) {
    selected_pair.first->c = ' ';
    selected_pair.second->c = ' ';

    // TODO: update AStar grid here
  }

  selected_pair.first = NULL;
  selected_pair.second = NULL;

  // highlight cell under cursor
  Cell *c_under_cursor = getCell(c_idx);
  if (c_under_cursor != NULL) c_under_cursor->state = 1;
};

void GameManager::pickCell() {
  Cell *c_under_cursor = getCell(c_idx);
  // cell under cursor is already selected
  if (c_under_cursor == selected_pair.first ||
      c_under_cursor == selected_pair.second)
    return;
  // both cell selected
  if (selected_pair.first != NULL && selected_pair.second != NULL) return;

  if (selected_pair.first == NULL && selected_pair.second == NULL) {
    // first cell selected
    selected_pair.first = c_under_cursor;
  } else {
    // second cell selected
    selected_pair.second = c_under_cursor;
    checkForMatching();
  }
};