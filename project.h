#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::set;
using std::pair;

/******************************************************************************
 *
 * Project Base class, APIs to read all files from a projects
 * Algorithm : Find fingerprint of two file and compare
 * Author : mhy12345
 *
 ******************************************************************************/

class Project
{
    protected:
        string path;
        vector<string> files;
        vector<string> ftype;
    public:
        Project(string _path);
        string get_path(){return path;}
        const vector<string>& get_files(){return files;}
        const vector<string>& get_ftype(){return ftype;}
        void show_files();
};


#endif // PROJECT_H
