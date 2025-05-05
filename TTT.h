#ifndef TTT_H
#define TTT_H

#include <QDialog>
#include <QPushButton>
#include <vector>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TTT;
}
QT_END_NAMESPACE

class TTT : public QDialog
{
    Q_OBJECT

public:
    TTT(QWidget *parent = nullptr, int BoardSize=3, bool CPU=1, bool CPUstart=0, int miniMaxDepth=3);
    ~TTT();
private:
    struct Cell
    {
        QPushButton *cellbtn=nullptr;
        int row=-1,col=-1;
        Cell(QPushButton *cellbtn, int row, int col):
            cellbtn(cellbtn),
            row(row),
            col(col)
        {}
    };
private:
    Ui::TTT *ui;
    BoardMark currentPlayer=BoardMark::X;
    Board board;
    std::vector<Cell> cells;
    bool CPU;
    bool CPUstart;
    int miniMaxDepth;
private:
    void setConnection();
    void changePlayer();
    QString getCurrentPlayerMark();
    QString getCurrentPlayerColor();
    QString getGameFinalStateText(GameState gameState);
    void declareGameState(GameState gameState);
    void updateGameState(Cell& cell);
    void creBoard(int BoardSize);
signals:
    void turnDone();
public slots:
    void cellClicked(Cell &cell);
    void CPUturn();
    void reset();
    void backtoTitle();
};
#endif // TTT_H
