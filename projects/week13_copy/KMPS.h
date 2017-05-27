#ifndef __KMPSEARCHSTRATEGY_H
#define __KMPSEARCHSTRATEGY_H
#include "SearchStrategy.h"

class KMPS:public SearchStrategy
{
	private:
		int *jump;//辅助数组
		char *pat;//原串
		int m;//串长
	public:
		KMPS();
		~KMPS();
		void compile(const char* pat);//预处理模式串
		int match(const char* str);//匹配
		void print();//输出
};
#endif
