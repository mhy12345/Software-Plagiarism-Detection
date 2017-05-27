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
		map<string,int> index;
		map<string,string> content;
		set<pair<string,string> > edges;
	public:
		PProject(string _path);
		string get_path(){return path;}
		const vector<string>& get_files(){return files;}
		void show_files();
		void clear_comment();
		void build_graph();
		friend int compare(PProject* p1,PProject* p2);
};

#endif
