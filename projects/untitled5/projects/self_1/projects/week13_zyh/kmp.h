#ifndef __KMP_H__
#define __KMP_H__

#include "match_strategy.h"

class KMPStrategy : public MatchStrategy
{
	std::vector<int> next_;
public:
	void initialize(const std::string& pattern);
	std::vector<int> match(const std::string& str);
};

#endif
