#include "utils.h"

VECI mapCharToPairDir(char a) {
  switch (a) {
    case 'w':
      return VECI{-1, 0};
    case 's':
      return VECI{1, 0};
    case 'a':
      return VECI{0, -1};
    case 'd':
      return VECI{0, 1};
  }
  return VECI{0, 0};
}