#ifndef PROJECT_STRATEGIES_H
#define PROJECT_STRATEGIES_H
#include "project.h"

/******************************************************************************
 *
 * File Plagirism Detector Algorihtm, Detect similarity of two file
 * Algorithm : Find fingerprint of all file between two project using FileStrategies,
 *              File the similarity of project using maximum cost flow algorithm.
 * Author : mhy12345
 *
 ******************************************************************************/

class PProject:public Project
{
    public:
        PProject(string _path):Project(_path){}
};

#endif // PROJECT_STRATEGIES_H
