#pragma once
#include <string>

class BookEntry
{
private:
	std::string bookTitle;
public:
	const std::string& getBookTitle() const;
};

