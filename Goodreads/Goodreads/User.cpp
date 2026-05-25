#include "User.h"
#include <stdexcept>
#include <algorithm>

User::User(const std::string& username, const std::string& password, const Date& registrationDate) 
	: username(username), password(passwordCoded(password)), registrationDate(registrationDate)
{
	validateUsername(username);
	validatePassword(password);
}

bool User::checkPassword(const std::string& password) const
{
	return passwordCoded(password) == this->password;
}

void User::addFollower(const std::string& follower)
{
	if (!hasFollower(follower))
	{
		followers.push_back(follower);
	}
}

bool User::hasFollower(const std::string& follower) const
{
	return std::find(followers.begin(), followers.end(), follower) != followers.end();
}

void User::removeFollower(const std::string& follower)
{
	auto followerIterator = std::find(followers.begin(), followers.end(), follower);
	if (followerIterator != followers.end())
	{
		followers.erase(followerIterator);
	}
}

void User::receiveMessage(const Message& message)
{
	inbox.push_back(message);
}

void User::validateUsername(const std::string& username)
{
	if (username.size() < 6 || username.size() > 24)
	{
		throw std::invalid_argument("Username must be between 6 and 24 characters long.");
	}
}

void User::validatePassword(const std::string& password)
{
	if (password.size() < 12 || password.size() > 36)
	{
		throw std::invalid_argument("Password must be between 12 and 36 characters.");
	}
	bool hasLower = false;
	bool hasUpper = false;
	bool hasNonLetter = false;
	for (char character : password)
	{
		if (std::islower((unsigned char)character))
		{
			hasLower = true;
		}
		if (std::isupper((unsigned char)character))
		{
			hasUpper = true;
		}
		if (!std::isalpha((unsigned char)character))
		{
			hasNonLetter = true;
		}
	}
	if (!hasLower)
	{
		throw std::invalid_argument("Password must contain at least one lowercase letter.");
	}
	if (!hasUpper)
	{
		throw std::invalid_argument("Password must contain at least one uppercase letter.");
	}
	if (!hasNonLetter)
	{
		throw std::invalid_argument("Password must contain at least one non-letter character.");
	}
}

std::string User::passwordCoded(const std::string& password)
{
	return password;
}

std::string User::userTypeString(UserType type)
{
	switch (type)
	{
	case UserType::Reader:
		return "Reader";
	case UserType::Author:
		return "Author";
	case UserType::Publisher:
		return "Publisher";
	}
	return "";
}

const std::string& User::getUsername() const
{
	return username;
}

const std::string& User::getPassword() const
{
	return password;
}

const Date& User::getRegistrationDate() const
{
	return registrationDate;
}

const std::vector<std::string>& User::getFollowers() const
{
	return followers;
}

const std::vector<Message>& User::getInbox() const
{
	return inbox;
}

std::vector<Message>& User::getInbox()
{
	return inbox;
}

void User::setUsername(const std::string& username)
{
	validateUsername(username);
	this->username = username;
}

void User::setPassword(const std::string& password)
{
	validatePassword(password);
	this->password = passwordCoded(password);
}

void User::setRegistrationDate(const Date& date)
{
	registrationDate = date;
}