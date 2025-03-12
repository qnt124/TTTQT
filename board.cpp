#include "board.h"
#include <QDebug>
#include <QString>

GameState Board::getNewState(BoardMark currentPlayer)
{
    GameState newState = GameState::InGame;
    if(currentPlayer == BoardMark::X) newState = GameState::XWin;
    else if (currentPlayer == BoardMark::O) newState = GameState::OWin;

    for(int row = 0; row < BoardSize; ++row)
    {
        if(board[row][0]==currentPlayer && board[row][1]==currentPlayer && board[row][2]==currentPlayer) return newState;
    }
    for(int col = 0; col < BoardSize; ++col)
    {
        if(board[0][col] == currentPlayer && board[1][col]==currentPlayer && board[2][col]==currentPlayer) return newState;
    }
    if(board[0][0]==currentPlayer && board[1][1]==currentPlayer && board[2][2]==currentPlayer) return newState;

    if(board[0][2]==currentPlayer && board[1][1]==currentPlayer && board[2][0]==currentPlayer) return newState;
    if(this->inputCount==this->BoardSize*this->BoardSize) return GameState::Tie;
    return GameState::InGame;
}
Board::Board():state(GameState::InGame),inputCount(0)
{
    for(int row=0;row<BoardSize;++row)
    {
        for(int col=0;col<BoardSize;++col)
        {
            board[row][col]=BoardMark::Empty;
        }
    }
}
/*void Board::printBoard()
{
    QString board;
    for(int row=0;row<BoardSize;++row)
    {
        for(int col=0;col<BoardSize;++col)
        {
            board+=QString::number(static_cast<int>(this->board[row][col]));
        }
        board+='\n';
    }
}*/
bool Board::setPlayerInput(int row, int col, BoardMark currentPlayer)
{
    if(state != GameState::InGame) return 0;
    if(row >= this->BoardSize && row < 0) return 0;
    if(col >= this->BoardSize && col < 0) return 0;
    if(board[row][col] != BoardMark::Empty) return 0;
    this->board[row][col] = currentPlayer;
    ++this->inputCount;
    return 1;
}
GameState Board::updateState(BoardMark currentPlayer)
{
    return this->state=getNewState(currentPlayer);
}

void Board::reset()
{
    state = GameState::InGame;
    inputCount = 0;
    for(int row=0;row<BoardSize;++row)
    {
        for(int col=0;col<BoardSize;++col)
        {
            board[row][col]=BoardMark::Empty;
        }
    }
}

