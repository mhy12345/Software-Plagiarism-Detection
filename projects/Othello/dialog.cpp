#include "dialog.h"
#include "ui_dialog.h"
#include "boardlabel.h"
#include <QInputDialog>
#include <QMessageBox>
#include <Qtimer>
#include <QTime>
//#include <QDebug>

QString url_images[3] =
{
    QString(":/Images/Images/white.png"),
    QString(":/Images/Images/blank.png"),
    QString(":/Images/Images/black.png")
};

int Directions[8][2] =
{
    {1,0},
    {0,1},
    {-1,0},
    {0,-1},
    {1,1},
    {1,-1},
    {-1,-1},
    {-1,1}
};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Othello"));
    SetCountLabel(&PlayerChessCount, 10, 50);
    SetCountLabel(&CpuChessCount, 250, 50);
    SetTitleLabel(Title, 10, 10);
    InitLabels();
}

void Dialog::SetCountLabel(QLabel **label, int x, int y)
{
    *label = new QLabel(this);
    (*label) ->move(x, y);
    (*label) ->setAlignment(Qt::AlignCenter);
    (*label) ->setStyleSheet("font-size:16px;");
    (*label) ->resize(240, 40);
}

void Dialog::SetTitleLabel(QLabel *label, int x, int y)
{
    label = new QLabel(this);
    label ->move(x, y);
    label ->setAlignment(Qt::AlignCenter);
    label ->setStyleSheet("font-size:30px;");
    label ->resize(480, 40);
    label ->setText(tr("Othello Game Made By Clazy Chen"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::InitLabels()
{
    int i, j;
    for (i = 0; i < 8; ++ i)
    {
        for (j = 0; j < 8; ++ j)
        {
            chess[i][j] = new BoardLabel(this);
            chess[i][j] ->resize(60, 60);
            chess[i][j] ->move(10+j*60, 100+i*60);
            chess[i][j] ->state = 0;
            chess[i][j] ->x = i;
            chess[i][j] ->y = j;
            connect(chess[i][j], SIGNAL(BoardOn(int,int)),
                    this, SLOT(DealWithPress(int,int)));
            connect(chess[i][j], SIGNAL(ToSkip()),
                    this, SLOT(SkipMain()));
        }
    }
    chess[3][3] ->state = chess[4][4] ->state = 1;
    chess[3][4] ->state = chess[4][3] ->state = -1;
    PaintLabels();
}

void Dialog::PaintLabels()
{
    int i, j;
    for (i = 0; i < 8; ++ i)
    {
        for (j = 0; j < 8; ++ j)
        {
            chess[i][j] ->setPixmap(QPixmap(url_images[chess[i][j] ->state + 1]));
        }
    }
}

void Dialog::PaintAll()
{
    PaintLabels();
    PlayerChessCount ->setText(QString(tr("Player Chess Count: "))+QString::number(CountChess(player)));
    CpuChessCount ->setText(QString(tr("Cpu Chess Count: "))+QString::number(CountChess(-player)));
}

void Dialog::StartGame()
{
    bool ok;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QStringList items_for_choose;
    items_for_choose << tr("Black") << tr("White");
    QString item = QInputDialog::getItem(this, tr("Please choose Black or White to use"),
                                tr("Tips:White acts first."), items_for_choose, 0, true, &ok);
    if (!ok)
    {
        StartGame();
        return;
    }
    else
    {
        if (item == QString(tr("Black")))
            player = 1;
        else
            player = -1;
    }
    if (player == 1)
        CpuMain();
    else
        PlayerMain();
}

int Dialog::CountChess(int part)
{
    int c = 0, i, j;
    for (i = 0; i < 8; ++ i)
    {
        for (j = 0; j < 8; ++ j)
        {
            if (chess[i][j] ->state == part)
                ++ c;
        }
    }
    return c;
}

void Dialog::EndGame()
{
    PaintAll();
    if (CountChess(player) > CountChess(-player))
        QMessageBox::about(this, tr("GameOver"),
                           tr("GameOver\nAnd You WIN!"));
    else if (CountChess(player) < CountChess(-player))
        QMessageBox::about(this, tr("GameOver"),
                           tr("GameOver\nAnd You LOSE!"));
    else
        QMessageBox::about(this, tr("GameOver"),
                           tr("GameOver\nAnd DRAW!"));
    close();
}

void Dialog::PlayerMain()
{
    now_flag = player;
    PaintAll();
}

void Dialog::PauseMain()
{
    PaintAll();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(EndPauseMain()));
    timer ->start(1000);
}

void Dialog::EndPauseMain()
{
    delete timer;
    CpuMain();
}

void Dialog::CpuMain()
{
    now_flag = - player;
    CopyTempFromBoard();
    //first, try to get the angle
    int temp_x = -1, temp_y = -1, temp_sum, i, j;
    temp_sum = - 1000;
    for (i = 0; i < 8; ++ i)
    {
        for (j = 0; j < 8; ++ j)
        {
           // if (PutInterest(i, j, -player) != - 1001)
           // qDebug() << PutInterest(i, j, -player) << i << j;
            if (PutInterest(i, j, -player) > temp_sum)
            {
                temp_x = i;
                temp_y = j;
                temp_sum = PutInterest(i, j, -player);
            }
            else if (PutInterest(i, j, -player) == temp_sum)
            {
                //introduce random algorithm
                if ((qrand() & 63) > ( i << 3 ) + j)
                {
                    temp_x = i;
                    temp_y = j;
                }
            }
        }
    }
    //qDebug() << "--------------";
    if (temp_x >= 0)
    {
        CopyTempFromBoard();
        PutChess(temp_x, temp_y, -player);
        MoveTempToBoard();
    }
    else
        QMessageBox::about(this, tr(""), tr("Cpu Skip its main!"));
    if (!JudgeIfGameIsEnd())
        PlayerMain();
    else
        EndGame();
}

void Dialog::DealWithPress(int x, int y)
{
    if (now_flag != player)
        return;
    CopyTempFromBoard();
    if (EatChess(x, y, player) == 0)
    {
        QMessageBox::warning(this, tr("Warning!"),
                             tr("You can\'t put a chess on this position!"), QMessageBox::Ok);
        return;
    }
    PutChess(x, y, player);
    MoveTempToBoard();
    if (!JudgeIfGameIsEnd())
        PauseMain();
    else
        EndGame();
}

void Dialog::SkipMain()
{
    if (now_flag != player)
        return;
    CpuMain();
}

bool Dialog::JudgeCoordinateLegal(int x, int y)
{
    return ((0 <= x && x <= 7) && (0 <= y && y <= 7));
}

bool Dialog::JudgeIfGameIsEnd()
{
    return !(CountChess(0) > 0 && CountChess(1) > 0 && CountChess(-1) > 0);
}

void Dialog::MoveTempToBoard()
{
    int i, j;
    for (i = 0; i < 8; ++ i)
        for (j = 0; j < 8; ++ j)
            chess[i][j] ->state = temp_Board[i][j];
}

void Dialog::CopyTempFromBoard()
{
    int i, j;
    for (i = 0; i < 8; ++ i)
        for (j = 0; j < 8; ++ j)
            temp_Board[i][j] = chess[i][j] ->state;
}

int Dialog::EatChess(int x, int y, int part)
{
    //this is a virtual calculate of how many chess can a put eat
    if (temp_Board[x][y] != 0)
        return 0;
    int temp_x, temp_y, sum, temp_sum, i;
    sum = 0;
    for (i = 0; i < 8; ++ i)
    {
        temp_sum = 0;
        temp_x = x + Directions[i][0];
        temp_y = y + Directions[i][1];
        for (;JudgeCoordinateLegal(temp_x, temp_y);
             temp_x += Directions[i][0], temp_y += Directions[i][1])
        {
            if (temp_Board[temp_x][temp_y] == part && temp_sum > 0)
            {
                sum += temp_sum;
                break;
            }
            else if (temp_Board[temp_x][temp_y] == - part)
                ++ temp_sum;
            else break;
        }
    }
    return sum;
}

void Dialog::PutChess(int x, int y, int part)
{
    int temp_x, temp_y, temp_sum, i;
    for (i = 0; i < 8; ++ i)
    {
        temp_sum = 0;
        temp_x = x + Directions[i][0];
        temp_y = y + Directions[i][1];
        for (;JudgeCoordinateLegal(temp_x, temp_y);
             temp_x += Directions[i][0], temp_y += Directions[i][1])
        {
            if (temp_Board[temp_x][temp_y] == part && temp_sum > 0)
            {
                do
                {
                    temp_x -= Directions[i][0];
                    temp_y -= Directions[i][1];
                    temp_Board[temp_x][temp_y] = part;
                }
                while (temp_x != x || temp_y != y);
                break;
            }
            else if (temp_Board[temp_x][temp_y] == - part)
                ++ temp_sum;
            else break;
        }
    }
    temp_Board[x][y] = part;
}

int Dialog::PutInterest(int x, int y, int part)
{
    if (EatChess(x, y, part) == 0)
        return -1001;
    int i, j, k, l, temp_interest = 1000;
    for (i = 0; i < 8; ++ i)
        for (j = 0; j < 8; ++ j)
        {
            CopyTempFromBoard();
            PutChess(x, y, part);
            for (k = 0; k < 8; ++ k)
                for (l = 0; l < 8; ++ l)
                {
                    if (EatChess(k, l, - part))
                    {
                        PutChess(k, l, - part);
                        if (temp_interest > CalInterest())
                            temp_interest = CalInterest();
                        CopyTempFromBoard();
                        PutChess(x, y, part);
                    }
                }
        }
    CopyTempFromBoard();
    return temp_interest;
}

int Dialog::CalInterest()
{
    int i, j, sum[3] = {0, 0, 0};
    for (i = 0; i < 8; ++ i)
        for (j = 0; j < 8; ++ j)
            if ((i == 0 || i == 7) && (j == 0 || j == 7))
                sum[temp_Board[i][j] + 1] += 10;
            else
                ++ sum[temp_Board[i][j] + 1];
    return (sum[ - player + 1] - sum[player + 1]);
}
