#include "console.h"

// move cursor to position x,y on terminal
void goToXY(int x, int y) {
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD cursorPosition;
  cursorPosition.X = x;
  cursorPosition.Y = y;
  SetConsoleCursorPosition(console, cursorPosition);
}

// set cursor visiblitiy
void setCursor(bool visible) {
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO lpCursor;
  lpCursor.bVisible = visible;
  lpCursor.dwSize = 20;
  SetConsoleCursorInfo(console, &lpCursor);
}

void resizeWindow(int x, int y) {
  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r);
  MoveWindow(console, r.left, r.top, x, y, TRUE);
}

void hideScrollBar() {
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
  GetConsoleScreenBufferInfo(console, &screenBufferInfo);

  COORD new_screen_buffer_size;

  new_screen_buffer_size.X =
      screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
  new_screen_buffer_size.Y =
      screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

  SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}

void initWindow(int width, int length) {
  resizeWindow(width, length);
  hideScrollBar();
  setCursor(0);
}