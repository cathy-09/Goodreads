#pragma once
#include <string>
#include <vector>
#include "Date.h"

class Book
{
private:
	std::string title;
	std::string author;
	std::string publisher;
	std::string summary;
	std::vector<std::string> genres;
	double averageRating = 0.0;
	int ratingCount = 0;
	Date releaseDate;
	int pageCount = 0;
public:
	void addRating(int rating);
	void updateRating(int oldRating, int newRating);
	std::string genresToString() const;
};

