#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class BoardLabel;
class QLabel;
class QTimer;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    BoardLabel * chess[8][8];//to express the whole board
    QLabel * PlayerChessCount, * CpuChessCount;
    QLabel * Title;
    QTimer * timer;
    int player;
    int now_flag;
    int CountChess(int part);
    int temp_Board[8][8];

    void MoveTempToBoard();
    void CopyTempFromBoard();

    bool JudgeCoordinateLegal(int x, int y);
    bool JudgeIfGameIsEnd();

    void SetCountLabel(QLabel ** label, int x,int y);
    void SetTitleLabel(QLabel * label, int x,int y);

    void InitLabels();
    void PaintLabels();
    void PaintAll();

    int EatChess(int x, int y, int part);
    void PutChess(int x, int y, int part);
    int PutInterest(int x, int y, int part);
    int CalInterest();
private slots:
    void DealWithPress(int x, int y);
    void SkipMain();
    void EndPauseMain();

public:
    void StartGame();
    void PlayerMain();
    void CpuMain();
    void PauseMain();
    void EndGame();
};

#endif // DIALOG_H
