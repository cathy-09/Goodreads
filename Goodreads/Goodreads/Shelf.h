#pragma once
#include <string>
#include <vector>

class Shelf
{
private:
	std::string name;
	std::vector<std::string> books;
public:
	const std::string& getName() const;
	void removeBook(const std::string& title);
};

