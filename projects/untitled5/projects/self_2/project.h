#ifndef __PROJECT_H
#define __PROJECT_H
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

class PProject
{
	private:
		string path;
		vector<string> files;
		vector<string> ftype;
		//map<string,string> content;
	public:
		PProject(string _path);
		string get_path(){return path;}
		const vector<string>& get_files(){return files;}
		const vector<string>& get_ftype(){return ftype;}
		void show_files();
};

#endif
