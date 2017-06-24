#include "file.h"
#include <iostream>
#include <fstream>
using namespace std;
void File::read_file(const char* filename)
{
    ifstream fin(filename);
    char buf[1000];
    while (fin.getline(buf,sizeof(buf)))
        content+=buf,content+="\n";
}
