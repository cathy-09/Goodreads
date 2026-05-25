#pragma once
#include "User.h"
#include "Reader.h"

class Author : public Reader
{
private:
	std::vector<std::string> publishedBooks;
	std::vector<std::string> publishers;
public:
	Author() = default;
	Author(const std::string& username, const std::string& password, const Date& registrationDate);

	UserType type() const override;
	void addPublishedBook(const std::string& title);
	bool worksWithPublisher(const std::string& publisher) const;
	void addPublisher(const std::string& publisher);
	void removePublisher(const std::string& publisher);

	const std::vector<std::string>& getPublishedBooks() const;
	const std::vector<std::string>& getPublishers() const;
};

