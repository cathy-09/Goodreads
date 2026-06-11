#pragma once
#include <string>
class Search
{
private:
	static std::string toLowerCase(const std::string& text);
	static int countDifferences(const std::string& firstString, const std::string& secondString);
public:
	static bool matches(const std::string& query, const std::string& target);
};

