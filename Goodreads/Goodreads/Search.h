#pragma once
#include <string>
class Search
{
private:
	static std::string toLowerCase(const std::string& text);
public:
	static bool matches(const std::string& query, const std::string& target);
};

