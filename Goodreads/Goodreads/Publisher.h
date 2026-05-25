#pragma once
#include "User.h"

class Publisher : public User
{
private:
	std::vector<std::string> authors;
	std::vector<std::string> publishedBooks;
public:
	Publisher() = default;
	Publisher(const std::string& username, const std::string& password, const Date& registrationDate);

	UserType type() const override;
	bool hasAuthor(const std::string& name) const;
	void addAuthor(const std::string& name);
	void removeAuthor(const std::string& name);
	void addPublishedBook(const std::string& title);

	const std::vector<std::string>& getAuthors() const;
	const std::vector<std::string>& getPublishedBooks() const;
};

