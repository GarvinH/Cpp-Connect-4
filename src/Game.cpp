#include "Game.h"

Game::Game()
{
    this->resetGame();
}

Game::~Game()
{
}

Move Game::play(int col)
{
    Move move;

    if (col >= 0 && col <= 6)
    {
        for (int i = 0; i < 6; i++)
        {
            if (this->board[col][i] == chip::Empty)
            {
                switch (this->turn)
                {
                case (turn::Yellow):
                    board[col][i] = chip::Yellow;
                    break;
                case (turn::Red):
                    board[col][i] = chip::Red;
                    break;
                }

                move.success = true;
                move.col = col;
                move.row = i;

                this->moves++;

                return move;
            }
        }
    }

    move.success = false;

    return move;
}

bool Game::checkWin(int col, int row)
{
    return this->checkVertical(col, row) || this->checkHorizontal(col, row) || this->checkDiagonals(col, row);
}

bool Game::checkVertical(int col, int row)
{
    if (row > 2) // vertical win requires that the row index is at least 3
    {
        for (int i = 1; i < 4; i++) //iteratively check downwards (vertical wins will only happen downwards of the newly placed chip)
        {
            if (this->board[col][row] != this->board[col][row - i])
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool Game::checkHorizontal(int col, int row)
{
    int colOffsetted = col; //temporary int tracker to see how far left we can go
    //move as far left possible while remaining same colour then check horizontal count
    while (colOffsetted > 0 && this->board[colOffsetted - 1][row] == this->board[col][row])
    {
        colOffsetted--;
    }

    for (int i = 0; i < 4; i++)
    {
        if (colOffsetted + i > 6) //going out of bounds rightwards
        {
            return false;
        }
        if (this->board[colOffsetted + i][row] != this->board[colOffsetted][row])
        {
            return false;
        }
    }

    return true;
}

bool Game::checkDiagonals(int col, int row)
{
    if (row > 2) // same condition as vertical win
    {

        int colOffsetted = col; //temp int to see how far left we can go
        int rowOffsetted = row; //temp int to see how far down/up we can go

        //check diagonal bottom left to top right -----------------------------------------
        //move as far bottom left as we can while remainig the same colour, then work up right
        bool diagonal1 = true; //represents if this diagonal is a win
        while (colOffsetted > 0 && rowOffsetted > 0 && this->board[colOffsetted - 1][rowOffsetted - 1] == this->board[col][row])
        {
            colOffsetted--;
            rowOffsetted--;
        }
        for (int i = 0; i < 4; i++)
        {
            if (colOffsetted + i > 6 || rowOffsetted + i > 5) //going out of bounds either upwards or rightwards
            {
                diagonal1 = false;
            }
            if (this->board[colOffsetted + i][rowOffsetted + i] != this->board[col][row])
            {
                diagonal1 = false;
            }
        }

        //check diagonal top left to bottom right -----------------------------------------
        colOffsetted = col; //reset
        rowOffsetted = row; //reset

        //move as far top left as possible while remaining the same color, then work bottom right
        bool diagonal2 = true;
        while (colOffsetted > 0 && rowOffsetted < 5 && this->board[colOffsetted - 1][rowOffsetted + 1] == this->board[col][row])
        {
            colOffsetted--;
            rowOffsetted++;
        }
        for (int i = 0; i < 4; i++)
        {
            if (colOffsetted + i > 6) //went to far right
            {
                diagonal2 = false;
                // don't need to check if going too far down because of vertical restriction
            }
            if (this->board[colOffsetted + i][rowOffsetted - i] != this->board[col][row])
            {
                diagonal2 = false;
            }
        }

        return diagonal1 || diagonal2; //if either of the two are true, ther is a win
    }

    return false;
}

void Game::resetGame()
{
    this->turn = turn::Yellow;
    for (int i = 0; i < 7; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            this->board[i][k] = chip::Empty;
        }
    }
    this->moves = 0;
}

bool Game::isTied()
{
    return this->moves == 42;
}