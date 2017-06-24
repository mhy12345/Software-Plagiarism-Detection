#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        int n,m;
        int x,y,z;
        scanf("%d",&n);
        for (int i=1;i<n;i++)
        {
                scanf("%d%d",&x,&y);
				printf("%d\n", x+y);
        }
}
