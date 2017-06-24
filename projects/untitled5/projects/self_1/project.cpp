#include "project.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "file.h"
using namespace std;

PProject::PProject(string _path)
{
	cerr<<"PProject("<<_path<<")"<<endl;
	path = _path;
	FILE *output = popen(("ls "+_path).c_str(),"r");
	char data[100];
	while (fgets(data,sizeof(data),output))
	{
		int l = strlen(data);
		if (data[l-1] == '\n' || data[l-1]=='\t' || data[l-1]==' ')
			data[--l] = '\0';
		string str = _path+"/"+data;
		if (str.substr(str.length()-4,4) == ".cpp" || str.substr(str.length()-3,3) == ".cc")
		{
			files.push_back(str);
			ftype.push_back("CPP Source file");
		}
		if (str.substr(str.length()-2,2) == ".h" || str.substr(str.length()-4,4) == ".hpp")
		{
			files.push_back(str);
			ftype.push_back("CPP Header");
		}
	}
	pclose(output);
	/*
	   for (auto f : files)
	   {
	   ifstream fin(f);
	   std::istreambuf_iterator<char> beg(fin), end;
	   content[f] = string(beg,end);
	   }*/
}

void PProject::show_files()
{
	for (auto i : files)
		cout<<i<<endl;
}


