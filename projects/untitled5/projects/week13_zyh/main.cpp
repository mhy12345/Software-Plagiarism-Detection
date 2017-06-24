#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <ctime>

#include "match_strategy.h"
#include "karp_rabin.h"
#include "kmp.h"

typedef std::shared_ptr<MatchStrategy> StrategyPtr;

std::string read_without_space(const std::string& filename)
{
	std::ifstream ifs(filename.c_str());
	std::string str, tmp;

	while(ifs >> tmp)
		str += tmp;

	return str;
}

std::vector<std::string> read_patterns(const std::string& filename)
{
	std::ifstream ifs(filename.c_str());
	std::vector<std::string> pats;
	std::string pat;

	while(ifs >> pat) pats.push_back(pat);

	return pats;
}

void do_match(
	StrategyPtr strategy,
	const std::string& str,
	const std::vector<std::string>& pats)
{
	clock_t clock_begin = std::clock();

	for(const std::string& pat : pats)
	{
		strategy->initialize(pat);
		auto ret = strategy->match(str);
		std::cout << "Pattern '" << pat << "' matched " << ret.size() << " time(s)\n";
	}

	clock_t clock_end = std::clock();
	double time_span = double(clock_end - clock_begin) / CLOCKS_PER_SEC;

	std::cout << ">>>> Time cost: " << time_span << "s <<<<" << std::endl;
}

int main()
{
	std::string source_filename, pattern_filename;
	std::cout << "Input source's filename (you can input data/text_format.cc): ";
	std::cin >> source_filename;
	std::cout << "Input patterns' filename (you can input data/patterns.txt): ";
	std::cin >> pattern_filename;

	std::string source = read_without_space(source_filename);
	auto patterns = read_patterns(pattern_filename);

	StrategyPtr kmp = std::make_shared<KMPStrategy>();
	StrategyPtr karp_rabin = std::make_shared<KarpRabinStrategy>();

	std::cout << ">>>> KMP algorithm <<<<" << std::endl;
	do_match(kmp, source, patterns);

	std::cout << std::endl;

	std::cout << ">>>> Karp-Rabin algorithm <<<<" << std::endl;
	do_match(karp_rabin, source, patterns);

	return 0;
}
