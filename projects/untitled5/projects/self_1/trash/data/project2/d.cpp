#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long double real;
const real eps = 1e-10;
#define MAXN 10010
#define PROB "give"
real ss[MAXN],kk[MAXN],vv[MAXN];
real xx[MAXN];
real work(real a,real b)
{
        real l=-a;
        real r=1e3;
        for (;l+eps<r;)
        {
                real mid=(l+r)*0.5;
                if (mid*mid*mid+mid*mid*a<b)
                        l=mid;
                else
                        r=mid;
        }
        return r;
}

int main()
{
        freopen(PROB".in","r",stdin);
        freopen(PROB".out","w",stdout);
        int n,x,y,z;
        double a0;
        scanf("%d%lf",&n,&a0);
        real e=a0;
        for (int i=0;i<n;i++)
        {
                double a1,a2,a3;
                scanf("%lf%lf%lf",&a1,&a2,&a3);
                ss[i]=a1;
                kk[i]=a2;
                vv[i]=a3;
        }
        real l=0,r=1e10;
        real s,s2;
        while (l+eps<r)
        {
                real mid=(l+r)/2.0;
                s=0;
                s2=0;
                for (int i=0;i<n;i++)
                {
                        xx[i]=work(-vv[i],mid/2/kk[i]);
                        s+=kk[i]*ss[i]*(vv[i]*vv[i]+xx[i]*xx[i]-2*xx[i]*vv[i]);
                        s2+=ss[i]/xx[i];
                }
                if (s<e)
                        l=mid;
                else
                        r=mid;
        }
        //printf("%.5lf\n",(double)l);
        printf("%.6lf\n",(double)s2);
}
