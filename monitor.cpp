#include "monitor.h"

ProjectDetectorMonitor::ProjectDetectorMonitor(QStringListModel *_model1, QStringListModel *_model2, QProgressBar *_progress_bar, QTextEdit *_text_edit):
    ProjectDetector(_model1, _model2)
{
    similarity_table_displayer = _text_edit;
    progress_bar = _progress_bar;
}

ProjectDetectorMonitor::~ProjectDetectorMonitor()
{
}

double ProjectDetectorMonitor::compare()
{
    connect(this, SIGNAL(progress_update()), this, SLOT(update_monitor()));
    double temp = ProjectDetector::compare();
    detect_end();
    return temp;
}

void ProjectDetectorMonitor::update_monitor()
{
    int progress = static_cast<int>(now_compare_progress / all_compare_progress * 100);
    progress_bar ->setValue(progress);
}

void ProjectDetectorMonitor::detect_end()
{
    progress_bar ->setValue(100);
    similarity_table_displayer ->setText(QString::fromStdString(similarity_table.str()));
}
