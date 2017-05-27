#include "SearchEngine.h"

int main()
{
	SearchEngine SE;
	SE.choose_strategy(SearchEngine::KR);
	SE.load_match("codes/aaa.cpp");
	SE.load_pattern("codes/aaa.pat");
	SE.choose_strategy(SearchEngine::KMP);
	SE.load_match("codes/bbb.cpp");
	SE.load_pattern("codes/bbb.pat");
}
