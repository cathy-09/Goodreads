#include "Publisher.h"

Publisher::Publisher(const std::string& username, const std::string& password, const Date& registrationDate)
	: User(username, password, registrationDate)
{

}

UserType Publisher::type() const 
{
	return UserType::Publisher; 
}

bool Publisher::hasAuthor(const std::string& name) const
{
	return std::find(authors.begin(), authors.end(), name) != authors.end();
}

void Publisher::addAuthor(const std::string& name)
{
	if (!hasAuthor(name))
	{
		authors.push_back(name);
	}
}

void Publisher::removeAuthor(const std::string& name) 
{
	auto authorToRemove = std::find(authors.begin(), authors.end(), name);
	if (authorToRemove != authors.end())
	{
		authors.erase(authorToRemove);
	}
}

void Publisher::addPublishedBook(const std::string& title)
{
	if (std::find(publishedBooks.begin(), publishedBooks.end(), title) == publishedBooks.end())
	{
		publishedBooks.push_back(title);
	}
}

const std::vector<std::string>& Publisher::getAuthors() const
{
	return authors;
}

const std::vector<std::string>& Publisher::getPublishedBooks() const
{
	return publishedBooks;
}