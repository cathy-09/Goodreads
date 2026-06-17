#include <algorithm>
#include "Reader.h"
#include "GoodreadsApp.h"

Reader::Reader(const std::string& username, const std::string& password, const Date& registrationDate)
    : User(username, password, registrationDate)
{

}

UserType Reader::type() const 
{ 
    return UserType::Reader;
}

void Reader::receiveMessage(const Message& message)
{
    inbox.push_back(message);
}

const std::vector<Message>& Reader::getInbox() const
{
    return inbox;
}

std::vector<Message>& Reader::getInbox()
{
    return inbox;
}


BookEntry* Reader::findBook(const std::string& title)
{
    for (auto& entry : books)
    {
        if (entry.getBookTitle() == title)
        {
            return &entry;
        }
    }
    return nullptr;
}

const BookEntry* Reader::findBook(const std::string& title) const
{
    for (auto& entry : books)
    {
        if (entry.getBookTitle() == title)
        {
            return &entry;
        }
    }
    return nullptr;
}

bool Reader::hasBook(const std::string& title) const 
{
    for (const auto& entry : books)
    {
        if (entry.getBookTitle() == title)
        {
            return true;
        }
    }
    return false;
}

bool Reader::hasFavorite(const std::string& title) const
{
    return std::find(favorites.begin(), favorites.end(), title) != favorites.end();
}

Shelf* Reader::findShelf(const std::string& name)
{
    for (auto& shelf : shelves)
    {
        if (shelf.getName() == name)
        {
            return &shelf;
        }
    }
    return nullptr;
}

const Shelf* Reader::findShelf(const std::string& name) const
{
    for (auto& shelf : shelves)
    {
        if (shelf.getName() == name)
        {
            return &shelf;
        }
    }
    return nullptr;
}

bool Reader::shelfExists(const std::string& name) const
{
    return findShelf(name) != nullptr;
}

void Reader::removeBookFromAllShelves(const std::string& title)
{
    for (auto& shelf : shelves)
    {
        shelf.removeBook(title);
    }
}

bool Reader::isFavorite(const std::string& title) const 
{
    return std::find(favorites.begin(), favorites.end(), title) != favorites.end();
}

const std::vector<BookEntry>& Reader::getBooks() const
{
    return books;
}

std::vector<BookEntry>& Reader::getBooks()
{
    return books;
}

const std::vector<Shelf>& Reader::getShelves() const
{
    return shelves;
}

std::vector<Shelf>& Reader::getShelves()
{
    return shelves;
}

const std::vector<std::string>& Reader::getFavorites() const
{
    return favorites;
}

const std::optional<Date>& Reader::getBirthday() const
{
    return birthday;
}

void Reader::addBook(const BookEntry& book)
{
    if (!hasBook(book.getBookTitle()))
    {
        books.push_back(book);
    }
}

void Reader::deleteBook(const std::string& title)
{
    auto foundBookIterator = std::find_if(books.begin(), books.end(),
        [&](const BookEntry& bookEntry)
        {
            return bookEntry.getBookTitle() == title;
        });
    if (foundBookIterator != books.end())
    {
        books.erase(foundBookIterator);
        removeBookFromAllShelves(title);
        removeFavorite(title);
    }
}

void Reader::createShelf(const Shelf& shelf)
{
    if (!shelfExists(shelf.getName()))
    {
        shelves.push_back(shelf);
    }
}

void Reader::deleteShelf(const std::string& name)
{
    auto bookShelf = std::find_if(shelves.begin(), shelves.end(),
        [&](const Shelf& shelf) 
        { 
            return shelf.getName() == name; 
        });

    if (bookShelf != shelves.end())
    {
        shelves.erase(bookShelf);
    }
}

void Reader::addFavorite(const std::string& title)
{
    if (!isFavorite(title))
    {
        favorites.push_back(title);
    }
}

void Reader::removeFavorite(const std::string& title)
{
    auto favoriteBookIterator = std::find(favorites.begin(), favorites.end(), title);
    if (favoriteBookIterator != favorites.end())
    {
        favorites.erase(favoriteBookIterator);
    }
}

void Reader::setBirthday(const Date& date)
{
    birthday = date;
}

void Reader::clearBirthday()
{
    birthday = {};
}
