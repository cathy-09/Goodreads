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