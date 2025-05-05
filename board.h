#ifndef BOARD_H
#define BOARD_H
#include <QtGlobal>
#include <vector>
enum class BoardMark
{
    Empty,X,O
};
enum class GameState
{
    InGame,XWin,OWin,Tie,
};
using std::vector;
class Board
{
private:
    vector<vector<BoardMark>>board;
    int BoardSize;
    BoardMark CPU;
    BoardMark player;

private:
    int maxMove(int depth, int alpha, int beta);
    int minMove(int depth, int alpha, int beta);
    int score(GameState gamestate);

public:
    Board(int BoardSize);
    GameState evalBoard();
    bool setPlayerInput(int row, int col, BoardMark currentPlayer);
    int miniMax(BoardMark currentPlayer, int depth);
    GameState updateState();
    void reset();
};

#endif
