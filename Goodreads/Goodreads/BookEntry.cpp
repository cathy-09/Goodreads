#include "BookEntry.h"
#include <string>
#include <stdexcept>

BookEntry::BookEntry(const std::string& title, ReadStatus status, int rating) : bookTitle(title), status(status), rating(rating)
{

}

const std::string& BookEntry::getBookTitle() const
{
    return bookTitle;
}

ReadStatus BookEntry::getStatus() const
{
    return status;
}

int BookEntry::getRating() const
{
    return rating;
}

void BookEntry::setStatus(ReadStatus newStatus)
{
    status = newStatus;
}

void BookEntry::setRating(int newRating)
{
    rating = newRating;
}

ReadStatus BookEntry::parseStatus(const std::string& string)
{
    if (string == "PlanToRead")
    {
        return ReadStatus::PlanToRead;
    }
    if (string == "Reading")
    {
        return ReadStatus::Reading;
    }
    if (string == "Paused")
    {
        return ReadStatus::Paused;
    }
    if (string == "Dropped")
    {
        return ReadStatus::Dropped;
    }
    throw std::invalid_argument("Unknown ReadStatus: " + string);
}

std::string BookEntry::statusToString(ReadStatus string)
{
    if (string == ReadStatus::PlanToRead)
    {
        return "PlanToRead";
    }
    if (string == ReadStatus::Reading)
    {
        return "Reading";
    }
    if (string == ReadStatus::Paused)
    {
        return "Paused";
    }
    if (string == ReadStatus::Dropped)
    {
        return "Dropped";
    }
    return "Unknown";
}
    
