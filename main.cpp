#include "file.h"
#include "project.h"
#include "detectors.h"
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;


void ProjectMode()
{
	char path1[1000],path2[1000];
	cout<<"Please Input Path 1['projects/A']";
	cin.getline(path1,sizeof(path1));
	if (path1[0] == '\n' || path1[0]=='\0')
		strcpy(path1,"projects/A");
	cout<<"Please Input Path 2['projects/A_copy']";
	cin.getline(path2,sizeof(path2));
	if (path2[0] == '\n' || path2[0]=='\0')
		strcpy(path2,"projects/A_copy");

	ProjectDetector PD;
	PD.init(path1,path2);
	double res = PD.compare();
	cout<<"RESULT:"<<res<<endl;
}

void FileMode()
{
	char path1[1000],path2[1000];
	cout<<"Please Input Path 1['code/A+B/A.cpp']";
	cin.getline(path1,sizeof(path1));
	if (path1[0] == '\n' || path1[0] =='\0')
		strcpy(path1,"code/A+B/A.cpp");
	cout<<"Please Input Path 2['code/A+B/B.cpp']";
	cin.getline(path2,sizeof(path2));
	if (path2[0] == '\n' || path2[0]=='\0')
		strcpy(path2,"code/A+B/B.cpp");

	FileDetector FD;
	FD.init(path1,path2);
	double res = FD.compare();
	cout<<"RESULT:"<<res<<endl;
}
void InputMode()
{
	FILE * fin = fopen("input.txt","r");
	char mode[20],path1[1000],path2[1000];
	fscanf(fin,"%s\n%s\n%s\n",mode,path1,path2);
	fclose(fin);
	if (string(mode) == "Project")
	{
		ProjectDetector PD;
		PD.init(path1,path2);
		double res = PD.compare();
		cout<<"Similarity between to project is "<<res<<endl;
	}else if (string(mode) == "File")
	{
		FileDetector FD;
		FD.init(path1,path2);
		double res = FD.compare();
		cout<<"Similarity between to project is "<<res<<endl;
	}
}

int main()
{
	char buf[100];
	cout<<"Please Input Mode(File/Project/Input) [Input]";
	cin.getline(buf,sizeof(buf));
	if (string(buf).substr(0,4) == "File")
	{
		FileMode();
	}else if (string(buf).substr(0,7) == "Project")
	{
		ProjectMode();
	}else
	{
		InputMode();
	}
}
