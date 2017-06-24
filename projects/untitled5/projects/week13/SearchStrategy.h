#ifndef __SEARCHSTRATEGY_H
#define __SEARCHSTRATEGY_H

class SearchStrategy
{
	public:
		virtual void compile(const char* pat) = 0;//预处理模式串
		virtual int match(const char* str) = 0;//匹配
		virtual void print() = 0;//输出debug信息
		virtual ~SearchStrategy();
};

#endif
