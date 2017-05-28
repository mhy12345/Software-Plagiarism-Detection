#include<iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include "detectors.h"
#include "cost_flow.h"
using namespace std;

Detector::Detector()
{
}
Detector::~Detector()
{
}

FileDetector::FileDetector()
{
	pf1 = pf2 = NULL;
}
FileDetector::~FileDetector()
{
	delete pf1;
	delete pf2;
}
void FileDetector::init(const char* path1,const char* path2)
{
	if (pf1)delete pf1;
	if (pf2)delete pf2;
	pf1 = new PFile(path1);
	pf2 = new PFile(path2);
}

double FileDetector::compare()
{
	pf1->make_fingerprint();
	pf2->make_fingerprint();
	return fingerprint_compare(*pf1,*pf2);
}

ProjectDetector::ProjectDetector()
{
	pp1 = pp2 = NULL;
}
ProjectDetector::~ProjectDetector()
{
	if (pp1)delete pp1;
	if (pp2)delete pp2;
}

void ProjectDetector::init(const char* path1,const char* path2)
{
	if (pp1)delete(pp1);
	if (pp2)delete(pp2);
	pp1 = new PProject(path1);
	pp2 = new PProject(path2);
}

double ProjectDetector::compare()
{
	cout<<"====================="<<endl;
	for (auto w : pp1->get_files())
		cout<<w<<endl;
	cout<<"====================="<<endl;
	for (auto w : pp2->get_files())
		cout<<w<<endl;
	int n = pp1->get_files().size();
	int m = pp2->get_files().size();
	double **mat = new double*[n];
	for (int i=0;i<n;i++)
		mat[i] = new double[m];
	PFile* pflst1 = new PFile[n];
	PFile* pflst2 = new PFile[m];
	for (int i=0;i<n;i++)
	{
		pflst1[i].read_file(pp1->get_files()[i].c_str());
		pflst1[i].make_fingerprint();
	}
	for (int i=0;i<m;i++)
	{
		pflst2[i].read_file(pp2->get_files()[i].c_str());
		pflst2[i].make_fingerprint();
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			if (pp1->get_ftype()[i]==pp2->get_ftype()[j])
			{
				double ans = fingerprint_compare(pflst1[i],pflst2[j]);
				mat[i][j] = log(ans);
			}else
			{
				mat[i][j] = -1e5;
			}
		}
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			if (mat[i][j]==-1e5)
				cout<<setiosflags(ios::fixed)<<setprecision(2)<< -1 <<"\t";
			else
				cout<<setiosflags(ios::fixed)<<setprecision(2)<< mat[i][j] <<"\t";
		}
		cout<<endl;
	}
	delete[] pflst1;
	delete[] pflst2;
	CostFlow* CF = new CostFlow();
	for (int i=0;i<n;i++)
		CF->add_edge(CostFlow::sour,2+i,1,0);
	for (int i=0;i<m;i++)
		CF->add_edge(2+n+i,CostFlow::sink,1,0);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			CF->add_edge(2+i,2+n+j,1,-mat[i][j]);
	pair<int,double> ans = CF->min_cost_flow();
	for (int i=0;i<n;i++)
		delete[] mat[i];
	delete[] mat;
	cout<<"N="<<n<<" M="<<m<<endl;
	cout<<"MAX FLOW:"<<ans.first<<endl;
	cout<<"MAX COST:"<<ans.second<<endl;
	return pow(exp(-ans.second),2.0/ans.first);
}
