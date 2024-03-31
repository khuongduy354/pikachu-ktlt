#include "utils.h"

VECI getConsoleInput()
{
	switch (_getch()) {
	case KEY_UP:			
		return VECI{-1, 0};
	case KEY_LEFT:			
		return VECI{0, -1};
	case KEY_RIGHT:				
		return VECI{0, 1};
	case KEY_DOWN:				
		return VECI{1, 0};
	case ENTER:				
		return VECI{-2, -2};
  default:
    return VECI{0, 0};
	}
}
