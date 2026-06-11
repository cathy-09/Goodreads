#include <algorithm>
#include "Author.h"

Author::Author(const std::string& username, const std::string& password, const Date& registrationDate)
	:Reader(username, password, registrationDate)
{

}

UserType Author::type() const
{
	return UserType::Author;
}

void Author::addPublishedBook(const std::string& title)
{
	if (std::find(publishedBooks.begin(), publishedBooks.end(), title) == publishedBooks.end())
	{
		publishedBooks.push_back(title);
	}
}

bool Author::worksWithPublisher(const std::string& publisher) const
{
	return std::find(publishers.begin(), publishers.end(), publisher) != publishers.end();
}

void Author::addPublisher(const std::string& publisher)
{
	if (!worksWithPublisher(publisher))
	{
		publishers.push_back(publisher);
	}
}

void Author::removePublisher(const std::string& publisher)
{
	auto publisherToRemove = std::find(publishers.begin(), publishers.end(), publisher);
	if (publisherToRemove != publishers.end())
	{
		publishers.erase(publisherToRemove);
	}
}

const std::vector<std::string>& Author::getPublishedBooks() const
{
	return publishedBooks;
}

const std::vector<std::string>& Author::getPublishers() const
{
	return publishers;
}
