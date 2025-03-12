#ifndef TTT_H
#define TTT_H

#include <QMainWindow>
#include <QPushButton>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TTT;
}
QT_END_NAMESPACE

class TTT : public QMainWindow
{
    Q_OBJECT

public:
    TTT(QWidget *parent = nullptr);
    ~TTT();

private:
    Ui::TTT *ui;
    BoardMark currentPlayer=BoardMark::X;
    Board board;
private:
    void setConnection();
    void changePlayer();
    QString getCurrentPlayerMark();
    QString getCurrentPlayerColor();
    QString getGameFinalStateText(GameState gameState);
    void declareGameState(GameState gameState);
public slots:
    void cellClicked(QPushButton *cell, int row, int col);
    void reset();
};
#endif // TTT_H
