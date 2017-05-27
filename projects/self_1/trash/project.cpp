#include "project.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

PProject::PProject(string _path)
{
	cerr<<"PProject("<<_path<<")"<<endl;
	path = _path;
	FILE *output = popen(("ls "+_path).c_str(),"r");
	char data[100];
	while (fgets(data,sizeof(data),output))
	{
		cout<<data<<endl;
		int l = strlen(data);
		if (data[l-1] == '\n' || data[l-1]=='\t' || data[l-1]==' ')
			data[--l] = '\0';
		files.push_back(data);
		index[data] = files.size()-1;
	}
	fclose(output);
	for (auto f : files)
	{
		ifstream fin(path+"/"+f);
		std::istreambuf_iterator<char> beg(fin), end;
		content[f] = string(beg,end);
	}
}

void PProject::show_files()
{
	for (auto i : files)
		cout<<i<<endl;
}

void PProject::clear_comment()
{
	for (auto &f : files)
	{
		cerr<<"Execute clear_comment-inline to files<"<<f<<">"<<endl;
		regex pattern("//[^\\n]*\\n");
		smatch result;
		string tmpStr = content[f];
		string newStr = "";
		while (std::regex_search(tmpStr, result, pattern)){  
			cerr<<"COMMENT FOUND AND CLEAR:"<<result.str()<<endl;
			newStr += result.prefix();
			tmpStr = result.suffix().str();  
		}  
		newStr += tmpStr;
		cout<<newStr<<endl;
		content[f] = newStr;
	}
	for (auto &f : files)
	{
		cerr<<"Execute clear_comment-block to files<"<<f<<">"<<endl;
		regex pattern("/\\*[\\S\\s]*\\*/");
		smatch result;
		string tmpStr = content[f];
		string newStr = "";
		while (std::regex_search(tmpStr, result, pattern)){  
			cerr<<"COMMENT FOUND AND CLEAR:"<<result.str()<<endl;
			newStr += result.prefix();
			tmpStr = result.suffix().str();  
		}  
		newStr += tmpStr;
		content[f] = newStr;
	}
	cerr<<"Result:"<<endl;
	for (auto &f : files)
		cerr<<content[f]<<endl;
}

void PProject::build_graph()
{
	for (auto &f : files)
	{
		regex pattern("#include\\s*\"(\\S*)\"\n");
		smatch result;
		string tmpStr = content[f];
		string newStr = "";
		while (regex_search(tmpStr, result, pattern))
		{
			cerr<<"Edge from "<<f<<" to "<<result.format("$1")<<endl;
			tmpStr = result.suffix();
		}
	}
}

int compare(PProject* p1,PProject* p2)
{
	if (p1->files.size() != p2->files.size())
	{
		cerr<<"That's bad..."<<endl;
		return 0;
	}
	int l = p1->files.size();
	int *a = new int[l];
	for (int i=0;i<l;i++)
		a[i] = i;
	do{
		bool flag = true;
		for (auto w : p1->edges)
		{
			string s1 = p2->files[a[p1->index[w.first]]];
			string s2 = p2->files[a[p1->index[w.second]]];
			if (p2->edges.find(make_pair(s1,s2)) == p2->edges.end())
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			for (auto w : p1->files)
			{
				cerr<<w<<" "<<p2->files[a[p1->index[w]]]<<endl;
			}
			cerr<<"Two project is similar"<<endl;
		}
	}while (next_permutation(a,a+l));
	return 0;
}
