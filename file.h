#ifndef FILE_H
#define FILE_H

#include <string>
#include <set>
using std::string;
using std::set;
/******************************************************************************
 *
 * File Base Class, APIs to read file
 * Author : mhy12345
 *
 ******************************************************************************/

class File
{
    protected:
        string content;
    public:
        File(){}
        void read_file(const char* filename);
};



#endif // FILE_H
