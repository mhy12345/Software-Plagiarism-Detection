#include "plagiarismdetectorwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlagiarismDetectorWidget w;
    w.show();

    return a.exec();
}
