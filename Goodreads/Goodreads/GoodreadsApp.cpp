#include "GoodreadsApp.h"
#include "FileManager.h"
#include "Author.h"
#include "Publisher.h"
#include "Search.h"
#include <filesystem>
#include <iostream>

GoodreadsApp::GoodreadsApp(const std::string& dataFile) : dataFile(dataFile)
{
	FileManager::load(dataFile, users, books);
}

GoodreadsApp::~GoodreadsApp()
{
	FileManager::save(dataFile, users, books);
}

void GoodreadsApp::run()
{
    std::cout << "Welcome to Goodreads. Type 'help' for commands.\n";
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            continue;
        }
        auto tokens = tokenize(line);
        if (tokens.empty())
        {
            continue;
        }
        const std::string& cmd = tokens[0];
        std::string output;
        if (cmd == "exit")
        {
            std::cout << "Saving data... Goodbye!\n";
            return;
        }
        else if (cmd == "help")
        {
            output = cmdHelp();
        }
        else if (cmd == "register")
        {
            output = cmdRegister(tokens);
        }
        else if (cmd == "login")
        {
            output = cmdLogin(tokens);
        }
        else if (cmd == "logout")
        {
            output = cmdLogout();
        }
        else if (!currentUser)
        {
            output = "Please login first.";
        }
        else if (cmd == "search")
        {
            output = cmdSearch(tokens);
        }
        else if (cmd == "follow")
        { 
            output = cmdFollow(tokens);
        }
        else if (cmd == "add-book")
        {
            output = cmdAddBook(tokens);
        }
        else if (cmd == "create-shelf")
        {
            output = cmdCreateShelf(tokens);
        }
        else if (cmd == "delete-shelf")
        {
            output = cmdDeleteShelf(tokens);
        }
        else if (cmd == "add-to-shelf")
        {
            output = cmdAddToShelf(tokens);
        }
        else if (cmd == "remove-from-shelf")
        {
            output = cmdRemoveFromShelf(tokens);
        }
        else if (cmd == "delete-book")
        {
            output = cmdDeleteBook(tokens);
        }
        else if (cmd == "show-shelf")
        {
            output = cmdShowShelf(tokens);
        }
        else if (cmd == "show-inbox")
        {
            output = cmdShowInbox(tokens);
        }
        else if (cmd == "read-msg")
        {
            output = cmdReadMsg(tokens);
        }
        else if (cmd == "delete-msg")
        {
            output = cmdDeleteMsg(tokens);
        }
        else if (cmd == "friends")
        {
            output = cmdFriends(tokens);
        }
        else if (cmd == "add-birthday")
        {
            output = cmdAddBirthday(tokens);
        }
        else if (cmd == "profile")
        { 
            output = cmdProfile(tokens); 
        }
        else if (cmd == "publish")
        {
            output = cmdPublish(tokens);
        }
        else if (cmd == "add-summary")
        {
            output = cmdAddSynopsis(tokens);
        }
        else if (cmd == "offer")
        {
            output = cmdOffer(tokens);
        }
        else if (cmd == "accept-offer")
        {
            output = cmdAcceptOffer(tokens);
        }
        else if (cmd == "leave")
        {
            output = cmdLeave(tokens);
        }
        else if (cmd == "followers")
        {
            output = cmdFollowers();
        }
        else
        {
            output = "Unknown command: " + cmd + ". Type 'help'.";
        }
        std::cout << output << "\n";
    }
}

User* GoodreadsApp::findUser(const std::string& username)
{
    for (auto& userPtr : users)
    {
        if (userPtr->getUsername() == username)
        {
            return userPtr.get();
        }
    }
    return nullptr;
}

const User* GoodreadsApp::findUser(const std::string& username) const
{
    for (auto& userPtr : users)
    {
        if (userPtr->getUsername() == username)
        {
            return userPtr.get();
        }
    }
    return nullptr;
}

Book* GoodreadsApp::findBook(const std::string& title)
{
    for (auto& book : books)
    {
        if (book.getTitle() == title)
        {
            return &book;
        }
    }
    return nullptr;
}

const Book* GoodreadsApp::findBook(const std::string& title) const
{
    for (auto& book : books)
    {
        if (book.getTitle() == title)
        {
            return &book;
        }
    }
    return nullptr;
}

bool GoodreadsApp::isFriends(const std::string& firstUsername, const std::string& secondUsername) const
{
    const User* firstUser = findUser(firstUsername);
    const User* secondUser = findUser(secondUsername);
    if (!firstUser || !secondUser)
    {
        return false;
    }
    return firstUser->hasFollower(secondUsername) && secondUser->hasFollower(firstUsername);
}

void GoodreadsApp::notifyFollowers(const std::string& authorName, const std::string& publisherName, const std::string& bookTitle)
{
    User* authorUser = findUser(authorName);
    User* publisherUser = findUser(publisherName);
    if (!authorUser || !publisherUser)
    {
        return;
    }
    for (auto& userPtr : users)
    {
        User* user = userPtr.get();
        if (user->getUsername() == authorName || user->getUsername() == publisherName)
        {
            continue;
        }
        bool followsAuthor = authorUser->hasFollower(user->getUsername());
        bool followsPublisher = publisherUser->hasFollower(user->getUsername());
        if (!followsAuthor && !followsPublisher)
        {
            continue;
        }
        std::string notificationMessage;
        if (followsAuthor && followsPublisher)
        {
            notificationMessage =
                "New book published by author " + authorName + " and publisher " + publisherName + ": " + bookTitle;
        }
        else if (followsAuthor)
        {
            notificationMessage = "New book published by author " + authorName + ": " + bookTitle;
        }
        else
        {
            notificationMessage = "New book published by publisher " + publisherName + ": " + bookTitle;
        }
        user->receiveMessage(Message("system", notificationMessage, MessageType::BookNotice));
    }
}

std::vector<std::string> GoodreadsApp::tokenize(const std::string& line) const
{
    std::vector<std::string> tokens;
    std::string currentToken;
    bool insideQuotes = false;
    for (char character : line)
    {
        if (character == '"')
        {
            insideQuotes = !insideQuotes;
            continue;
        }
        if (character == ' ' && !insideQuotes)
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
        else
        {
            currentToken += character;
        }
    }
    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }
    return tokens;
}

std::string GoodreadsApp::joinFrom(const std::vector<std::string>& tokens, int startIndex) const
{
    std::string result;
    for (int index = startIndex; index < static_cast<int>(tokens.size()); ++index)
    {
        if (index > startIndex)
        {
            result += " ";
        }
        result += tokens[index];
    }
    return result;
}

bool GoodreadsApp::tryParseInt(const std::string& text, int& parsedNumber) const
{
    parsedNumber = 0;
    if (text.empty())
    {
        return false;
    }
    for (char character : text)
    {
        if (character < '0' || character > '9')
        {
            return false;
        }
        parsedNumber = parsedNumber * 10 + (character - '0');
    }
    return true;
}

std::string GoodreadsApp::cmdHelp() const
{
    std::string result;
    result += "Available Commands\n";
    result += "help\n";
    result += "register <username> <password> <reader|author|publisher>\n";
    result += "login <username> <password>\n";
    result += "logout\n";
    result += "exit\n";
    if (!currentUser)
    {
        return result;
    }
    UserType userType = currentUser->type();
    if (userType == UserType::Reader || userType == UserType::Author)
    {
        result += "\nReader\n";
        result += "search <name>\n";
        result += "follow <username>\n";
        result += "add-book <bookTitle> <status> [rating]\n";
        result += "status: plan-to-read | reading | paused | dropped\n";
        result += "create-shelf <name>\n";
        result += "delete-shelf <name>\n";
        result += "add-to-shelf <bookTitle> <shelfName>\n";
        result += "remove-from-shelf <bookTitle> <shelfName>\n";
        result += "delete-book <bookTitle>\n";
        result += "show-shelf [reader] <shelfName>\n";
        result += "show-inbox [job-offers|follow-notices]\n";
        result += "read-msg <index>\n";
        result += "delete-msg <index>\n";
        result += "friends [reader]\n";
        result += "add-birthday [date]\n";
        result += "profile [reader]\n";
    }
    if (userType == UserType::Author)
    {
        result += "\nAuthor\n";
        result += "accept-offer <index>\n";
        result += "leave <publisher>\n";
        result += "followers\n";
    }
    if (userType == UserType::Publisher)
    {
        result += "Publisher\n";
        result += "publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres...>\n";
        result += "add-summary <bookTitle> <summary>\n";
        result += "offer <authorName>\n";
        result += "followers\n";
    }
    return result;
}

std::string GoodreadsApp::cmdRegister(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 4)
    {
        return "register <username> <password> <reader|author|publisher>";
    }
    const std::string& username = tokens[1];
    const std::string& password = tokens[2];
    const std::string& typeStr = tokens[3];
    if (findUser(username))
    {
        return "Username already taken.";
    }
    try
    {
        Date today(26, 5, 2026);
        std::unique_ptr<User> newUser;
        if (typeStr == "reader")
        {
            newUser = std::make_unique<Reader>(username, password, today);
        }
        else if (typeStr == "author")
        {
            newUser = std::make_unique<Author>(username, password, today);
        }
        else if (typeStr == "publisher")
        {
            newUser = std::make_unique<Publisher>(username, password, today);
        }
        else
        {
            return "Unknown type. Use: reader, author, publisher";
        }
        users.push_back(std::move(newUser));
        return "Registered successfully as " + typeStr + ": " + username;
    }
    catch (const std::exception& exception)
    {
        return std::string("Registration failed: ") + exception.what();
    }
}

std::string GoodreadsApp::cmdLogin(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3)
    {
        return "login <username> <password>";
    }
    if (currentUser)
    {
        return "Already logged in as " + currentUser->getUsername() +". Logout first.";
    }
    User* foundUser = findUser(tokens[1]);
    if (!foundUser || !foundUser->checkPassword(tokens[2]))
    {
        return "Invalid username or password.";
    }
    currentUser = foundUser;
    return "Welcome, " + currentUser->getUsername() + "! (" + User::userTypeString(currentUser->type()) + ")";
}

std::string GoodreadsApp::cmdLogout()
{
    if (!currentUser)
    {
        return "Not logged in.";
    }
    std::string name = currentUser->getUsername();
    currentUser = nullptr;
    return "Goodbye, " + name + "!";
}

std::string GoodreadsApp::cmdSearch(const std::vector<std::string>& tokens) const
{
    if (tokens.size() < 2)
    {
        return "search <name>";
    }
    const std::string& searchQuery = tokens[1];
    std::string result = "\nUsers:\n";
    bool hasUsers = false;
    for (const auto& userPtr : users)
    {
        const User* user = userPtr.get();
        if (Search::matches(searchQuery, user->getUsername()))
        {
            result += user->getUsername() + " (" + User::userTypeString(user->type()) + ")\n";
            hasUsers = true;
        }
    }
    if (!hasUsers)
    {
        result += "(none)\n";
    }
    result += "\nBooks:\n";
    bool hasBooks = false;
    for (const auto& book : books)
    {
        if (Search::matches(searchQuery, book.getTitle()))
        {
            result += book.getTitle() + " (" + FileManager::intToString(book.getAverageRating()) + ")\n";
            hasBooks = true;
        }
    }
    if (!hasBooks)
    {
        result += "(none)\n";
    }

    return result;
}

std::string GoodreadsApp::cmdFollow(const std::vector<std::string>& tokens)
{
    if (!currentUser)
    {
        return "Not logged in.";
    }
    if (tokens.size() < 2)
    {
        return "follow <username>";
    }
    const std::string& targetName = tokens[1];
    if (targetName == currentUser->getUsername())
    {
        return "You cannot follow yourself.";
    }
    User* target = findUser(targetName);
    if (!target)
    {
        return "User not found: " + targetName;
    }
    if (target->hasFollower(currentUser->getUsername()))
    {
        return "You already follow " + targetName + ".";
    }
    target->addFollower(currentUser->getUsername());
    std::string message = currentUser->getUsername() + " started following you.";
    target->receiveMessage(Message(currentUser->getUsername(), message, MessageType::FollowNotice));
    return "You are now following " + targetName + ".";
}

