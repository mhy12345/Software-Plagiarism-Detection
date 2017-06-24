#include "kmp.h"

void KMPStrategy::initialize(const std::string& pattern)
{
	pattern_ = pattern;
	next_.assign(pattern_.size(), 0);

	int cur = -1;

	for(int i = 0; i < (int)pattern_.size(); ++i)
	{
		while(cur != -1 && pattern_[cur] != pattern_[i])
			cur = next_[cur];
		next_[i] = cur++;
	}
}

std::vector<int> KMPStrategy::match(const std::string& str)
{
	std::vector<int> matched;

	for(int i = 0, now = 0; i < (int)str.size(); ++i)
	{
		while(now != -1 && str[i] != pattern_[now])
			now = next_[now];
		if(now == (int)pattern_.size() - 1)
			matched.push_back(i - pattern_.size() + 1);
		else ++now;
	}

	return matched;
}
