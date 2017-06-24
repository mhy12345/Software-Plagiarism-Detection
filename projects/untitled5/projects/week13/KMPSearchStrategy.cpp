#include <cstring>
#include "KMPSearchStrategy.h"
#include <cstdio>

KMPSearchStrategy::KMPSearchStrategy()
{
	pat = NULL;
	jump = NULL;
}

KMPSearchStrategy::~KMPSearchStrategy()
{
	if (pat)
		delete[] pat;
	if (jump)
		delete[] jump;
}

void KMPSearchStrategy::compile(const char* pat)
{
	m = strlen(pat);
	//数组resize
	if (jump)delete[] jump;
	if (this->pat)delete[] this->pat;
	jump = new int[m];
	this->pat = new char[m];
	strcpy(this->pat,pat);
	jump[0] = -1;
	for (int i=0; i<m-1; i++)
	{
		int p = jump[i];
		while (~p && pat[i+1] != pat[p+1])
			p = jump[p];
		if (pat[i+1] == pat[p+1])
			jump[i+1] = p+1;
		else
			jump[i+1] = -1;
	}
}

int KMPSearchStrategy::match(const char* str)
{
	int n = strlen(str); 
	int count = 0; //匹配个数
	int p = -1;
	for (int i=0; i<n; i++)//KMP算法
	{
		while (~p && pat[p+1] != str[i])
			p = jump[p];
		if (pat[p+1] == str[i])
			p++;
		if (p == m-1)
		{
			fprintf(stderr,"Match found at position<%d>\n",i-m+1);
			count ++;
			p = jump[p];
		}
	}
	return count;
}

void KMPSearchStrategy::print()
{
	printf("m= %d\n",m);
	printf("pat= %s\n",pat);
	printf("jump= ");
	for (int i=0;i<m;i++) printf("%d ",jump[i]);printf("\n");
}
