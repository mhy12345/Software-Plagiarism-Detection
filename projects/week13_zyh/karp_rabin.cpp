#include "karp_rabin.h"

void KarpRabinStrategy::initialize(const std::string& pattern)
{
	pattern_ = pattern;

	hash_mod = 1000000007, hash_base = 17;

	hash_pat = 0;
	for(char c : pattern_)
		hash_pat = (hash_pat * hash_base + c) % hash_mod;

	if(hash_pat < 0) hash_pat += hash_mod;

	hash_empty = 1;
	for(size_t i = 1; i < pattern_.size(); ++i)
		hash_empty = hash_empty * hash_base % hash_mod;
}

std::vector<int> KarpRabinStrategy::match(const std::string& str)
{
	std::vector<int> matched;
	if(str.size() < pattern_.size()) 
		return matched;

	int pat_n = pattern_.size();
	int str_n = str.size();
	value_t now = 0;

	for(int i = 0; i != pat_n; ++i)
		now = (now * hash_base + str[i]) % hash_mod;

	if(now < 0) now += hash_mod;

	if(now == hash_pat)
		matched.push_back(0);

	for(int i = pat_n; i < str_n; ++i)
	{
		now = ((now - hash_empty * str[i - pat_n]) * hash_base + str[i]) % hash_mod;
		if(now < 0) now += hash_mod;
		if(now == hash_pat)
			matched.push_back(i - pat_n + 1);
	}

	return matched;
}
