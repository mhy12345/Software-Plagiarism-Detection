#include "project.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "file.h"

#ifndef Unix
#include <QDir>
#include <QDebug>

QFileInfoList get_file_list(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < folder_list.size(); ++ i)
    {
        QString child_path = folder_list.at(i).filePath();
        file_list.append(get_file_list(child_path));
    }
    return file_list;
}

#endif

using namespace std;

Project::Project(string _path)
{
	cerr<<"Project("<<_path<<")"<<endl;
	path = _path;
#ifdef Unix
    FILE *output = popen("ls ".c_str(),"r");
	char data[100];
	while (fgets(data,sizeof(data),output))
	{
		int l = strlen(data);
		if (data[l-1] == '\n' || data[l-1]=='\t' || data[l-1]==' ')
			data[--l] = '\0';
		string str = _path+"/"+data;
#else
    QFileInfoList file_list = get_file_list(QString::fromStdString(_path));
    for (int i = 0; i < file_list.size(); ++ i)
    {
        QString file_name = file_list.at(i).filePath();
        string str = file_name.toStdString();
#endif
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
#ifdef Unix
	pclose(output);
#endif
}

void Project::show_files()
{
	for (auto i : files)
		cout<<i<<endl;
}


