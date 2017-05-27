#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define MAXN 401
#define MAXS MAXN*4
#define PI 3.1415926535897
#define vv 4
#define vvv 10000
//#pragma GCC optimize("O2")
struct Complex
{
		double x,y;
		Complex(){};
		Complex(double x,double y):x(x),y(y){};
		Complex operator +(Complex a)
		{
				Complex ret(x + a.x, y + a.y);
				return ret;
		}
		Complex operator -(Complex a)
		{
				Complex ret(x - a.x, y - a.y);
				return ret;
		}
		Complex operator *(Complex a)
		{
				Complex ret(x*a.x - y*a.y, x*a.y + y*a.x);
				return ret;
		}
		Complex operator /(double v)
		{
				Complex ret(x/v,y/v);
				return ret;
		}
		Complex operator =(double x)
		{
				this->x=x;
				return *this;
		}
};
char s1[MAXS],s2[MAXS];
int t1[MAXN],t2[MAXN];
int l1,l2;
Complex g1[MAXN],g2[MAXN];
Complex r1[MAXN],r2[MAXN];
Complex a[MAXN];
long long res[MAXN];
void DFT(Complex s[],Complex r[],int len,int flag)
{
		if (len==1)
		{
				*r=*s;
				return ;
		}
		//Complex t1[len>>1],t2[len>>1];
		//Complex r1[len>>1],r2[len>>1];
		Complex *t1=new Complex[len>>1];
		Complex *t2=new Complex[len>>1];
		Complex *r1=new Complex[len>>1];
		Complex *r2=new Complex[len>>1];
		for (int i=0;i<(len>>1);i++)
		{
				t1[i]=s[i<<1];
				t2[i]=s[i<<1^1];
		}
		DFT(t1,r1,len>>1,flag);
		DFT(t2,r2,len>>1,flag);
		for (int i=0;i<(len>>1);i++)
		{
				Complex tt(cos(2*PI*i/len),-sin(2*PI*i/len));
				tt.y*=flag;
				r[i]=r1[i] + r2[i] * tt;
				r[i+(len>>1)]=r1[i] - r2[i]*tt;
		}
				delete[] t1;
	delete[] t2;
	delete[] r1;
	delete[] r2;


}

int main()
{
		int n,m,nn;
		int n1,n2;
		//scanf("%d\n",&nn);
		nn=1;
		while (nn--)
		{
				scanf("%s\n",s1);
				scanf("%s\n",s2);
				l1=strlen(s1);
				l2=strlen(s2);
				for (int i=0;i<l1/2;i++)swap(s1[i],s1[l1-i-1]);
				for (int i=0;i<l2/2;i++)swap(s2[i],s2[l2-i-1]);
				memset(t1,0,sizeof(t1));
				memset(t2,0,sizeof(t2));
				for (int i=l1-1;i>=0;i--)
						t1[i/vv]=t1[i/vv]*10+s1[i]-'0';
				n1=(l1-1)/vv+1;
				for (int i=l2-1;i>=0;i--)
						t2[i/vv]=t2[i/vv]*10+s2[i]-'0';
				n2=(l2-1)/vv+1;
				for (int i=n1-1;i>=0;i--)g1[i].x=t1[i];
				for (int i=n2-1;i>=0;i--)g2[i].x=t2[i];
				n=max(l1,l2);
				while (n!=(n&(-n)))n-=n&(-n);
				n<<=1;
				DFT(g1,r1,n,1);
				DFT(g2,r2,n,1);
				for (int i=0;i<n;i++)r1[i]=r1[i]+r2[i];
				DFT(r1,a,n,-1);
				for (int i=0;i<n;i++)res[i]=(long long)(a[i].x/n+0.5);
		//		for (int i=0;i<n;i++)
		//		{
		//				printf("%I64d\n",res[i]);
		//		}
				for (int i=0;i<n;i++)
				{
						res[i+1]+=res[i]/vvv;
						res[i]%=vvv;
				}
				while (n && !res[n-1])n--;
				while (res[n])
				{
						res[n+1]+=res[n]/vvv;
						res[n]/=vvv;
						n++;
				}
				printf("%d",(int)res[n-1]);
				for (int i=n-2;i>=0;i--)
				{
						printf("%04d",(int)res[i]);
				}
				printf("\n");
		}
}

