#ifndef TITLE_H
#define TITLE_H
#include <QMainWindow>
#include "TTT.h"
namespace Ui{
class Title;
}
class Title:public QMainWindow
{
    Q_OBJECT
public:
    explicit Title(QWidget *parent = nullptr);
    ~Title();

private:
    Ui::Title *ui;
    void setConnections();
    int BoardSize;
    int miniMaxDepth;
    bool CPU;
    bool CPUstart;

public slots:
    void updateBoardSize(int BoardSize);
    void update1Player(bool checked);
    void update2Players(bool checked);
    void updateCPUstart(bool checked);
    void updateMiniMaxDepth(int depth);
    void startGame();

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void exited();
};


#endif // TITLE_H
