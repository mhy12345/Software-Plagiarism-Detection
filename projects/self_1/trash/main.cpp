#include "project.h"
#include<iostream>
using namespace std;

int main(int argc)
{
	cout<<argc<<endl;
	PProject P1("./data/project1");
	P1.show_files();
	//P1.clear_comment();
	P1.build_graph();
	PProject P2("./data/project1");
	P2.show_files();
	//P2.clear_comment();
	P2.build_graph();
	compare(&P1,&P2);
}
