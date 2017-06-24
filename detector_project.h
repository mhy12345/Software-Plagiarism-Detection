#ifndef PROJECT_DETECTOR_H
#define PROJECT_DETECTOR_H
#include "detector.h"
#include "strategies_project.h"

/******************************************************************************
 *
 * File Detector, Detect similarity of two project
 * Algorithm : Find fingerprint of two file and compare
 * Author : mhy12345 & czk
 *
 ******************************************************************************/


class ProjectDetector:public QObject, public Detector
{
    Q_OBJECT

    private:
        PProject *pp1,*pp2;
    protected:
        QStringListModel *model1, *model2;
        std::stringstream similarity_table;
        double now_compare_progress;
        double all_compare_progress;
    signals:
        void progress_update();
    public:
        ProjectDetector(QStringListModel* _model1, QStringListModel* _model2);
        ~ProjectDetector();
        void init(const char* path1,const char* path2);
        double compare();
};

#endif // PROJECT_DETECTOR_H
