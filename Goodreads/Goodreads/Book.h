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
	Book() = default;
	Book(const std::string& title, const std::string& author, const std::string& publisher, const Date& releaseDate, int pageCount, const std::vector<std::string>& genres);
	void addRating(int rating);
	void updateRating(int oldRating, int newRating);
	std::string genresToString() const;
	const std::string& getTitle() const;
	const std::string& getAuthor() const;
	const std::string& getPublisher() const;
	const std::string& getSummary() const;
	const std::vector<std::string>& getGenres() const;
	double getAverageRating() const;
	int getRatingCount() const;
	const Date& getReleaseDate() const;
	int getPageCount() const;
	void setSummary(const std::string& summary);
	void setGenres(const std::vector<std::string>& genres);
	void setAverageRating(double rating);
	void setRatingCount(int count);

};

