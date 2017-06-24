#include "boardlabel.h"
#include <QMouseEvent>

BoardLabel::BoardLabel(QWidget *parent) :
    QLabel(parent)
{
}

void BoardLabel::mouseReleaseEvent(QMouseEvent * event)
{
    if (event ->button() == Qt::LeftButton)
        emit BoardOn(x, y);
    else if (event ->button() == Qt::RightButton)
        emit ToSkip();
    QLabel::mouseReleaseEvent(event);
}
