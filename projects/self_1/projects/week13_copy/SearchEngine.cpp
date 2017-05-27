#include "SearchEngine.h"
#include "KMPS.h"
#include "KRS.h"
#include <cstdio>
#include <ctime>
#include <cstring>
const int SearchEngine::maxn = 1000000;
const int SearchEngine::maxm = 30;

SearchEngine::SearchEngine(StrategyName KR)
{
	SS = NULL;
	choose_strategy(KR);
}

void SearchEngine::choose_strategy(StrategyName KR)//改变当前策略
{
	if (SS)delete SS;
	switch(KR)
	{
		case (SearchEngine::KMP):
			SS = new KMPS();
			fprintf(stderr,"Strategy switch into KMP\n");
			break;
		case (SearchEngine::KR):
			SS = new KRS();
			fprintf(stderr,"Strategy switch into KR\n");
			break;
	}
	match = new char[maxn];
	pattern = new char[maxm];
}

void SearchEngine::load_match(const char* filename)
{
	FILE *fin = fopen(filename,"r");
	int n = 0;
	char ch;
	while (n<maxn && ~(ch = fgetc(fin)))
		if (ch!=' ' && ch!='\n' && ch!='\r' && ch!='\t')
		match[n++] = ch;
	fclose(fin);
}

void SearchEngine::load_pattern(const char* filename)
{
	clock_t begin = clock();
	FILE *fin = fopen(filename,"r");
	while (fgets(pattern,maxn,fin))
	{
		pattern[strlen(pattern)-1] = '\0';
		SS->compile(pattern);
		printf("Match pattern :%s\n",pattern);
		printf("Matches count:%d\n",SS->match(match));
	}
	fclose(fin);
	clock_t end = clock();
	printf("Time usage: %lums\n",end-begin);
}

