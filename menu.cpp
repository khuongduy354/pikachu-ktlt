#include <iostream>
#include <string>

#include "board.h"

class Menu {
  int selected = 1;
  std::string menu_template;
  std::string uname;

  Menu() {
    menu_template =
        " \n \ 
|                                      |  \n \ 
|              Pikachoo!               | \n \
|                                      | \n \ 
|    1. Start                          | \n \
|    2. Quit                           | \n \ 
|                                      | \ 
";
    uname = "";
  };
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
    std::cout << menu_template;
    highlightSelected();
  };
};
