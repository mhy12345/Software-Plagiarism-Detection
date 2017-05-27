#ifndef __KARP_RABIN_H__
#define __KARP_RABIN_H__

#include "match_strategy.h"

class KarpRabinStrategy : public MatchStrategy
{
	typedef long long value_t;
	value_t hash_mod, hash_base, hash_pat, hash_empty;
public:
	void initialize(const std::string& pattern);
	std::vector<int> match(const std::string& str);
};

#endif
