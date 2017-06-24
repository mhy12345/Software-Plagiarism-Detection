#ifndef __SEARCHENGINE_H
#define __SEARCHENGINE_H
#include "KMPSearchStrategy.h"
#include "KRSearchStrategy.h"

class SearchEngine
{
	private:
		SearchStrategy* SS;
		char *match,*pattern;
	public:
		static const int maxn;
		static const int maxm;
		enum StrategyName{KMP,KR};
		SearchEngine(StrategyName SN = KR);
		void choose_strategy(StrategyName);
		void load_match(const char* filename);//从文件读入原串
		void load_pattern(const char* filename);//从文件读入模式串
};
#endif
