#ifndef FILE_H
#define FILE_H

#include <string>
#include <set>

using std::string;
using std::set;

class File
{
    protected:
        string content;
    public:
        File(){}
        void read_file(const char* filename);
};

class PFile:public File
{
    private:
        string fp_structure;
        set<string> st_strings;
        string fp_nocomment_structure;
        string hash(string str,int len=3);
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

#endif // FILE_H
