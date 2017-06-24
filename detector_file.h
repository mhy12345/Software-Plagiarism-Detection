#ifndef FILE_DETECTOR_H
#define FILE_DETECTOR_H
#include "file.h"
#include "detector.h"
#include "strategies_file.h"

/******************************************************************************
 *
 * File Detector, Detect similarity of two file
 * Algorithm : Find fingerprint of two file and compare
 * Author : mhy12345
 *
 ******************************************************************************/

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

#endif // FILE_DETECTOR_H
