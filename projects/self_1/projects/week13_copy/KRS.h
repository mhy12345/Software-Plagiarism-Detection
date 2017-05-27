#ifndef __KRSEARCHSTRATEGY_H
#define __KRSEARCHSTRATEGY_H
#include "SearchStrategy.h"

class KRS:public SearchStrategy
{
	private:
		static const unsigned p = 137;
		unsigned long long hash;
		int m;
	public:
		//用法见基类
		KRS();
		~KRS();
		void compile(const char* pat);
		int match(const char* str);
		void print();
};
#endif
