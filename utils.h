#pragma once

#include <utility>

// pair<int,int> use as integer vector (for coordinates)
#ifndef VECI
#define VECI std::pair<int, int>
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
// map input key to directions
VECI mapCharToPairDir(char a);
