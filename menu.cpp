#include <iostream>
#include <string>
#include <fstream>
#include "board.h"
#include "playSound.h"
using namespace std;
class Menu {
  int selected = 1;
  std::string menu_template;
  std::string uname;

//   Menu() {
//     menu_template =
//         " \n \\ 
// |                                      |  \n \\ 
// |              Pikachoo!               | \n \\
// |                                      | \n \\ 
// |    1. Start                          | \n \\
// |    2. Quit                           | \n \\ 
// |                                      | \\ 
// ";
//     uname = "";
//   };
  void moveSelected() {
    // toggle
    selected = 1 ? 0 : 1;
  }
  void press() {
    if (selected == 1 && uname == "") {
      std::cout << "Input your name: ";
      std::cin >> uname;
    } else if (selected == 1 && uname != "") {
      // TODO: enter game
    } else if (selected == 0) {
      // TODO: quit game
    }
  }
  void highlightSelected() {
    if (selected == 1) {
      // goto start and cout start with color
      //  reset the other color
    } else if (selected == 0) {
    }
  };
  void showMenu() {
    goToXY(0, 0);
    // std::cout << menu_template;
    highlightSelected();
  };
};

void gameTitle() {
  char gameTitle[][71] = {{" ________  ___  ___  __    ________  ________  ___  ___  ___  ___     "},
                          {"|\\   __  \\|\\  \\|\\  \\|\\  \\ |\\   __  \\|\\   ____\\|\\  \\|\\  \\|\\  \\|\\  \\    "},
                          {"\\ \\  \\|\\  \\ \\  \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\ \\  \\   "},
                          {" \\ \\   ____\\ \\  \\ \\   ___  \\ \\   __  \\ \\  \\    \\ \\   __  \\ \\  \\ \\  \\  "},
                          {"  \\ \\  \\___|\\ \\  \\ \\   \\ \\  \\ \\  \\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\ "},
                          {"   \\ \\__\\    \\ \\__\\ \\__ \\ \\__\\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\_______\\"},
                          {"    \\|__|     \\|__|\\|__| \\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______|"}};     
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
  for (int i = 0; i < 7; i++) {
    goToXY(3 * 7 + 5, 1 + i);
    cout << gameTitle[i];
  }
}

void getPlayerInfor() {
  char table[][63] =        {{" ------------------------------------------------------------ "},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {" ------------------------------------------------------------ "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
  for (int i = 0; i < 9; i++) {
    goToXY(3 * 7 + 7, 11 + i);
      cout << "                                                                  ";
    }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  for (int i = 0; i < 7; i++) {
    goToXY(3 * 7 + 9, 12 + i);
      cout << table[i];
    }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
  goToXY(7 * 7 + 3, 13);
  cout << "ENTER YOUR NAME";
  goToXY(6 * 7 + 5, 14);
  cout << "(Less than 10 characters)";
  goToXY(5 * 7 + 3, 16);
  cout << "Player: ";
  char input[][25] = {{" ---------------------- "},
                      {"|                      |"},
                      {" ---------------------- "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  for (int i = 0; i < 3; i++) {
    goToXY(7 * 7 + 6, 15 + i);
      cout << input[i];
    }
  setCursor(true);
  goToXY(7 * 7 + 8, 16);
  string name;
  do {
    getline(cin, name);
    if (name.length() > 10)
    {
      setCursor(false);
      goToXY(7 * 7 + 8, 16);
      for (int i = 0; i < name.length() + 1; i++)
        cout << " ";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
      goToXY(5 * 7 + 3, 14);
      cout << "Your name must contain less than 10 characters!";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      goToXY(7 * 7 + 8, 16);
      setCursor(true);
    }
  } while (name.length() > 10);
  ofstream fout ("leaderboard.txt");
  fout << name << " ";
  fout.close(); 
}


void LeaderBoard() {
  using namespace std;
  setCursor(false);
  char title[][99] = {{" ,--.   ,------.  ,---.  ,------.  ,------.,------. ,-----.   ,-----.   ,---.  ,------. ,------.  "},
                      {"|   |   |  .---' /  O  \\ |  .-.  \\ |  .---'|  .--. '|  |) /_ '  .-.  ' /  O  \\ |  .--. '|  .-.  \\ "},
                      {"|   |   |  `--, |  .-.  ||  |  \\  :|  `--, |  '--'.'|  .-.  \\|  | |  ||  .-.  ||  '--'.'|  |  \\  :"},
                      {"|   '--.|  `---.|  | |  ||  '--'  /|  `---.|  |\\  \\ |  '--' /'  '-'  '|  | |  ||  |\\  \\ |  '--'  /"},
                      {"`-----'`------'`--' `--'`-------' `------'`--' '--'`------'  `-----' `--' `--'`--' '--'`-------'  "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
  for (int i = 0; i < 5; i++) {
    goToXY(1 * 7 + 5, 1 + i);
    cout << title[i];
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
  for (int i = 1; i < 4; i++) {
    goToXY(3 * 7 + 5 + 4, 7 + i);
    cout << "                                                             ";
  }
  goToXY(5 * 7 + 6, 9);
  cout << "PLAYER";
  goToXY(9 * 7 + 1, 9);
  cout << "STAGE";
  goToXY(11 * 7 + 4, 9);
  cout << "SCORE";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  char learderBoard[][62] = {{" -------------------------- ----------------- -------------- "},
                             {"|                          |                 |              |"},
                             {" -------------------------- ----------------- -------------- "}};
  ifstream fin ("leaderboard.txt");
  string name[50] = {" "};
  int stage[50];
  int score[50];
  int k = 0;
  while (!fin.eof()) {
    getline(fin, name[k], ' ');
    fin >> stage[k];
    fin >> score[k];
    fin.get();
    k++;
  }
  int max_pos;
  for (int i = 0; i < k; i++)
  {
    max_pos = i;
    for (int j = i + 1; j < k; j++) {
      if (score[j] > score[max_pos])
        max_pos = j;
      }
      if (max_pos != i) {
        swap(score[max_pos], score[i]);
        swap(stage[max_pos], stage[i]);
        swap(name[max_pos], name[i]);
      }
    }
  int n = 0;
  while (n < 5) {
    for (int i = 0; i < 3; i++) {
      goToXY(3 * 7 + 5 + 4, 11 + n * 3 + i);
      cout << learderBoard[i];
    }
    goToXY(5 * 7 + 7, 12 + n * 3);
    cout << name;
    goToXY(9 * 7 + 3, 12 + n * 3);
    cout << stage;
    goToXY(11 * 7 + 5, 12 + n * 3);
    cout << score;
    n++;
  } 
  goToXY(3 * 7 + 5 + 4, 15 + n * 3);
  cout << "(Press Space to return to Menu)";

  fin.close();
}

void endGame(int score)
{
  setCursor(false);
  endSound();
  char end[][63] = {{"  _____          __  __ ______    ______      ________ _____  "},
                    {" / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ "},
                    {"| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |"},
                    {"| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / "},
                    {"| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ "},
                    {" \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\"}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
  for (int i = 0; i < 6; i++) {
    goToXY(4 * 7 + 2, 1 + i);
    cout << end[i];
  }
  char table[][63] =        {{" ------------------------------------------------------------ "},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {"|                                                            |"},
                             {" ------------------------------------------------------------ "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
  for (int i = 0; i < 8; i++) {
    goToXY(3 * 7 + 7, 13 + i);
      cout << "                                                                 ";
    }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
  for (int i = 0; i < 6; i++) {
    goToXY(3 * 7 + 9, 14 + i);
      cout << table[i];
    }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
  for (int i = 0; i < 4; i++) {
    goToXY(3 * 7 + 10, 15 + i);
      cout << "                                                            ";
    }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 115);
  goToXY(6 * 7 + 8, 16);
  cout << "YOUR SCORE: ";
  goToXY(7 * 7 + 18, 16);
  cout << score;
  goToXY(6 * 7 + 3, 18);
  cout << "(Press Space to return to Menu)";
}

