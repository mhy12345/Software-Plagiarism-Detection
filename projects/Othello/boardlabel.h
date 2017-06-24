#ifndef BOARDLABEL_H
#define BOARDLABEL_H

#include <QLabel>

class BoardLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BoardLabel(QWidget *parent = 0);

    int state;//use 0, 1 and -1 to express blank, black and white
    int x, y;//coordinate

signals:
    void BoardOn(int coordinate_x, int coordinate_y);
    void ToSkip();
public slots:

protected:
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // BOARDLABEL_H
