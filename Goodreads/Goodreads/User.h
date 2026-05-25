#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Message.h"

enum class UserType 
{ 
	Reader, 
	Author, 
	Publisher
};

class User
{
private:
	std::string username;
	std::string password;
	Date registrationDate;
	std::vector<std::string> followers;
	std::vector<Message> inbox;
public:
	User() = default;
	User(const std::string& username, const std::string& password, const Date& registrationDate);
	virtual ~User() = default;
	bool checkPassword(const std::string& password) const;
	void addFollower(const std::string& follower);
	bool hasFollower(const std::string& follower) const;
	void removeFollower(const std::string& follower);
	void receiveMessage(const Message& message);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	const Date& getRegistrationDate() const;
	const std::vector<std::string>& getFollowers() const;
	const std::vector<Message>& getInbox() const;
	std::vector<Message>& getInbox();

	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setRegistrationDate(const Date& date);

	static void validateUsername(const std::string& username);
	static void validatePassword(const std::string& password);
	static std::string passwordCoded(const std::string& password);

	std::string userTypeString(UserType type);

	virtual UserType type() const = 0;
};
