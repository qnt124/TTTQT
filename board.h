#ifndef BOARD_H
#define BOARD_H
enum class BoardMark
{
    Empty,X,O
};
enum class GameState
{
    InGame,XWin,OWin,Tie,
};

class Board
{
private:
    const static int BoardSize=3;
    BoardMark board[BoardSize][BoardSize];
    GameState state;
    short inputCount;
private:
    GameState getNewState(BoardMark currentPlayer);
public:
    Board();
    bool setPlayerInput(int row,int col,BoardMark currentPlayer);
    void printBoard();
    void reset();
    GameState updateState(BoardMark currentPlayer);
};

#endif
