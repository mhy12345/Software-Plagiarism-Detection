#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long double eps = 1e-10;
long double ss[10010],kk[10010],vv[10010];
long double xx[10010];
long double work(long double a,long double b)
{
        long double l=-a;
        long double r=1e3;
        while (l+eps<r)
        {
                long double mid=(l+r)/2.0;
                if (mid*mid*mid+mid*mid*a<b)
                        l=mid;
                else
                        r=mid;
        }
        return r;
}

int main()
{
        freopen("give"".in","r",stdin);
        freopen("give"".out","w",stdout);
        int n;
        long double e;
        int x,y,z;
        double a0;
        scanf("%d%lf",&n,&a0);
        e=a0;
        for (int i=0;i<n;i++)
        {
                double a1,a2,a3;
                scanf("%lf%lf%lf",&a1,&a2,&a3);
                ss[i]=a1;
                kk[i]=a2;
                vv[i]=a3;
        }
        long double l=0,r=1e10;
        long double s,s2;
        while (l+eps<r)
        {
                long double mid=(l+r)/2.0;
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
