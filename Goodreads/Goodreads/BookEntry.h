#pragma once
#include <string>

enum class ReadStatus 
{ 
	WantToRead, 
	Reading, 
	Read
};


class BookEntry
{
private:
	std::string bookTitle;
	ReadStatus status;
	int rating;
public:
    BookEntry(const std::string& title, ReadStatus status, int rating = 0);
	const std::string& getBookTitle() const;
    ReadStatus getStatus() const;
    int getRating() const;
    void setStatus(ReadStatus newStatus);
    void setRating(int newRating);
    static ReadStatus parseStatus(const std::string& string);
    static std::string statusToString(ReadStatus string);
};

