#include "board.h"

// border of a cell
char box[4][9] =  {{" ------ "},
                   {"|      |"},
                   {"|      |"},
                   {" ------ "}};
//Function to draw a cell in the board
void drawCell(Cell c) {
  using namespace std;
  float x = c.pos.second, y = c.pos.first;
  if (c.c != ' ')
  {
    for (int i = 0; i < 4; i++) {
    goToXY(x * 7, y * 3 + i);
    cout << box[i];
    }
  }
  if (c.state == 1) { //selected 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 100 + (c.c % 6 + 1)); // draw yellow background
    for (int i = 1; i < 3; i++) {
      goToXY(x * 7 + 1, y * 3 + i);
      cout << "      ";
      }
    goToXY(x * 7 + 3, y * 3 + 1);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
  else if (c.state == 2) { //cursor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + (c.c % 6 + 1)); // draw white background
    for (int i = 1; i < 3; i++) {
      goToXY(x * 7 + 1, y * 3 + i);
      cout << "      ";
      }
      goToXY(x * 7 + 3, y * 3 + 1);
      cout << c.c;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
  else if (c.state == -1 || c.c == ' ') { // deleted
    for (int i = 1; i < 3; i++) {
      goToXY(x * 7 + 1, y * 3 + i);
      cout << "      ";
        }
  }
  else { // normal state
    goToXY(x * 7 + 3, y * 3 + 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.c % 6 + 1);
    cout << c.c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }  
}

void wrongCells(Cell *c1, Cell *c2)
{
  //first cell
  int x1 = c1->pos.second, y1 = c1->pos.first;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 70 + (c1->c % 6 + 1)); // draw red background
  for (int i = 1; i < 3; i++) {
      goToXY(x1 * 7 + 1, y1 * 3 + i);
      std::cout << "      ";
      }
  goToXY(x1 * 7 + 3, y1 * 3 + 1);
  std::cout << c1->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  //second cell
  int x2 = c2->pos.second, y2 = c2->pos.first;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 70 + (c2->c % 6 + 1)); // draw red background
  for (int i = 1; i < 3; i++) {
      goToXY(x2 *7 + 1, y2 * 3 + i);
      std::cout << "      ";
      }
  goToXY(x2 * 7 + 3, y2 * 3 + 1);
  std::cout << c2->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void correctCells(Cell *c1, Cell *c2)
{
  //first cell
  int x1 = c1->pos.second, y1 = c1->pos.first;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 + (c1->c % 6 + 1)); // draw green background
  for (int i = 1; i < 3; i++) {
      goToXY(x1 * 7 + 1, y1 * 3 + i);
      std::cout << "      ";
      }
  goToXY(x1 * 7 + 3, y1 * 3 + 1);
  std::cout << c1->c;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  //second cell
  int x2 = c2->pos.second, y2 = c2->pos.first;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 + (c2->c % 6 + 1)); // draw green background
  for (int i = 1; i < 3; i++) {
      goToXY(x2 * 7 + 1, y2 * 3 + i);
      std::cout << "      ";
      }
  goToXY(x2 * 7 + 3, y2 * 3 + 1);
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
    for (int i = 0; i < config.m + 2; i++) {
      B.c[i] = new Cell[config.n + 2];
      for (int j = 0; j < config.n + 2; j++) {
        if (i == 0 || i == config.m + 1 || j == 0 || j == config.n + 1) {
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
  } else {
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
  int x1, x2;
  int y = pos1.first * 3 + 1;
  if (pos1.second < pos2.second) {
    x1 = pos1.second * 7 + 3;
    x2 = pos2.second * 7 + 3;
  }
  else {
    x1 = pos2.second * 7 + 3;
    x2 = pos1.second * 7 + 3;
  }
  for (int i = 0; i < x2 - x1; i++) {
    goToXY(x1 + i, y);
    std::cout << "-";
  }
}

void drawLineY(VECI pos1, VECI pos2) {
  int y1, y2;
  int x = pos1.second * 7 + 3.5;
  if (pos1.first < pos2.first) {
    y1 = pos1.first * 3 + 1.5;
    y2 = pos2.first * 3 + 1.5;
  }
  else {
    y1 = pos2.first * 3 + 1.5;
    y2 = pos1.first * 3 + 1.5;
  }
  for (int i = 0; i < y2 - y1; i++)
  {
    goToXY(x, y1 + i);
    std::cout << "|";
  }
}

void drawLine(VECI pos1, VECI pos2) {
  if (pos1.first == pos2.first)
    drawLineX(pos1, pos2);
  else if (pos1.second == pos2.second)
    drawLineY(pos1, pos2);
}

void deleteLineX(VECI pos1, VECI pos2) {
int x1, x2;
  int y = pos1.first * 3 + 1;
  if (pos1.second < pos2.second) {
    x1 = pos1.second * 7 + 3;
    x2 = pos2.second * 7 + 3;
  }
  else {
    x1 = pos2.second * 7 + 3;
    x2 = pos1.second * 7 + 3;
  }
  for (int i = 0; i < x2 - x1; i++) {
    goToXY(x1 + i, y);
    std::cout << " ";
  }
}

void deleteLineY(VECI pos1, VECI pos2) {
  int y1, y2;
  int x = pos1.second * 7 + 3.5;
  if (pos1.first < pos2.first) {
    y1 = pos1.first * 3 + 1.5;
    y2 = pos2.first * 3 + 1.5;
  }
  else {
    y1 = pos2.first * 3 + 1.5;
    y2 = pos1.first * 3 + 1.5;
  }
  for (int i = 0; i < y2 - y1; i++)
  {
    goToXY(x, y1 + i);
    std::cout << " ";
  }
}

void deleteLine(VECI pos1, VECI pos2) {
  if (pos1.first == pos2.first)
    deleteLineX(pos1, pos2);
  else 
    deleteLineY(pos1, pos2);
}

//---------------------------------

void drawScore(int stage, int score, std::string name) {
  using namespace std;
  int x = 13, y = 1;
  char scoreBox[9][30] = {{" --------------------------- "},
                           {"|         STAGE             |"},
                           {"|---------------------------|"},
                           {"|  -----------------------  |"},
                           {"| |  PLAYER  |            | |"},
                           {"| |          |            | |"},
                           {"| |  SCORE   |            | |"},
                           {"|  -----------------------  |"},
                           {" --------------------------- "}};
  for (int i = 0; i < 9; i++) {
    goToXY(x*7, y*3 + i);
    cout << scoreBox[i];
  } 
  goToXY(15 * 7 + 2, 3 + 6);
  cout << score;
  goToXY(15 * 7 + 2, 3 + 4);
  cout << name;
  goToXY(15 * 7 + 3, 3 + 1);
  cout << stage;
}

void drawBackground(Board B)
{
  using namespace std;
  string bg[8][8][4] = {{{{" _______"},{"|       "},{"|       "},{"|       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"       "},{"       "},{"       "}},{{"_______"},{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"    \\`*"}},{{"       "},{"       "},{"-.     "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"     ) "},{"    .  "},{"    : _"}},{{" _`-.  "},{": `. . "},{"   '  \\"}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"    ; *"},{"    `-."},{"      ;"}},{{"` _.   "},{"-'     "},{"       "}},{{"`*-._  "},{"     `-"},{"`      "}},{{"       "},{".      "},{" `.    "}},{{"       "},{"       "},{"       "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{":.     "},{". \\  . "},{"'  `+.;"}},{{"   .   "},{"  :   ."},{"  ;  ' "}},{{"    \\  "},{"-'   . "},{"     : "}},{{"       "},{"       "},{"       "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"       "},{"       "},{"     .*"}},{{":  '  |"},{"; '   :"},{"' /  .*"}},{{"    ;  "},{" :`-:  "},{"' ; .*`"}},{{"     ;-"},{"   _.`*"},{"`- +'  `"}},{{".      "},{" ;     "},{"*'     "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|       "},{"|       "},{"|       "}},{{"       "},{"       "},{"       "}},{{"     `*"},{"       "},{"       "}},{{"-*   `*"},{"       "},{"       "}},{{"-*  `*-"},{"       "},{"       "}},{{"*'     "},{"       "},{"       "}},{{"       "},{"       "},{"       "}},{{"      |"},{"      |"},{"      |"}}},
                     {{{"|_______"},{"|_______"},{"|_______"}},{{"_______"},{"_______"},{"_______"}},{{"_______"},{"_______"},{"_______"}},{{"_______"},{"_______"},{"_______"}},{{"_______"},{"_______"},{"_______"}},{{"_______"},{"_______"},{"_______"}},{{"_______"},{"_______"},{"_______"}},{{"______|"},{"______|"},{"______|"}}}
  };
  for (int i = 1; i < 9; i++){
    for (int j = 1; j < 9; j++){
      for (int k = 0; k < 4; k++)
      { 
        if (i != 1 && k == 3)
          continue;
        if (B.c[i][j].c == ' ')
        {
          goToXY(j * 7, i * 3 + k);
          cout << bg[i - 1][j - 1][k];
        }
      }   
    }
  } 
}
