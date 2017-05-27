#include "file.h"
#include "project.h"
#include "detectors.h"
#include<iostream>
using namespace std;


int main()
{
	const char *filename1 = "code/d.cpp";
	const char *filename2 = "code/c.cpp";
	const char *pathname1 = "projects/week13";
	const char *pathname2 = "projects/week13_copy";
	ProjectDetector PD;
	PD.init(pathname1,pathname2);
	double res = PD.compare();
	cout<<"RESULT:"<<res<<endl;
}
