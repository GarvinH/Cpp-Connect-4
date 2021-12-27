#include "Move.h"

namespace chip
{
    enum Chip
    {
        Empty,
        Yellow,
        Red
    };
}

namespace turn
{
    enum Turn
    {
        Yellow,
        Red
    };
}

class Game
{
    bool checkHorizontal(int col, int row);
    bool checkVertical(int col, int row);
    bool checkDiagonals(int col, int row);
    int moves;

public:
    turn::Turn turn;
    chip::Chip board[7][6];
    Game();
    ~Game();
    Move play(int col); //returns bool representing if player won
    bool checkWin(int col, int row);
    void resetGame();
    bool isTied();
};