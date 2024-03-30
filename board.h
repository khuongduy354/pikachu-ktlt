#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "console.h"
#include "utils.h"

struct GameConfig {
  int m;               // length
  int n;               // width
  int distinct_chars;  // number of distinct chars appear in the generated board
  int char_occurences[26];  // number of occurences of each char, under the
                            // condition that sum of array is equal to length *
                            // width
};

struct Cell {
  // cell's coordinate
  VECI pos;

  // cell's character
  char c = ' ';

  // 1 selected, 0 normal, -1 deleted
  int state = 0;
};


void wrongCells(Cell *c1, Cell *c2);
void correctCells(Cell *c1, Cell *c2);
void drawCell();

struct Board {
  GameConfig config;
  Cell **c;
};
Board generateBoard(GameConfig &config);
char **toCharBoard(
    Board B);  // convert board to char array (for easier pathfinding)
void showBoard(Board &B);
void deleteBoard();