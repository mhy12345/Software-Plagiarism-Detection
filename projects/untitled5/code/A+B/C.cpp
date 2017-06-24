#include <cstdio>
#include <iostream>
#include <cstring>
#define INF 1000000
using namespace std;
int u[501],v[501],h[501],ne[501],map[501],f[501];
int n,m,en=0,S,T;
void add(int a,int b,int r)
{
    u[en]=a;v[en]=b;ne[en]=h[a];f[en]=r;h[a]=en++;
    u[en]=b;v[en]=a;ne[en]=h[b];f[en]=0;h[b]=en++;
}
bool tell()
{
    memset(map,-1,sizeof map);
    int que[501];
    int head=0,tail=0;
    que[tail++]=S;
    map[S]=0;
    while (head<tail){
        int u=que[head++];
        for (int i=h[u];i!=-1;i=ne[i]){
            if (map[v[i]]==-1&&f[i]){
                map[v[i]]=map[u]+1;
                que[tail++]=v[i];
            }
        }
    }
    if (map[T]!=-1) return true;
    else return false;
}
int zeng (int k,int now)
{
    if (k==T) return now;
    int r=0;
    for (int i=h[k];i!=-1&&now>r;i=ne[i]){
        if (map[k]+1==map[v[i]]&&f[i]!=0){
            int t=zeng(v[i],min(now-r,f[i]));
            f[i]-=t;f[i^1]+=t;r+=t;
        }
    }
    if (!r) map[k]=-1;
    return r;
}
int dinic()
{
    int r=0,t;
    while (tell()) while (t=zeng(S,INF)) r+=t;
    return r; 
}
int main()
{
    memset(h,-1,sizeof h);
    S=0;T=2;
    int a,b;
    scanf("%d%d",&a,&b);
    add(S,1,a),add(S,1,b),add(1,T,a),add(1,T,b);
    cout<<dinic()<<endl;
}
