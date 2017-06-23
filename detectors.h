#ifndef DETECTORS_H
#define DETECTORS_H

#include "file.h"
#include "project.h"

#include <sstream>
#include <QStringListModel>

class Detector
{
    public:
        Detector();
        virtual void init(const char* path1,const char* path2) = 0;
        virtual double compare() = 0;
        virtual ~Detector() = 0;
};

class FileDetector:public Detector
{
    private:
        PFile *pf1,*pf2;
    public:
        FileDetector();
        ~FileDetector();
        void init(const char* path1,const char* path2);
        double compare();
};

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

#endif // DETECTORS_H
