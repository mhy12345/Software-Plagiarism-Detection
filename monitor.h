#ifndef PROJECTDETECTORMONITOR_H
#define PROJECTDETECTORMONITOR_H

#include "detector_project.h"
#include "detector_file.h"
#include <QProgressBar>
#include <QTextEdit>

/******************************************************************************
 *
 * A project detector monitoring rate of progress of comparing procedure
 * Author : czk
 *
 ******************************************************************************/

class ProjectDetectorMonitor:public ProjectDetector
{
    Q_OBJECT

public:
    ProjectDetectorMonitor(QStringListModel* _model1, QStringListModel* _model2, QProgressBar* _progress_bar, QTextEdit* _text_edit);
    ~ProjectDetectorMonitor();

    double compare();

public slots:
    void update_monitor();

protected:
    QTextEdit* similarity_table_displayer;
    QProgressBar* progress_bar;

private:
    void detect_end();

};

#endif // PROJECTDETECTORMONITOR_H
