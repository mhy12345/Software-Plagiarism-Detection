#include <cstring>
#include "KRSearchStrategy.h"
#include <cstdio>

KRSearchStrategy::KRSearchStrategy()
{
}

KRSearchStrategy::~KRSearchStrategy()
{
}

void KRSearchStrategy::compile(const char* pat)//预处理模式串hash值
{
	m = strlen(pat);
	hash = 0;
	for (int i=0;i<m;i++)
		hash = hash * p + pat[i];
}

int KRSearchStrategy::match(const char* str)//实现匹配
{
	int n = strlen(str);
	if (n<m)
		return 0;
	unsigned long long *hs = new unsigned long long[n+1];//原串hash数组
	unsigned long long *pp = new unsigned long long[n+1];//p的幂数组
	hs[0] = 0;
	for (int i=0;i<n;i++)
		hs[i+1] = hs[i]*p + str[i];
	pp[0] = 1;
	for (int i=0;i<n;i++)
		pp[i+1] = pp[i]*p;
	//for (int i=0;i<=n;i++) printf("%llu ",hs[i]);printf("\n");
	//for (int i=0;i<=n;i++) printf("%llu ",pp[i]);printf("\n");
	int count = 0;
	for (int i=0;i<=n-m;i++)
		if (hs[i+m] - hs[i]*pp[m] == hash)
		{
			fprintf(stderr,"Match found at position<%d>\n",i);
			count++;
		}
	return count;
}

void KRSearchStrategy::print()
{
	printf("m=%d\n",m);
	printf("hash=%llu\n",hash);
}
