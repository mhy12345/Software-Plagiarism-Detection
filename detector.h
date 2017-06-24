#ifndef DETECTORS_H
#define DETECTORS_H

#include "file.h"
#include "project.h"

#include <sstream>
#include <QStringListModel>

/******************************************************************************
 *
 * Base class of Detector, Detect similarity of two file/project
 * Author : mhy12345
 *
 ******************************************************************************/

class Detector
{
    public:
        Detector();
        virtual void init(const char* path1,const char* path2) = 0;
        virtual double compare() = 0;//Return similarity between two object
        virtual ~Detector() = 0;
};




#endif // DETECTORS_H
