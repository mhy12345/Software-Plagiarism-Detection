#ifndef __COST_FLOW_H
#define __COST_FLOW_H
#include<algorithm>
using std::pair;
class CostFlow
{
	public:
		static const int maxn = 110;
		static const int sour = 0;
		static const int sink = 1;
	private:
		int tope;
		struct Edge 
		{
			int np,val;
			double cost;
			Edge *next,*neg;
		}E[maxn*maxn],*V[maxn*2];
		int q[maxn*10],vis[maxn];
		double dis[maxn];
		int dfstime=0;
		int prev[maxn];
		Edge *path[maxn];
	public:
		CostFlow();
		void add_edge(int x,int y,int z,double cost);
		double spfa();
		pair<int,double> min_cost_flow();
		void clear();
};

#endif
