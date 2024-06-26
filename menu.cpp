#include "menu.h"

#include <fstream>
#include <iostream>
#include <string>

#include "board.h"
#include "playSound.h"
void Menu::moveSelected() {
  // toggle between 3 options: start, leaderboard, quit
  selected = (selected + 1) % 3;
}

void Menu::showScreen() {  
  // show leaderboard  has higher priority than menu
  if (show_leaderboard) {  
    LeaderBoard();
  } else if (uname == "") { 
    // if uname is not empty, means user typed name and entered game 
    showMenu();
  }
  menuSound();
}

void Menu::press() {
  if (show_leaderboard) { 
    // turn off leaderboard if is showing
    system("cls");
    show_leaderboard = false;
    return;
  }

  if (selected == 0 && uname == "") { 
    // start is pressed (idx = 0) and allowing input name
    getPlayerInfor(); 
    goToXY(7 * 7, 20);
    std::cout << "Press enter to start game!";
  } else if (uname != "") { 
    // enter game if name is inputted
    system("cls");
    enter_game = true;
  } else if (selected == 1) { 
    // show leaderboard if leaderboard is pressed (idx = 1)
    system("cls");
    show_leaderboard = true;
  } else if (selected == 2) { 
    // exit pressed (idx = 2)
    exit(0);
  }
}
void Menu::showMenu() { 
  // draw main menu
  goToXY(0, 0);
  gameTitle();
  std::cout << endl;

  goToXY(7 * 6, 14);
  std::cout << "Press arrow key to move down & Enter to select." << endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          selected == 0 ? 14 : 15);
  goToXY(7 * 7 + 8, 16);
  std::cout << "Start" << endl;

  goToXY(7 * 7 + 8, 17);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          selected == 1 ? 14 : 15);
  std::cout << "Leaderboard" << endl;

  goToXY(7 * 7 + 8, 18);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          selected == 2 ? 14 : 15);
  std::cout << "Quit" << endl;
};

void Menu::gameTitle() {
  char gameTitle[][71] = {
      {" ________  ___  ___  __    ________  ________  ___  ___  ___  ___    "
       " "},
      {"|\\   __  \\|\\  \\|\\  \\|\\  \\ |\\   __  \\|\\   ____\\|\\  \\|\\  "
       "\\|\\  \\|\\  \\    "},
      {"\\ \\  \\|\\  \\ \\  \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\___|\\ \\  "
       "\\ \\  \\ \\  \\ \\  \\   "},
      {" \\ \\   ____\\ \\  \\ \\   ___  \\ \\   __  \\ \\  \\    \\ \\   __  "
       "\\ \\  \\ \\  \\  "},
      {"  \\ \\  \\___|\\ \\  \\ \\   \\ \\  \\ \\  \\ \\  \\ \\  \\____\\ \\  "
       "\\ \\  \\ \\  \\ \\  \\ "},
      {"   \\ \\__\\    \\ \\__\\ \\__ \\ \\__\\ \\__\\ \\__\\ \\_______\\ "
       "\\__\\ \\__\\ \\_______\\"},
      {"    \\|__|     \\|__|\\|__| "
       "\\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______|"}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
  for (int i = 0; i < 7; i++) {
    goToXY(3 * 7 + 5, 1 + i);
    cout << gameTitle[i];
  }
}
void Menu::getPlayerInfor() { 
  // prompt panel for user input 
  char table[][63] = {
      {" ------------------------------------------------------------ "},
      {"|                                                            |"},
      {"|                                                            |"},
      {"|                                                            |"},
      {"|                                                            |"},
      {"|                                                            |"},
      {" ------------------------------------------------------------ "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
  for (int i = 0; i < 9; i++) {
    goToXY(3 * 7 + 7, 11 + i);
    cout
        << "                                                                  ";
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
  do {
    getline(cin, uname);
    if (uname.length() > 10) {
      setCursor(false);
      goToXY(7 * 7 + 8, 16);
      for (int i = 0; i < uname.length() + 1; i++) cout << " ";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
      goToXY(5 * 7 + 3, 14);
      cout << "Your name must contain less than 10 characters!";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      goToXY(7 * 7 + 8, 16);
      setCursor(true);
    }
  } while (uname.length() > 10);
}

void Menu::LeaderBoard() { 
  // draw leaderboard
  using namespace std;
  setCursor(false);
  char title[][99] = {{" ,--.   ,------.  ,---.  ,------.  ,------.,------. "
                       ",-----.   ,-----.   ,---.  ,------. ,------.  "},
                      {"|   |   |  .---' /  O  \\ |  .-.  \\ |  .---'|  .--. "
                       "'|  |) /_ '  .-.  ' /  O  \\ |  .--. '|  .-.  \\ "},
                      {"|   |   |  `--, |  .-.  ||  |  \\  :|  `--, |  '--'.'| "
                       " .-.  \\|  | |  ||  .-.  ||  '--'.'|  |  \\  :"},
                      {"|   '--.|  `---.|  | |  ||  '--'  /|  `---.|  |\\  \\ "
                       "|  '--' /'  '-'  '|  | |  ||  |\\  \\ |  '--'  /"},
                      {"`-----'`------'`--' `--'`-------' `------'`--' "
                       "'--'`------'  `-----' `--' `--'`--' '--'`-------'  "}};
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
  for (int i = 0; i < 5; i++) {
    goToXY(1 * 7 + 5, 1 + i);
    cout << title[i];
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 * 16);
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
  char learderBoard[][62] = {
      {" -------------------------- ----------------- -------------- "},
      {"|                          |                 |              |"},
      {" -------------------------- ----------------- -------------- "}};
  ifstream fin("leaderboard.txt");
  string name[50] = {" "};
  int stage[50];
  int score[50];
  int k = 0;
  while (getline(fin, name[k], ' ')) {
    fin >> stage[k];
    fin >> score[k];
    fin.get();
    k++;
  }
  int max_pos;
  for (int i = 0; i < k; i++) {
    max_pos = i;
    for (int j = i + 1; j < k; j++) {
      if (score[j] > score[max_pos]) max_pos = j;
    }
    if (max_pos != i) {
      swap(score[max_pos], score[i]);
      swap(stage[max_pos], stage[i]);
      swap(name[max_pos], name[i]);
    }
  }
  int n = 0;
  while (n < 4) {
    for (int i = 0; i < 3; i++) {
      goToXY(3 * 7 + 5 + 4, 11 + n * 3 + i);
      cout << learderBoard[i];
    }
    goToXY(5 * 7 + 7, 12 + n * 3);
    cout << name[n];
    goToXY(9 * 7 + 3, 12 + n * 3);
    cout << stage[n];
    goToXY(11 * 7 + 5, 12 + n * 3);
    cout << score[n];
    n++;
  }
  goToXY(3 * 7 + 5 + 20, 16 + n * 3);
  cout << "(Press Enter to return to Menu)";

  fin.close();
}
