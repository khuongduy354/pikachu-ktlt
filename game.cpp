#include "game.h"
#include <fstream>
#include <algorithm>
#include <vector>
using std::string;
using std::vector;

GameManager::GameManager(GameConfig &config) {
  B = generateBoard(config);
  c_idx = VECI{0, 0};
  cleared = false;
  B.c[0][0].state = 2;
  b = toCharBoard(B);
  pathfinder = AstarGrid(b, config.m, config.n);

  updateSuggestPair();
};
// GameManager::~GameManager() {
//   for (int i = 0; i < B.config.m; i++) {
//     delete[] b[i];
//   }
// }

void GameManager::displayBoard() { showBoard(B); };
void GameManager::displayScore(int stage, int score, string uname) {
  drawScore(stage, score, uname);
};
void GameManager::BackGround() { drawBackground(B); };
void GameManager::saveFile(string name, int stage, int score) {
  using namespace std;
  ofstream fout ("leaderboard.txt", ios::app);
  fout << endl << name << " " << stage << " " << score;
  fout.close();
};
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
    B.c[c_idx.first][c_idx.second].state = 2;

    // if prev cell is not picked, deactivate it
    if (prev_cell != selected_pair.first && prev_cell != selected_pair.second) {
      prev_cell->state = 0;
    }
  }
}

void GameManager::scramble() {
  // save remaining letters to vec
  // vector<char> letters = {};
  // for (int i = 0; i < B.config.m; i++) {
  //   for (int j = 0; j < B.config.n; j++) {
  //     char curr_let = b[i][j];
  //     if ('A' <= curr_let && curr_let <= 'Z') {
  //       letters.push_back(curr_let);
  //     };
  //   }
  // }

  // // scramble vec
  // std::random_shuffle(letters.begin(), letters.end());

  // // generate positions to place letters
  // vector<VECI> positions = {};

  // // exclude borders
  // for (int i = 1; i < B.config.m - 1; i++) {
  //   for (int j = 1; j < B.config.n - 1; j++) {
  //     positions.push_back(VECI{i, j});
  //   };
  // };
  // // scramble position
  // std::random_shuffle(positions.begin(), positions.end());

  // // put letters into positions
  // for (int i = 0; i < letters.size(); i++) {
  //   VECI pos = positions.at(i);
  //   char let = letters.at(i);

  //   b[pos.first][pos.second] = let;
  // }

  // // update struct Board
  // for (int i = 0; i < B.config.m; i++) {
  //   for (int j = 0; j < B.config.n; j++) {
  //     B.c[i][j].c = b[i][j];
  //   }
  // }
  return;
}

Cell *GameManager::getCell(VECI pos) {
  for (int i = 0; i < B.config.m; i++) {
    for (int j = 0; j < B.config.n; j++) {
      if (pos.first == i && pos.second == j) {
        return &B.c[i][j];
      }
    }
  }
  return NULL;
};

bool GameManager::suggestPath() {
  if (suggest_pair.first == NULL || suggest_pair.second == NULL) return false;

  // TODO: draw suggested line  
  Cell *c1 = suggest_pair.first;
  Cell *c2 = suggest_pair.second;  

  correctCells(c1,c2);
 
  return true;
}

void GameManager::checkForMatching() {
  Cell *cell_1 = selected_pair.first;
  Cell *cell_2 = selected_pair.second;

  // must have 2 selected cell.
  if (cell_1 == NULL || cell_2 == NULL) return;

  //  setup astar
  Point start = Point{cell_1->pos};
  Point end = Point{cell_2->pos};
  vector<Point> paths = pathfinder.find_path(start, end);
  cell_1->state = 0;
  cell_2->state = 0;

  // found
  if (paths.size() > 0) {
    correctCells(cell_1, cell_2);
    correctSound();
    for (int i = 0; i < paths.size() - 1; i++)
      drawLine(paths[i].pos, paths[i + 1].pos);
    Sleep(120);
    cell_1->c = ' ';
    cell_1->state = -1;
    cell_2->c = ' ';
    cell_2->state = -1;
    for (int i = 0; i < paths.size() - 1; i++)
      deleteLine(paths[i].pos, paths[i + 1].pos);

    // update char board
    b[cell_1->pos.first][cell_1->pos.second] = ' ';
    b[cell_2->pos.first][cell_2->pos.second] = ' ';

    // add 10 points
    buffer_score += 10;


    // if board clear, don't check suggest pair
    if(checkBoardCleared()) return;

    // check for valid pair, and scramble if board not solveable
    updateSuggestPair();

  } else {
    wrongCells(cell_1, cell_2);
    wrongSound();
    Sleep(120);
    cell_1->state = 0;
    cell_2->state = 0;
  }

  selected_pair.first = NULL;
  selected_pair.second = NULL;

  // highlight cell under cursor
  Cell *c_under_cursor = getCell(c_idx);
  if (c_under_cursor != NULL) c_under_cursor->state = 2;
}; 

void GameManager::pickCell() {
  Cell *c_under_cursor = getCell(c_idx);
  selectSound();
  // cell under cursor is already selected
  if (c_under_cursor == selected_pair.first ||
      c_under_cursor == selected_pair.second)
    return;
  // both cell selected
  if (selected_pair.first != NULL && selected_pair.second != NULL) return;

  // dont select cell if not a letter
  if (c_under_cursor->c == ' ') return;

  if (selected_pair.first == NULL && selected_pair.second == NULL) {
    // first cell selected
    c_under_cursor->state = 1;
    selected_pair.first = c_under_cursor;

  } else {
    // second cell selected
    selected_pair.second = c_under_cursor;
    c_under_cursor->state = 1;
    checkForMatching();
  }
};

void GameManager::updateSuggestPair() {
  pair<Point, Point> paths = pathfinder.suggest_path();
  Point start = paths.first;
  Point end = paths.second;

  while (start == NULL_POINT || end == NULL_POINT) {
    scramble();
    paths = pathfinder.suggest_path();
    start = paths.first;
    end = paths.second;
  }

  suggest_pair.first = getCell(start.pos);
  suggest_pair.second = getCell(end.pos);
}

bool GameManager::checkBoardCleared() {
  for (int i = 0; i < B.config.m; i++) {
    for (int j = 0; j < B.config.n; j++) {
      if (b[i][j] != ' ') {
        cleared = false;
        return false;
      }
    }
  }
  cleared = true;
  return true;
}