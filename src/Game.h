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

public:
    turn::Turn turn;
    chip::Chip board[7][6];
    Game();
    ~Game();
    void play();
};