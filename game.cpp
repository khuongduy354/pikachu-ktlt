#include <iostream>
#include "board.h"
#include "Astar.h"
using namespace std;

#ifndef VECI //integer vector(x,y)
#define VECI pair<int, int>
#endif

VECI mapCharToPairDir(char a);
class GameManager
{
    Board B;

    // selected pair
    pair<Cell *, Cell *> selected_pair{NULL, NULL};

    // cursor index
    VECI c_idx;

public:
    GameManager(GameConfig config)
    {
        this->B = generateBoard(config);
        c_idx = VECI{0, 0};
        this->B.c[0][0].state = 1;
    }

    static VECI mapCharToPairDir(char a)
    {
        switch (a)
        {
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
    void displayBoard()
    {
        showBoard(B);
    }

    void moveCursor(VECI dir)
    {
        // wrap around grid
        int ncell_i = (c_idx.first + dir.first) % B.config.m;
        int ncell_j = (c_idx.second + dir.second) % B.config.n;

        if (ncell_i < 0)
            ncell_i = B.config.m - 1;

        if (ncell_j < 0)
            ncell_j = B.config.n - 1;

        // previsous cell
        Cell *prev_cell = getCell(c_idx);
        // set cursor
        c_idx.first = ncell_i;
        c_idx.second = ncell_j;

        // highlight cell under cursor
        if (prev_cell != NULL)
        {
            // set active for next cell
            B.c[c_idx.first][c_idx.second].state = 1;

            // if prev cell is not picked, deactivate it
            if (prev_cell != selected_pair.first && prev_cell != selected_pair.second)
            {
                prev_cell->state = 0;
            }
        }
    }

    // get cell based on position
    Cell *getCell(VECI pos)
    {
        for (int i = 0; i < B.config.m; i++)
        {
            for (int j = 0; j < B.config.n; j++)
            {
                if (pos.first == i && pos.second == j)
                    return &B.c[i][j];
            }
        }
        return NULL;
    }
    void checkForMatching(){

    };
    void pickCell()
    {
        Cell *c_under_cursor = getCell(c_idx);
        // cell under cursor is already selected
        if (c_under_cursor == selected_pair.first || c_under_cursor == selected_pair.second)
            return;
        // both cell selected
        if (selected_pair.first != NULL && selected_pair.second != NULL)
            return;

        if (selected_pair.first == NULL && selected_pair.second == NULL)
        {
            // first cell selected
            selected_pair.first = c_under_cursor;
        }
        else
        {
            // second cell selected
            selected_pair.second = c_under_cursor;
            checkForMatching();
        }
    }
};
int main()
{

    srand((time(nullptr)));

    // Default config
    GameConfig config = {4, 5, 4, {2, 4, 6, 8}};
    GameManager game = GameManager(config);

    while (true)
    {
        system("cls");
        game.displayBoard();

        char kb;
        cin >> kb;

        if (kb == 'w' || kb == 's' || kb == 'a' || kb == 'd')
        {
            VECI dir = GameManager::mapCharToPairDir(kb);
            game.moveCursor(dir);
        }
        if (kb == 'p')
        {
            game.pickCell();
        }
    }
}
