#include "board.h"

// border of a cell
char box[5][12] = {
    {" --------- "},
    {"|         |"},
    {"|         |"},
    {"|         |"},
    {" --------- "}};
// Function to draw a cell in the board
void drawCell(Cell c, int color)
{
    // check the state of cell, -1 means deleted cell
  if (c.state == -1)
    return;
    // draw border of the cell
  int x = c.j + 1, y = c.i + 1;
  for (int i = 0; i < 5; i++)
  {
    goToXY(x * 10, y * 4 + i);
    cout << box[i];
  }
    // 1 means selected cell
  if (c.state == 1)
  {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c.c % 6 + 1)); 
      // draw white background
    for (int i = 1; i < 4; i++)
    {
      goToXY(x * 10 + 1, y * 4 + i);
      cout << "         ";
    }
    goToXY(x * 10 + 5, y * 4 + 2);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  }
      // normal state
  else
  {
    goToXY(x * 10 + 5, y * 4 + 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.c % 6 + 1);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  }
}

void deleteCell(Cell c)
{
  int x = c.j + 1, y = c.i + 1;
  for (int i = 0; i < 5; i++)
  {
    goToXY(x * 10, y * 4 + i);
    cout << "           ";
  }
}
// function to generate distinct random int for generating board in generateBoard function below
int getRandomInt(int begin, int end)
{
  static random_device rd;
  static mt19937 mt(rd());
  uniform_int_distribution<int> dist(begin, end);
  return dist(mt);
}
// function to get generated chars in the board
char **toCharBoard(const Board &B)
{
  char **board;
  board = new char *[B.config.m];
  for (int i = 0; i < B.config.m; i++)
  {
    for (int j = 0; j < B.config.n; j++)
      board[i][j] = B.c[i][j].c;
  }
  return board;
}
// function to generate board
Board generateBoard(GameConfig config)
{
  if (config.m * config.n % 2 == 0)
  {
    // Generate random chars
    char *ran_chars;
    ran_chars = new char[config.distinct_chars];
    for (int i = 0; i < config.distinct_chars; i++)
      ran_chars[i] = static_cast<char>(getRandomInt(65, 90));
    // Generate board
      //Generate total chars of the board form random chars generated above
    char *chars;
    chars = new char[config.m * config.n];
    int index = 0;
    for (int i = 0; i < config.distinct_chars; i++)
      for (int j = 0; j < config.char_occurences[i]; j++)
        chars[index++] = ran_chars[i];
      // attach the value of game configures to that of Board
    Board B;
    B.config.m = config.m;
    B.config.n = config.n;
    B.config.distinct_chars = config.distinct_chars;
    for (int i = 0; i < config.distinct_chars; i++)
      B.config.char_occurences[i] = config.char_occurences[i];
    B.c = new Cell *[config.m];
    for (int i = 0; i < config.m; i++)
    {
      B.c[i] = new Cell[config.n];
      for (int j = 0; j < config.n; j++)
      {
        B.c[i][j].i = i;
        B.c[i][j].j = j;
        B.c[i][j].c = chars[getRandomInt(0, config.m * config.n - 1)];
        B.c[i][j].state = 0;
      }
    }
    delete[] ran_chars;
    delete[] chars;
    return B;
  }
  else
  {
    Board b;
    return b;
  }
}
// function to draw the whole board on the screen
void showBoard(Board &B)
{
  for (int i = 0; i < B.config.m; i++)
    for (int j = 0; j < B.config.n; j++)
      drawCell(B.c[i][j], 112);
}
