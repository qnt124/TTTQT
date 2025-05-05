#include "board.h"
#include <QDebug>
#include <QString>
#include <QPair>

Board::Board(int BoardSize):
    board(BoardSize, vector<BoardMark>(BoardSize, BoardMark::Empty)),
    BoardSize(BoardSize)
{
    CPU = BoardMark::Empty;
    player = BoardMark::Empty;
}

bool Board::setPlayerInput(int row, int col, BoardMark currentPlayer)
{
    if(evalBoard() != GameState::InGame) return 0;
    if(row >= this->BoardSize && row < 0) return 0;
    if(col >= this->BoardSize && col < 0) return 0;
    if(board[row][col] != BoardMark::Empty) return 0;
    this->board[row][col] = currentPlayer;
    return 1;
}
GameState Board::evalBoard()
{
    //Hàng
    for(int row=0;row<this->BoardSize;++row)
    {
        bool equalRow=1;
        BoardMark r=board[row][0];
        for(int col=1;col<this->BoardSize;++col)
        {
            if(board[row][col]!=r) equalRow=0;
        }
        if(equalRow)
        {
            if(r==BoardMark::X) return GameState::XWin;
            else if(r==BoardMark::O) return GameState::OWin;
        }
    }
    //Cột
    for(int col=0;col<this->BoardSize;++col)
    {
        bool equalCol=1;
        BoardMark r=board[0][col];
        for(int row=1;row<this->BoardSize;++row)
        {
            if(board[row][col]!=r) equalCol=0;
        }
        if(equalCol)
        {
            if(r==BoardMark::X) return GameState::XWin;
            else if(r==BoardMark::O) return GameState::OWin;
        }
    }
    //Chéo
    bool equalDiag=1;
    BoardMark r=board[0][0];
    for(int i=1;i<this->BoardSize;++i)
    {
        if(board[i][i]!=r) equalDiag=0;
    }
    if(equalDiag)
    {
        if(r==BoardMark::X) return GameState::XWin;
        else if(r==BoardMark::O) return GameState::OWin;
    }
    equalDiag=1;
    r=board[0][this->BoardSize-1];
    for(int i=1;i<this->BoardSize;++i)
    {
        int row=i;
        int col=this->BoardSize-i-1;
        if(board[row][col]!=r) equalDiag=0;
    }
    if(equalDiag)
    {
        if(r==BoardMark::X) return GameState::XWin;
        else if(r==BoardMark::O) return GameState::OWin;
    }

    for(int row=0;row<this->BoardSize;++row)
        for(int col=0;col<this->BoardSize;++col)
            if(board[row][col]==BoardMark::Empty) return GameState::InGame;

    return GameState::Tie;
}

void Board::reset()
{
    for(int row=0;row<BoardSize;++row)
    {
        for(int col=0;col<BoardSize;++col)
        {
            board[row][col]=BoardMark::Empty;
        }
    }
    CPU=BoardMark::Empty;
    player=BoardMark::Empty;
}
int Board::score(GameState state)
{
    if (CPU == BoardMark::O && state == GameState::OWin) return 1;
    else if (CPU == BoardMark::X && state == GameState::XWin) return 1;
    else if (CPU == BoardMark::O && state == GameState::XWin) return -1;
    else if (CPU == BoardMark::X && state == GameState::OWin) return -1;
    else return 0;
}
int Board::miniMax(BoardMark currentPlayer, int depth)
{
    if(evalBoard() != GameState::InGame) return -1;

    if(CPU == BoardMark::Empty)
    {
        CPU = currentPlayer;
        player = (this->CPU == BoardMark::O ? BoardMark::X : BoardMark::O);
    }
    int bestScore = INT_MIN;
    QPair<int, int> bestEntry;
    for(int row = 0; row < this->BoardSize; ++row)
    {
        for (int col = 0; col < this->BoardSize; ++col)
        {
            if(board[row][col] == BoardMark::Empty)
            {
                board[row][col] = CPU;
                int moveScore = minMove(depth-1,INT_MIN,INT_MAX);
                if(moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestEntry.first = row;;
                    bestEntry.second = col;
                }
                board[row][col] = BoardMark::Empty;
            }
        }
    }
    board[bestEntry.first][bestEntry.second] = currentPlayer;
    return bestEntry.first * this->BoardSize + bestEntry.second;
}

int Board::maxMove(int depth, int alpha, int beta)
{
    GameState state = evalBoard();
    if(depth==0||state != GameState::InGame) return score(state);
    int bestScore = INT_MIN;
    for(int row = 0; row < this->BoardSize; ++row)
    {
        for (int col = 0; col < this->BoardSize; ++col)
        {
            if(board[row][col] == BoardMark::Empty)
            {
                board[row][col] = this->CPU;
                int score = minMove(depth-1,alpha,beta);
                board[row][col] = BoardMark::Empty;
                bestScore=std::max(alpha,score);
                alpha=std::max(alpha,score);
                if(beta<=alpha) break;
            }
        }
    }
    return bestScore;
}

int Board::minMove(int depth, int alpha, int beta)
{
    GameState state = evalBoard();
    if(depth==0||state != GameState::InGame) return score(state);
    int bestScore = INT_MAX;
    for(int row = 0; row < this->BoardSize; ++row)
    {
        for (int col = 0; col < this->BoardSize; ++col)
        {
            if(board[row][col] == BoardMark::Empty)
            {
                board[row][col] = player;
                int score = maxMove(depth-1,alpha,beta);
                board[row][col] = BoardMark::Empty;
                bestScore=std::min(bestScore,score);
                beta=std::min(beta,score);
                if(beta<=alpha) break;
            }
        }
    }
    return bestScore;
}
