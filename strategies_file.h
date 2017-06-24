#ifndef FILE_STRATEGIES_H
#define FILE_STRATEGIES_H
#include "file.h"

/******************************************************************************
 *
 * File Plagirism Detector Algorihtm, Detect similarity of two file
 * Algorithm : Find fingerprint of two file and compare
 * Author : mhy12345
 *
 ******************************************************************************/

class PFile:public File
{
    private:
        string fp_structure;//Fingerprint extracted from code structure
        set<string> st_strings;//All string using in the code
        string fp_nocomment_structure;//Finger print extracted ignoring comment
        string deal_keyword(string &ss);
        string deal_variable(string &ss);
        string deal_precompiled(string &ss);
        string deal_comment(string &ss);
        string deal_string(string &ss);
        string deal_number(string &ss);
    public:
        PFile(){}
        PFile(const char* filename);
        void make_fingerprint();
        void print_fp();
        friend double fingerprint_compare(PFile &pf1,PFile &pf2);
};

#endif // FILE_STRATEGIES_H
