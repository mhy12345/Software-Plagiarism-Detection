#include <iostream>
#include <cstring>
#include "cost_flow.h"
#define INF 0x3f3f3f3f
using namespace std;

CostFlow::CostFlow()
{
    clear();
}
void CostFlow::clear()
{
    tope = -1;
    memset(V,0,sizeof(V));
}
void CostFlow::add_edge(int x,int y,int z,double cost)
{
    //cout<<"Add"<<x<<" "<<y<<" "<<z<<" "<<cost<<endl;
    E[++tope].np=y;
    E[tope].val=z;
    E[tope].cost=cost;
    E[tope].next=V[x];
    V[x]=&E[tope];
    E[++tope].np=x;
    E[tope].val=0;
    E[tope].cost=-cost;
    E[tope].next=V[y];
    V[y]=&E[tope];

    E[tope].neg=&E[tope-1];
    E[tope-1].neg=&E[tope];
}
double CostFlow::spfa()
{
    int head=-1,tail=0,now;
    Edge *ne;
    for (int i=0;i<maxn;i++)
        dis[i] = 1e10;
    q[0]=sour;
    vis[sour]=++dfstime;
    dis[sour]=0;
    while (head<tail)
    {
        now=q[++head];
        vis[now]=0;
        for (ne=V[now];ne;ne=ne->next)
        {
            if (ne->val&&dis[ne->np]>dis[now]+ne->cost)
            {
                dis[ne->np]=dis[now]+ne->cost;
                prev[ne->np]=now;
                path[ne->np]=ne;
                if (vis[ne->np]!=dfstime)
                {
                    vis[ne->np]=dfstime;
                    q[++tail]=ne->np;
                }
            }
        }
    }
    return dis[sink];
}
pair<int,double> CostFlow::min_cost_flow()
{
    double ds;
    int fl,x;
    pair<int,double> ret;
    ret.first=ret.second=0;
    while (ds=spfa(),ds!=1e10)
    {
        x=sink;
        fl=INF;
        while (x!=sour)
        {
            fl=min(fl,path[x]->val);
            x=prev[x];
        }
        x=sink;
        while (x!=sour)
        {
            path[x]->val-=fl;
            path[x]->neg->val+=fl;
            x=prev[x];
        }
        ret.first+=fl;
        ret.second+=ds*fl;
    }
    return ret;
}
