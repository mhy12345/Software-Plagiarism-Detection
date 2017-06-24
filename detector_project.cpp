#include "detector_project.h"
#include "costflow_alg.h"
#include "strategies_file.h"
#include <cmath>
#include <iostream>
#include <set>
#include <iomanip>
#include <algorithm>
#include <QStringListModel>
#ifdef DEBUG
#include <QDebug>
#endif
using namespace std;

ProjectDetector::ProjectDetector(QStringListModel *_model1, QStringListModel *_model2):
    QObject(), model1(_model1), model2(_model2)
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
#ifdef DEBUG
    cout<<"====================="<<endl;
    for (auto w : pp1->get_files())
        cout<<w<<endl;
    cout<<"====================="<<endl;
    for (auto w : pp2->get_files())
        cout<<w<<endl;
#endif
    model1 ->removeRows(0, model1 ->rowCount());
    for (auto w : pp1 ->get_files())
    {
        model1 ->insertRow(0);
        model1 ->setData(model1 ->index(0), QString::fromStdString(w));
    }
    model2 ->removeRows(0, model2 ->rowCount());
    for (auto w : pp2 ->get_files())
    {
        model2 ->insertRow(0);
        model2 ->setData(model2 ->index(0), QString::fromStdString(w));
    }

    int n = pp1->get_files().size();
    int m = pp2->get_files().size();
    all_compare_progress = static_cast<double>(n * m + m + n);
    double **mat = new double*[n];
    for (int i=0;i<n;i++)
        mat[i] = new double[m];
    PFile* pflst1 = new PFile[n];
    PFile* pflst2 = new PFile[m];
    for (int i=0;i<n;i++)
    {
        pflst1[i].read_file(pp1->get_files()[i].c_str());
        pflst1[i].make_fingerprint();
        now_compare_progress = static_cast<double>(i);
        emit progress_update();
    }
    for (int i=0;i<m;i++)
    {
        pflst2[i].read_file(pp2->get_files()[i].c_str());
        pflst2[i].make_fingerprint();
        now_compare_progress = static_cast<double>(i + n);
        emit progress_update();
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
            now_compare_progress = static_cast<double>(i * m + j + m + n);
            emit progress_update();
        }
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if (mat[i][j]==-1e5)
                similarity_table<<setiosflags(ios::fixed)<<setprecision(2)<< -1 << "\t";
            else
                similarity_table<<setiosflags(ios::fixed)<<setprecision(2)<< exp(mat[i][j]) <<"\t";
        }
        similarity_table<<"\n";
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
    now_compare_progress = all_compare_progress;
    double result = pow(exp(-ans.second),4.0/ans.first);
    //cout<<result<<endl;
    result = sin((result-0.5)*3.14159265)*.5+.5;
    //cout<<result<<endl;
    return result;
}
