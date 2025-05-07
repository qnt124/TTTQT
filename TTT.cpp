#include <QMessageBox>
#include "TTT.h"
#include "ui_TTT.h"

TTT::TTT(QWidget *parent, int BoardSize, bool CPU, bool CPUstart, int miniMaxDepth)
    : QDialog(parent)
    , ui(new Ui::TTT),board(BoardSize),CPU(CPU),CPUstart(CPUstart),miniMaxDepth(miniMaxDepth)
{
    ui->setupUi(this);
    currentPlayer=BoardMark::X;
    creBoard(BoardSize);
    setConnection();
    reset();
}

TTT::~TTT()
{
    delete ui;
}

void TTT::creBoard(int BoardSize)
{
    cells.reserve(BoardSize * BoardSize);
    for(int row = 0; row < BoardSize; ++row)
    {
        for (int col = 0; col < BoardSize; ++col)
        {
            QPushButton* btn = new QPushButton();
            btn->setProperty("cell", true);
            ui->gridBoard->addWidget(btn, row, col, 1, 1);
            cells.emplace_back(btn, row, col);
        }
    }
}

void TTT::setConnection()
{
    for(Cell& cell:this->cells) connect(cell.cellbtn, &QPushButton::clicked, [&] { cellClicked(cell); });
    connect(ui->reset, SIGNAL(clicked()), SLOT(reset()));
    if(this->CPU) connect(this, SIGNAL(turnDone()), this, SLOT(CPUturn()));
    connect(ui->back, SIGNAL(clicked(bool)), SLOT(backtoTitle()));
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
    QString color;
    switch(this->currentPlayer)
    {
    case BoardMark::O:color="#0000FF";break;
    case BoardMark::X:color="#FF0000";break;
    default:return "#FFF";
    }
        return QString("font: 50px \"Arial\";"
                       "min-height: 100px;"
                       "max-height: 100px;"
                       "min-width: 100px;"
                       "max-width: 100px;"
                       "color: %1").arg(color);
}
void TTT::CPUturn()
{
    int i = board.miniMax(this->currentPlayer, this->miniMaxDepth);
    if(i != -1) updateGameState(cells.at(i));
}
void TTT::updateGameState(Cell& cell)
{
    cell.cellbtn->setStyleSheet(getCurrentPlayerColor());
    cell.cellbtn->setText(getCurrentPlayerMark());
    GameState GameState = board.evalBoard();
    if(GameState != GameState::InGame) declareGameState(GameState);
    changePlayer();
}
void TTT::reset()
{
    currentPlayer = BoardMark::X;
    board.reset();
    for(auto& cell:cells) cell.cellbtn->setText("");
    if(this->CPU&&this->CPUstart) CPUturn();
}

QString TTT::getGameFinalStateText(GameState GameState)
{
    switch (GameState)
    {
    case GameState::XWin: return "Người chơi X thắng";
    case GameState::OWin: return "Người chơi O thắng";
    case GameState::Tie: return "Hai người chơi hòa";
    default : return "";
    }
}
void TTT::cellClicked(Cell& cell)
{
    bool success = board.setPlayerInput(cell.row, cell.col, this->currentPlayer);
    if(success){
        updateGameState(cell);
        emit turnDone();
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
void TTT::backtoTitle()
{
    this->close();
}
