#include "title.h"
#include "ui_title.h"

Title::Title(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Title),
    BoardSize(3),
    miniMaxDepth(3),
    CPU(true),
    CPUstart(false)
{
    ui->setupUi(this);
    setConnections();
}

void Title::setConnections()
{
    connect(ui->BoardSize, SIGNAL(valueChanged(int)), SLOT(updateBoardSize(int)));
    connect(ui->onePlayer, SIGNAL(toggled(bool)), SLOT(update1Player(bool)));
    connect(ui->twoPlayers, SIGNAL(toggled(bool)), SLOT(update2Players(bool)));
    connect(ui->CPUstart, SIGNAL(toggled(bool)), SLOT(updateCPUstart(bool)));
    connect(ui->startGame, SIGNAL(clicked()), SLOT(startGame()));
}

void Title::updateBoardSize(int size)
{
    ui->BoardSizeValue->setText(QString::number(size));
    this->BoardSize = size;
}

void Title::update1Player(bool checked)
{
    if(checked){
        ui->CPUstart->setEnabled(1);
        ui->miniMaxDepth->setEnabled(1);
        this->CPU = true;
    }
}

void Title::update2Players(bool checked)
{
    if(checked){
        ui->CPUstart->setEnabled(0);
        ui->miniMaxDepth->setEnabled(0);
        this->CPU = false;
    }
}

void Title::updateCPUstart(bool checked)
{
    if(checked){
        this->CPUstart = true;
    }else{
        this->CPUstart = false;
    }
}

void Title::updateMiniMaxDepth(int depth)
{
    ui->miniMaxDepthValue->setText(QString::number(depth));
    this->miniMaxDepth = depth;
}
void Title::startGame()
{
    this->hide();
    TTT game(nullptr,
                    this->BoardSize,
                    this->CPU,
                    this->CPUstart,
                    this->miniMaxDepth);
    game.setModal(true);
    game.exec();
    this->show();
}

Title::~Title()
{
    delete ui;
}
void Title::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    emit exited();
}
