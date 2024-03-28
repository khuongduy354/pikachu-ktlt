#include "Astar.h"

#include <iostream>

#include "board.h"

char **setup_board(char b[MAX_ARR_SIZE][MAX_ARR_SIZE], int size) {
  char **board = new char *[size];
  for (int i = 0; i < size; i++) {
    board[i] = new char[size];
    for (int j = 0; j < size; j++) {
      board[i][j] = b[i][j];
    }
  }
  return board;
}
int basic_finding() {
  // 10
  char b1[MAX_ARR_SIZE][MAX_ARR_SIZE] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'x', 'A', 'x', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'x', 'x', 'x', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', 'A', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

  char **board = setup_board(b1, 10);
  Astar::AstarGrid astar = Astar::AstarGrid(board, 10, 10);
  //   cout << "Scan order: " << endl;
  std::vector<Astar::Point> *path =
      astar.find_path(Astar::Point{1, 1}, Astar::Point{8, 8});
  if (path == NULL) {
    std::cout << "No path found" << std::endl;
  } else {
    std::cout << std::endl;
    std::cout << "Found Path size: " << path->size() << std::endl;
    std::cout << "Path from destination to start: " << std::endl;
    for (Astar::Point p : *path) {
      std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
  }
}

int _main2() {
  GameConfig config = {4, 5, 4, {2, 4, 6, 8}};
  Board B = generateBoard(config);
  Astar::AstarGrid astar = Astar::AstarGrid(toCharBoard(B), config.m, config.n);
  astar.display_board();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  int a;
  std::cin >> a;
  system("cls");
  showBoard(B);
}

// int main() { basic_finding(); }