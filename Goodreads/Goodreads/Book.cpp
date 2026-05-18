#include "Book.h"
#include <stdexcept>

void Book::addRating(int rating)
{
    if (rating < 1 || rating > 5)
    {
        throw std::invalid_argument("Rating must be 1-5.");
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
        throw std::invalid_argument("Rating must be 1-5.");
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