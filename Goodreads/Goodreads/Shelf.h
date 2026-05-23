#pragma once
#include <string>
#include <vector>
#include "Date.h"

class Shelf
{
private:
	std::string name;
	std::vector<std::string> books;
	Date createdAt;
public:
	const std::string& getName() const;
	void removeBook(const std::string& title);
	bool hasBook(const std::string& title) const;
	void addBook(const std::string& title);
	int size() const;
};

