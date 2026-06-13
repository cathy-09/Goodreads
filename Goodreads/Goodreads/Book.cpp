#include "Book.h"
#include "GoodreadsException.h"
#include "RatingException.h"
#include <stdexcept>

Book::Book(const std::string& title, const std::string& author,
    const std::string& publisher, const Date& releaseDate,
    int pageCount, const std::vector<std::string>& genres) 
    : title(title), author(author),
    publisher(publisher), genres(genres),
    releaseDate(releaseDate), pageCount(pageCount)
{

}

void Book::addRating(int rating)
{
    if (rating < 1 || rating > 5)
    {
        throw RatingException("Rating must be 1-5.");
    }
    averageRating = (averageRating * ratingCount + rating) / (ratingCount + 1);
    ++ratingCount;
}

void Book::updateRating(int oldRating, int newRating)
{
    if (ratingCount == 0) 
    {
        addRating(newRating); 
        return;
    }
    if (oldRating < 1 || oldRating > 5 || newRating < 1 || newRating > 5)
    {
        throw RatingException("Rating must be 1-5.");
    }
    averageRating = ((averageRating * ratingCount) - oldRating + newRating) / ratingCount;
}

std::string Book::genresToString() const
{
    std::string stringResult;
    for (size_t index = 0; index < genres.size(); ++index) 
    {
        if (index)
        {
            stringResult += ", ";
        }
        stringResult += genres[index];
    }
    return stringResult;
}

const std::string& Book::getTitle() const
{
    return title;
}

const std::string& Book::getAuthor() const
{
    return author;
}

const std::string& Book::getPublisher() const
{
    return publisher;
}

const std::string& Book::getSummary() const
{
    return summary;
}

const std::vector<std::string>& Book::getGenres() const
{
    return genres;
}

double Book::getAverageRating() const
{
    return averageRating;
}

int Book::getRatingCount() const
{
    return ratingCount;
}

const Date& Book::getReleaseDate() const
{
    return releaseDate;
}

int Book::getPageCount() const
{
    return pageCount;
}

void Book::setSummary(const std::string& summary)
{
    this->summary = summary;
}

void Book::setGenres(const std::vector<std::string>& genres)
{
    this->genres = genres;
}

void Book::setAverageRating(double rating)
{
    this->averageRating = rating;
}

void Book::setRatingCount(int count)
{
    this->ratingCount = count;
}
