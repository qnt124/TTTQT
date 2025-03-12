#include <QMessageBox>
#include "TTT.h"
#include "ui_TTT.h"

TTT::TTT(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TTT)
{
    ui->setupUi(this);
    setConnection();
}

TTT::~TTT()
{
    delete ui;
}
void TTT::setConnection()
{
    connect(ui->cell_1,&QPushButton::clicked,[=]{cellClicked(ui->cell_1,0,0);});
    connect(ui->cell_2,&QPushButton::clicked,[=]{cellClicked(ui->cell_2,0,1);});
    connect(ui->cell_3,&QPushButton::clicked,[=]{cellClicked(ui->cell_3,0,2);});
    connect(ui->cell_4,&QPushButton::clicked,[=]{cellClicked(ui->cell_4,1,0);});
    connect(ui->cell_5,&QPushButton::clicked,[=]{cellClicked(ui->cell_5,1,1);});
    connect(ui->cell_6,&QPushButton::clicked,[=]{cellClicked(ui->cell_6,1,2);});
    connect(ui->cell_7,&QPushButton::clicked,[=]{cellClicked(ui->cell_7,2,0);});
    connect(ui->cell_8,&QPushButton::clicked,[=]{cellClicked(ui->cell_8,2,1);});
    connect(ui->cell_9,&QPushButton::clicked,[=]{cellClicked(ui->cell_9,2,2);});
    connect(ui->retryButton,SIGNAL(clicked()),SLOT(reset()));
}
void TTT::changePlayer()
{
    if(this->currentPlayer==BoardMark::X) this->currentPlayer=BoardMark::O;
    else if(this->currentPlayer==BoardMark::O) this->currentPlayer=BoardMark::X;
}
QString TTT::getCurrentPlayerMark()
{
    switch(this->currentPlayer)
    {
        case BoardMark::O:
            return "O";
        case BoardMark::X:
            return "X";
        default:
            return "";
    }
}
QString TTT::getCurrentPlayerColor()
{
    switch(this->currentPlayer)
    {
        case BoardMark::O:
            return "#FF5722";
        case BoardMark::X:
            return "#455A64";
        default:
            return "";
    }
}
void TTT::cellClicked(QPushButton* cell, int row, int col)
{
    bool success=board.setPlayerInput(row, col, this->currentPlayer);
    if(success)
    {
        cell->setStyleSheet(QString("color: %1;").arg(getCurrentPlayerColor()));
        cell->setText(getCurrentPlayerMark());
        GameState boardState = board.updateState(this->currentPlayer);
        if(boardState != GameState::InGame)
        {
            declareGameState(boardState);
        }
        changePlayer();
    }
}
void TTT::reset()
{
    board.reset();
    ui->cell_1->setText("");
    ui->cell_2->setText("");
    ui->cell_3->setText("");
    ui->cell_4->setText("");
    ui->cell_5->setText("");
    ui->cell_6->setText("");
    ui->cell_7->setText("");
    ui->cell_8->setText("");
    ui->cell_9->setText("");
}
QString TTT::getGameFinalStateText(GameState GameState)
{
    switch (GameState) {
    case GameState::XWin: return "Người chơi X thắng";
    case GameState::OWin: return "Người chơi O thắng";
    case GameState::Tie: return "Hai người chơi hòa";
    default : return "";
    }
}
void TTT::declareGameState(GameState GameState)
{
    QMessageBox resultBox;
    resultBox.setWindowTitle("Kết quả");
    resultBox.setMinimumWidth(500);
    resultBox.setText("Kết thúc trò chơi, "+getGameFinalStateText(GameState));
    resultBox.exec();
}
