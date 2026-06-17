#pragma once
#include <string>
class Search
{
private:
	static std::string toLowerCase(const std::string& text);
	static int countDifferences(const std::string& firstString, const std::string& secondString);
	//static std::string substring(const std::string& string, size_t start, size_t length);
	static int bestDistance(const std::string& query, const std::string& target);
public:
	static bool matches(const std::string& query, const std::string& target);
};

