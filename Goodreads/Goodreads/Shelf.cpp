#include "Shelf.h"
#include <string>
#include "BookEntry.h"

const std::string& Shelf::getName() const
{
    return name;
}

void Shelf::removeBook(const std::string& title)
{
    auto bookToErase = std::find(books.begin(), books.end(), title);
    {
        if (bookToErase != books.end())
        {
            books.erase(bookToErase);
        }
    }
}

bool Shelf::hasBook(const std::string& title) const
{
    return std::find(books.begin(), books.end(), title) != books.end();
}

void Shelf::addBook(const std::string& title)
{
    if (!hasBook(title))
    {
        books.push_back(title);
    }
}

int Shelf::size() const
{
    return static_cast<int>(books.size());
}