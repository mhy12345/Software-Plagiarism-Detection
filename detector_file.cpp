#include "detector_file.h"
FileDetector::FileDetector()
{
    pf1 = pf2 = NULL;
}
FileDetector::~FileDetector()
{
    delete pf1;
    delete pf2;
}
void FileDetector::init(const char* path1,const char* path2)
{
    if (pf1)delete pf1;
    if (pf2)delete pf2;
    pf1 = new PFile(path1);
    pf2 = new PFile(path2);
}

double FileDetector::compare()
{
    pf1->make_fingerprint();
    pf2->make_fingerprint();
    return fingerprint_compare(*pf1,*pf2);
}
