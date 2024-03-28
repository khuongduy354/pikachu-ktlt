#include "Astar.h"

#include <iostream>

#include "board.h"

char **setup_board(char b[100][100], int size) {
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
  // 10x10
  char b1[100][100] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
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
  AstarGrid astar = AstarGrid(board, 10, 10);
  //   cout << "Scan order: " << endl;
  std::vector<Point> path = astar.find_path(Point{1, 1}, Point{8, 8});
  if (path.size() == 0) {
    std::cout << "No path found" << std::endl;
  } else {
    std::cout << std::endl;
    std::cout << "Found Path size: " << path.size() << std::endl;
    std::cout << "Path from destination to start: " << std::endl;
    for (Point p : path) {
      std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
  }
}

int _main2() {
  GameConfig config = {4, 5, 4, {2, 4, 6, 8}};
  Board B = generateBoard(config);
  AstarGrid astar = AstarGrid(toCharBoard(B), config.m, config.n);
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