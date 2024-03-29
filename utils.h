#pragma once

#include <Windows.h>

#include <utility>
#include <conio.h>

// pair<int,int> use as integer vector (for coordinates)
#ifndef VECI
#define VECI std::pair<int, int>
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define ENTER 13

// map input key to directions
VECI mapCharToPairDir(char a);

void cls();
VECI getConsoleInput();
