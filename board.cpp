#include "board.h"

// border of a cell
char box[5][12] = {{" --------- "},
                   {"|         |"},
                   {"|         |"},
                   {"|         |"},
                   {" --------- "}};
//Function to draw a cell in the board
void drawCell(Cell c) {
  using namespace std;
  int x = c.pos.second + 1, y = c.pos.first + 1;
  for (int i = 0; i < 5; i++) {
    goToXY(x * 10, y * 4 + i);
    cout << box[i];
    }
  if (c.state == 1) { //selected 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 100 + (c.c % 6 + 1)); // draw yellow background
    for (int i = 1; i < 4; i++) {
      goToXY(x * 10 + 1, y * 4 + i);
      cout << "         ";
      }
    goToXY(x * 10 + 5, y * 4 + 2);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
  else if (c.state == 2) { //cursor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + (c.c % 6 + 1)); // draw white background
    for (int i = 1; i < 4; i++) {
      goToXY(x * 10 + 1, y * 4 + i);
      cout << "         ";
      }
    goToXY(x * 10 + 5, y * 4 + 2);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
  else if (c.state == -1) { // deleted
    for (int i = 1; i < 4; i++) {
      goToXY(x * 10 + 1, y * 4 + i);
      cout << "         ";
        }
  }
  else { // normal state
    goToXY(x * 10 + 5, y * 4 + 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.c % 6 + 1);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }  
}

void wrongCells(Cell *c1, Cell *c2)
{
  //first cell
  int x1 = c1->pos.second + 1, y1 = c1->pos.first + 1;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 70 + (c1->c % 6 + 1)); // draw red background
  for (int i = 1; i < 4; i++) {
      goToXY(x1 * 10 + 1, y1 * 4 + i);
      std::cout << "         ";
      }
  goToXY(x1 * 10 + 5, y1 * 4 + 2);
  std::cout << c1->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  //second cell
  int x2 = c2->pos.second + 1, y2 = c2->pos.first + 1;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 70 + (c2->c % 6 + 1)); // draw red background
  for (int i = 1; i < 4; i++) {
      goToXY(x2 * 10 + 1, y2 * 4 + i);
      std::cout << "         ";
      }
  goToXY(x2 * 10 + 5, y2 * 4 + 2);
  std::cout << c2->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void correctCells(Cell *c1, Cell *c2)
{
  //first cell
  int x1 = c1->pos.second + 1, y1 = c1->pos.first + 1;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 + (c1->c % 6 + 1)); // draw green background
  for (int i = 1; i < 4; i++) {
      goToXY(x1 * 10 + 1, y1 * 4 + i);
      std::cout << "         ";
      }
  goToXY(x1 * 10 + 5, y1 * 4 + 2);
  std::cout << c1->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  //second cell
  int x2 = c2->pos.second + 1, y2 = c2->pos.first + 1;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 + (c2->c % 6 + 1)); // draw green background
  for (int i = 1; i < 4; i++) {
      goToXY(x2 * 10 + 1, y2 * 4 + i);
      std::cout << "         ";
      }
  goToXY(x2 * 10 + 5, y2 * 4 + 2);
  std::cout << c2->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// function to generate distinct random int for generating board in
// generateBoard function below
int getRandomInt(int begin, int end) {
  using namespace std;

  static random_device rd;
  static mt19937 mt(rd());
  uniform_int_distribution<int> dist(begin, end);
  return dist(mt);
}
// function to get generated chars in the board
char **toCharBoard(Board B) {
  char **board = new char *[B.config.m];
  for (int i = 0; i < B.config.m; i++) {
    board[i] = new char[B.config.n];
    for (int j = 0; j < B.config.n; j++) {
      board[i][j] = B.c[i][j].c;
    }
  }
  return board;
}
// function to generate board
Board generateBoard(GameConfig &config)
{
  if (config.m * config.n % 2 == 0)
  {
    // Generate random chars
    char *ran_chars;
    ran_chars = new char[config.distinct_chars];
    for (int i = 0; i < config.distinct_chars; i++)
      ran_chars[i] = static_cast<char>(getRandomInt(65, 90));
    // Generate board
    char *chars;
    chars = new char[config.m * config.n];
    int index = 0;
    for (int i = 0; i < config.distinct_chars; i++)
      for (int j = 0; j < config.char_occurences[i]; j++)
        chars[index++] = ran_chars[i];
    Board B;
    B.config.m = config.m;
    B.config.n = config.n;
    B.config.distinct_chars = config.distinct_chars;
    for (int i = 0; i < config.distinct_chars; i++)
      B.config.char_occurences[i] = config.char_occurences[i];
    B.c = new Cell *[config.m + 2];
    for (int i = 0; i < config.m + 2; i++)
    {
      B.c[i] = new Cell[config.n + 2];
      for (int j = 0; j < config.n + 2; j++)
      {
        if (i == 0 || i == config.m + 1 || j == 0 || j == config.n + 1)
        {
          B.c[i][j].pos.first = i;
          B.c[i][j].pos.second = j;
          B.c[i][j].c = ' ';
          B.c[i][j].state = -1;
        }
        else 
        {
          B.c[i][j].pos.first = i;
          B.c[i][j].pos.second = j;
          B.c[i][j].c = chars[getRandomInt(0, config.m * config.n - 1)];
          B.c[i][j].state = 0;
        }
      }
    }
    config.m += 2;
    config.n += 2;
    B.config.m += 2;
    B.config.n += 2;
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
void showBoard(Board &B) {
  for (int i = 0; i < B.config.m; i++) {
    for (int j = 0; j < B.config.n; j++) {
      drawCell(B.c[i][j]);
    }
  }
}

//---------------------------------------------------------------
// draw line
void drawLineX(VECI pos1, VECI pos2) {
  int x1, y1, x2, y2;
  if (pos1 < pos2) {
    x1 = pos1.first * 10 + 5, y1 = pos1.second * 4 + 2;
    x2 = pos2.first * 10 + 5, y2 = pos2.second * 4 + 2;
  }
  else {
    x1 = pos2.first * 10 + 5, y1 = pos2.second * 4 + 2;
    x2 = pos1.first * 10 + 5, y2 = pos1.second * 4 + 2;
  }
  for (int i = 0; i < x2 - x1; i++) {
    goToXY(x1 + i, y1);
    std::cout << "-";
  }
}

void drawLineY(VECI pos1, VECI pos2) {
  int x1, y1, x2, y2;
  if (pos1 < pos2) {
    x1 = pos1.first * 10 + 5, y1 = pos1.second * 4 + 2;
    x2 = pos2.first * 10 + 5, y2 = pos2.second * 4 + 2;
  }
  else {
    x1 = pos2.first * 10 + 5, y1 = pos2.second * 4 + 2;
    x2 = pos1.first * 10 + 5, y2 = pos1.second * 4 + 2;
  }
  for (int i = 0; i < y2 - y1; i++)
  {
    goToXY(x2, y1 + i);
    std::cout << "|";
  }
}

void drawLine(VECI pos1, VECI pos2) {
  if (pos1.first == pos2.first)
    drawLineY(pos1, pos2);
  else 
    drawLineX(pos1, pos2);
}

void deleteLineX(VECI pos1, VECI pos2) {
  int x1, y1, x2, y2;
  if (pos1 < pos2) {
    x1 = pos1.first * 10 + 5, y1 = pos1.second * 4 + 2;
    x2 = pos2.first * 10 + 5, y2 = pos2.second * 4 + 2;
  }
  else {
    x1 = pos2.first * 10 + 5, y1 = pos2.second * 4 + 2;
    x2 = pos1.first * 10 + 5, y2 = pos1.second * 4 + 2;
  }
  for (int i = 0; i < x2 - x1; i++) {
    goToXY(x1 + i, y1);
    std::cout << " ";
  }
}

void deleteLineY(VECI pos1, VECI pos2) {
  int x1, y1, x2, y2;
  if (pos1 < pos2) {
    x1 = pos1.first * 10 + 5, y1 = pos1.second * 4 + 2;
    x2 = pos2.first * 10 + 5, y2 = pos2.second * 4 + 2;
  }
  else {
    x1 = pos2.first * 10 + 5, y1 = pos2.second * 4 + 2;
    x2 = pos1.first * 10 + 5, y2 = pos1.second * 4 + 2;
  }
  for (int i = 0; i < y2 - y1; i++)
  {
    goToXY(x2, y1 + i);
    std::cout << " ";
  }
}

void deleteLine(VECI pos1, VECI pos2) {
  if (pos1.first == pos2.first)
    deleteLineY(pos1, pos2);
  else 
    deleteLineX(pos1, pos2);
}