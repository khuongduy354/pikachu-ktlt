#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
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
  // 1 selected, 0 normal, -1 deleted, 2 cursor
  int state = 0;
};
struct Board {
  GameConfig config;
  Cell **c;
};

//handle game board
Board generateBoard(GameConfig &config); 
// char Board representation: 2D array of char
// ' ' is empty
// 'A' is letter, B,C,D,...
char **toCharBoard(Board B);  // convert struct board to char board (for pathfinding)
void drawCell(Cell c, Board B);
void showBoard(Board &B);
void deleteBoard();

//visual effects
void wrongCells(Cell *c1, Cell *c2);
void correctCells(Cell *c1, Cell *c2);
void drawLineX(VECI pos1, VECI pos2);
void drawLineY(VECI pos1, VECI pos2);
void drawLine(VECI pos1, VECI pos2);
void deleteLineX(VECI pos1, VECI pos2);
void deleteLineY(VECI pos1, VECI pos2);
void deleteLine(VECI pos1, VECI pos2);
void drawScore(int stage, int score, std::string name);
void drawBackground(Board B);