#ifndef __MATCH_STRATEGY_H__
#define __MATCH_STRATEGY_H__

#include <string>
#include <vector>

class MatchStrategy
{
protected:
	std::string pattern_;
public:
	virtual ~MatchStrategy() = default;
public:
	// initialize 
	virtual void initialize(const std::string& pattern) = 0;
	// match str and pattern
	// return first matched position
	virtual std::vector<int> match(const std::string& str) = 0;
};

#endif
