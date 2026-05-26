#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Book.h"
class GoodreadsApp
{
private:
    std::vector<std::unique_ptr<User>> users;
    std::vector<Book> books;
    User* currentUser = nullptr;
    std::string dataFile;

    User* findUser(const std::string& username);
    const User* findUser(const std::string& username) const;
    Book* findBook(const std::string& title);
    const Book* findBook(const std::string& title) const;
    bool isFriends(const std::string& firstUsername, const std::string& secondUsername) const;
    void notifyFollowers(const std::string& authorName, const std::string& publisherName, const std::string& bookTitle);
    std::vector<std::string> tokenize(const std::string& line) const;
    std::string joinFrom(const std::vector<std::string>& tokens, int startIndex) const;
    bool tryParseInt(const std::string& text, int& parsedNumber) const;

    std::string cmdHelp() const;

    std::string cmdRegister(const std::vector<std::string>& tokens);
    std::string cmdLogin(const std::vector<std::string>& tokens);
    std::string cmdLogout();

    std::string cmdSearch(const std::vector<std::string>& tokens) const;
    std::string cmdFollow(const std::vector<std::string>& tokens);

    std::string cmdAddBook(const std::vector<std::string>& tokens);
    std::string cmdCreateShelf(const std::vector<std::string>& tokens);
    std::string cmdDeleteShelf(const std::vector<std::string>& tokens);

    std::string cmdAddToShelf(const std::vector<std::string>& tokens);
    std::string cmdRemoveFromShelf(const std::vector<std::string>& tokens);

    std::string cmdDeleteBook(const std::vector<std::string>& tokens);

    std::string cmdShowShelf(const std::vector<std::string>& tokens) const;
    std::string cmdShowInbox(const std::vector<std::string>& tokens) const;

    std::string cmdReadMsg(const std::vector<std::string>& tokens);
    std::string cmdDeleteMsg(const std::vector<std::string>& tokens);

    std::string cmdFriends(const std::vector<std::string>& tokens) const;
    std::string cmdAddBirthday(const std::vector<std::string>& tokens);

    std::string cmdProfile(const std::vector<std::string>& tokens) const;

    std::string cmdPublish(const std::vector<std::string>& tokens);
    std::string cmdAddSynopsis(const std::vector<std::string>& tokens);
    std::string cmdOffer(const std::vector<std::string>& tokens);

    std::string cmdAcceptOffer(const std::vector<std::string>& tokens);
    std::string cmdLeave(const std::vector<std::string>& tokens);

    std::string cmdFollowers();

public:
    explicit GoodreadsApp(const std::string& dataFile);
    ~GoodreadsApp();
    void run();
};

