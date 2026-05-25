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
	Shelf() = default;
	Shelf(const std::string& name, const Date& createdAt);
	const std::string& getName() const;
	const Date& getCreatedAt() const;
	const std::vector<std::string>& getBooks() const;
	void removeBook(const std::string& title);
	bool hasBook(const std::string& title) const;
	void addBook(const std::string& title);
	int size() const;
};

