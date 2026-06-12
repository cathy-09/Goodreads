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

bool GoodreadsApp::validateRating(const std::string& ratingStr, int& rating, std::string& error) const
{
    rating = 0;
    if (!tryParseInt(ratingStr, rating) || rating < 1 || rating > 5)
    {
        error = "Rating must be a number between 1 and 5.";
        return false;
    }
    return true;
}

bool GoodreadsApp::validateBookForReader(const std::string& title, Reader* reader, Book*& book, std::string& error)
{
    book = findBook(title);
    if (!book)
    {
        error = "Book not found: " + title;
        return false;
    }
    if (reader->hasBook(title))
    {
        error = "You already have '" + title + "' in your profile.";
        return false;
    }
    return true;
}

bool GoodreadsApp::validateShelfAccess(const std::string& bookTitle, const std::string& shelfName, Reader* reader, Shelf*& shelf, std::string& error)
{
    if (!reader->hasBook(bookTitle))
    {
        error = "You don't have " + bookTitle + " in ur profile.";
        return false;
    }

    shelf = reader->findShelf(shelfName);

    if (!shelf)
    {
        error = "Shelf " + shelfName + " does not exist.";
        return false;
    }

    return true;
}

bool GoodreadsApp::validateShelfExists(const std::string& shelfName, Reader* reader, Shelf*& shelf, std::string& error)
{
    shelf = reader->findShelf(shelfName);
    if (!shelf)
    {
        error = "Shelf " + shelfName + " does not exist.";
        return false;
    }
    return true;
}

void GoodreadsApp::removeRating(const std::string& title, Reader* reader)
{
    const BookEntry* entry = reader->findBook(title);
    if (!entry || entry->getRating() == 0)
    {
        return;
    }
    Book* book = findBook(title);
    if (!book)
    {
        return;
    }
    if (book->getRatingCount() > 1)
    {
        book->updateRating(entry->getRating(), 0);
        book->setRatingCount(book->getRatingCount() - 1);
    }
    else
    {
        book->setAverageRating(0.0);
        book->setRatingCount(0);
    }
}

const Reader* GoodreadsApp::resolveTargetReader(const std::string& readerName, std::string& error) const
{
    if (!isFriends(currentUser->getUsername(), readerName))
    {
        error = "Access denied. You must be friends with " + readerName + " to view their shelves.";
        return nullptr;
    }
    return resolveReader(readerName, error);
}

std::string GoodreadsApp::formatShelf(const Shelf* shelf) const
{
    std::string result = "Shelf: " + shelf->getName() + " (" + FileManager::intToString(shelf->size()) + " books)\n";

    result += "Created: " + shelf->getCreatedAt().toDateString() + "\n";

    if (shelf->getBooks().empty())
    {
        return result + "(empty)\n";
    }

    for (const auto& bookTitle : shelf->getBooks())
    {
        result += " - " + bookTitle;
        const Book* book = findBook(bookTitle);
        if (book)
        {
            result += " (" + FileManager::intToString((int)book->getAverageRating()) + ")";
        }
        result += "\n";
    }
    return result;
}

std::string GoodreadsApp::formatMessage(const Message& message, int index) const
{
    std::string result = "[" + FileManager::intToString(index) + "] ";
    if (message.isRead())
    {
        result += "  ";
    }
    else
    {
        result += "* ";
    }
    result += "From " + message.getFrom();
    if (message.isJobOffer())
    {
        result += " [Job Offer]";
    }
    if (message.isFollowNotice())
    {
        result += " [Follow]";
    }
    if (message.isBookNotice())
    {
        result += " [New Book]";
    }
    result += ": " + message.getContent() + "\n";
    return result;
}

bool GoodreadsApp::messageMatchesFilter(const Message& message, bool jobOffersOnly, bool followsOnly) const
{
    if (jobOffersOnly)
    {
        return message.isJobOffer();
    }
    if (followsOnly)
    {
        return message.isFollowNotice();
    }
    return true;
}

const Reader* GoodreadsApp::resolveReader(const std::string& username, std::string& error) const
{
    const User* user = findUser(username);
    if (!user)
    {
        error = "User not found: " + username;
        return nullptr;
    }
    const Reader* reader = dynamic_cast<const Reader*>(user);
    if (!reader)
    {
        error = username + " is not a reader.";
        return nullptr;
    }
    return reader;
}

std::string GoodreadsApp::formatFriendsList(const Reader* targetReader) const
{
    std::string result = "Friends of " + targetReader->getUsername() + ":\n";
    bool hasFriends = false;

    for (const auto& followerName : targetReader->getFollowers())
    {
        const User* other = findUser(followerName);

        if (!other)
        {
            continue;
        }

        if (other->hasFollower(targetReader->getUsername()))
        {
            result += "  " + followerName + " (" +User::userTypeString(other->type()) + ")\n";
            hasFriends = true;
        }
    }

    if (!hasFriends)
    {
        result += "  (none)\n";
    }

    return result;
}

std::string GoodreadsApp::parseBirthday(const std::string& dateStr, Date& birthday) const
{
    try
    {
        birthday = Date::parserForDates(dateStr);
        return "";
    }
    catch (const std::exception& exception)
    {
        return std::string("Invalid date: ") + exception.what();
    }
}

std::string GoodreadsApp::formatPublisherProfile(const User* user) const
{
    std::string result = " " + user->getUsername() + " (Publisher) \n";
    result += "Registered: " + user->getRegistrationDate().toDateString() + "\n";
    result += "Followers: " + FileManager::intToString((int)user->getFollowers().size()) + "\n";
    return result;
}

std::string GoodreadsApp::formatShelves(const Reader* reader) const
{
    std::string result = "\nShelves (" + FileManager::intToString((int)reader->getShelves().size()) + "):\n";
    for (const auto& shelf : reader->getShelves())
    {
        result += "  " + shelf.getName() + " (" + FileManager::intToString(shelf.size()) + " books)\n";
    }
    return result;
}

std::string GoodreadsApp::formatFavorites(const Reader* reader) const
{
    std::string result = "\nFavorite books (" + FileManager::intToString((int)reader->getFavorites().size()) + "):\n";
    if (reader->getFavorites().empty())
    {
        return result + "  (none)\n";
    }
    for (const auto& fav : reader->getFavorites())
    {
        result += "  " + fav + "\n";
    }
    return result;
}

std::string GoodreadsApp::formatReaderProfile(const Reader* reader) const
{
    std::string result = " " + reader->getUsername();
    result += " (" + User::userTypeString(reader->type()) + ") n";
    result += "Registered: " + reader->getRegistrationDate().toDateString() + "\n";
    if (reader->getBirthday())
    {
        result += "Birthday: " + reader->getBirthday()->toDateString() + "\n";
    }
    result += "Followers: " + FileManager::intToString((int)reader->getFollowers().size()) + "\n";
    result += formatShelves(reader);
    result += formatFavorites(reader);
    return result;
}

std::string GoodreadsApp::formatFollowersList(const std::vector<std::string>& followers) const
{
    if (followers.empty())
    {
        return "  (none)\n";
    }
    std::string result;
    for (const auto& followerName : followers)
    {
        result += "  " + followerName;
        const User* user = findUser(followerName);
        if (user)
        {
            result += " (" + User::userTypeString(user->type()) + ")";
        }
        result += "\n";
    }
    return result;
}

void GoodreadsApp::unlinkAuthorFromPublisher(Author* author, const std::string& publisherName)
{
    author->removePublisher(publisherName);
    Publisher* publisher = dynamic_cast<Publisher*>(findUser(publisherName));
    if (publisher)
    {
        publisher->removeAuthor(author->getUsername());
    }
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

std::string GoodreadsApp::cmdAddBook(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3)
    {
        return "add-book <bookTitle> <status> [rating]";
    }
    Reader* reader = dynamic_cast<Reader*>(currentUser);
    if (!reader)
    {
        return "Only readers and authors can add books.";
    }

    const std::string& title = tokens[1];
    Book* book = nullptr;
    std::string error;

    if (!validateBookForReader(title, reader, book, error))
    {
        return error;
    }

    ReadStatus status;
    try
    {
        status = BookEntry::parseStatus(tokens[2]);
    }
    catch (const std::exception&)
    {
        return "Invalid status. Helps for status: plan-to-read, reading, paused, dropped";
    }

    int rating = 0;
    if (tokens.size() >= 4)
    {
        if (!validateRating(tokens[3], rating, error))
        {
            return error;
        }
    }

    reader->addBook(BookEntry(title, status, rating));
    if (rating > 0)
    {
        book->addRating(rating);
    }
    return "" + title + " added to ur profile.";
}

std::string GoodreadsApp::cmdCreateShelf(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2)
    {
        return "create-shelf <name>";
    }

    Reader* reader = dynamic_cast<Reader*>(currentUser);

    if (!reader)
    {
        return "Only readers and authors can create shelves.";
    }

    const std::string& name = tokens[1];

    if (reader->shelfExists(name))
    {
        return "A shelf named " + name + " already exists.";
    }

    Date today(20, 6, 2026);
    reader->createShelf(Shelf(name, today));
    return "Shelf '" + name + "' created.";
}

std::string GoodreadsApp::cmdDeleteShelf(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2)
    {
        return "delete-shelf <name>";
    }

    Reader* reader = dynamic_cast<Reader*>(currentUser);

    if (!reader)
    {
        return "Only readers and authors can delete shelves.";
    }

    const std::string& name = tokens[1];

    if (!reader->shelfExists(name))
    {
        return "Shelf " + name + " does not exist.";
    }

    reader->deleteShelf(name);
    return "Shelf " + name + " deleted.";
}

std::string GoodreadsApp::cmdAddToShelf(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3)
    {
        return "add-to-shelf <bookTitle> <shelfName>";
    }
    Reader* reader = dynamic_cast<Reader*>(currentUser);
    if (!reader)
    {
        return "Only readers and authors can organize shelves.";
    }

    const std::string& bookTitle = tokens[1];
    const std::string& shelfName = tokens[2];
    Shelf* shelf = nullptr;
    std::string error;

    if (!validateShelfAccess(bookTitle, shelfName, reader, shelf, error))
    {
        return error;
    }
    if (shelf->hasBook(bookTitle))
    {
        return "'" + bookTitle + " is already on shelf " + shelfName + ".";
    }
    shelf->addBook(bookTitle);
    return "'" + bookTitle + " added to shelf " + shelfName + "'.";
}

std::string GoodreadsApp::cmdRemoveFromShelf(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3)
    {
        return " remove-from-shelf <bookTitle> <shelfName>";
    }
    Reader* reader = dynamic_cast<Reader*>(currentUser);
    if (!reader)
    {
        return "Only readers and authors can organize shelves.";
    }

    const std::string& bookTitle = tokens[1];
    const std::string& shelfName = tokens[2];
    Shelf* shelf = nullptr;
    std::string error;

    if (!validateShelfExists(shelfName, reader, shelf, error))
    {
        return error;
    }

    if (!shelf->hasBook(bookTitle))
    {
        return "" + bookTitle + " is not on shelf " + shelfName + ".";
    }
    shelf->removeBook(bookTitle);
    return "" + bookTitle + " removed from shelf " + shelfName + ".";
}

std::string GoodreadsApp::cmdDeleteBook(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2)
    {
        return "delete-book <bookTitle>";
    }

    Reader* reader = dynamic_cast<Reader*>(currentUser);

    if (!reader)
    {
        return "Only readers and authors can delete books from their profile.";
    }

    const std::string& title = tokens[1];

    if (!reader->hasBook(title))
    {
        return "You don't have " + title + " in ur profile.";
    }

    removeRating(title, reader);
    reader->deleteBook(title);
    return "" + title + " removed from your profile.";
}

std::string GoodreadsApp::cmdShowShelf(const std::vector<std::string>& tokens) const
{
    if (tokens.size() < 2)
    {
        return "Usage: show-shelf [readerName] <shelfName>";
    }
    const Reader* targetReader = dynamic_cast<const Reader*>(currentUser);
    if (!targetReader)
    {
        return "Only readers and authors can view shelves.";
    }

    std::string shelfName = tokens[1];
    if (tokens.size() >= 3)
    {
        std::string error;
        targetReader = resolveTargetReader(tokens[1], error);
        if (!targetReader)
        {
            return error;
        }
        shelfName = tokens[2];
    }

    const Shelf* shelf = targetReader->findShelf(shelfName);
    if (!shelf)
    {
        return "Shelf '" + shelfName + "' does not exist.";
    }
    return formatShelf(shelf);
}

std::string GoodreadsApp::cmdShowInbox(const std::vector<std::string>& tokens) const
{
    if (!currentUser)
    {
        return "Not logged in.";
    }

    bool jobOffersOnly = tokens.size() >= 2 && tokens[1] == "job-offers";
    bool followsOnly = tokens.size() >= 2 && tokens[1] == "follow-notices";

    const auto& inbox = currentUser->getInbox();

    if (inbox.empty())
    {
        return "Your inbox is empty.";
    }

    std::string result;
    int index = 1;
    for (const auto& message : inbox)
    {
        if (messageMatchesFilter(message, jobOffersOnly, followsOnly))
        {
            result += formatMessage(message, index);
        }
        ++index;
    }

    if (result.empty())
    {
        return "No messages matching the filter.";
    }
    return result;
}

std::string GoodreadsApp::cmdReadMsg(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2)
    {
        return "read-msg <index>";
    }
    int index = 0;
    if (!tryParseInt(tokens[1], index) || index < 1)
    {
        return "Invalid index.";
    }
    auto& inbox = currentUser->getInbox();
    if (index > (int)inbox.size())
    {
        return "Invalid index.";
    }
    inbox[index - 1].markRead();
    return "Message [" + FileManager::intToString(index) + "] marked as read.";
}

std::string GoodreadsApp::cmdDeleteMsg(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2)
    {
        return "delete-msg <index>";
    }
    int index = 0;
    if (!tryParseInt(tokens[1], index) || index < 1)
    {
        return "Invalid index.";
    }
    auto& inbox = currentUser->getInbox();
    if (index > (int)inbox.size())
    {
        return "Invalid index.";
    }
    if (!inbox[index - 1].isRead())
    {
        return "Cannot delete an unread message. Mark it as read first.";
    }
    inbox.erase(inbox.begin() + (index - 1));
    return "Message deleted.";
}

std::string GoodreadsApp::cmdFriends(const std::vector<std::string>& tokens) const
{
    const Reader* targetReader = dynamic_cast<const Reader*>(currentUser);
    if (!targetReader)
    {
        return "Only readers and authors have friends.";
    }

    if (tokens.size() >= 2)
    {
        std::string error;
        targetReader = resolveReader(tokens[1], error);
        if (!targetReader)
        {
            return error;
        }
    }

    return formatFriendsList(targetReader);
}

std::string GoodreadsApp::cmdAddBirthday(const std::vector<std::string>& tokens)
{
    Reader* reader = dynamic_cast<Reader*>(currentUser);
    if (!reader)
    {
        return "Only readers and authors can set a birthday.";
    }
    if (tokens.size() < 2)
    {
        reader->clearBirthday();
        return "Birthday removed from your profile.";
    }

    Date birthday;
    std::string error = parseBirthday(tokens[1], birthday);
    if (!error.empty())
    {
        return error;
    }
    reader->setBirthday(birthday);
    return "Birthday set to " + birthday.toDateString() + ".";
}

std::string GoodreadsApp::cmdProfile(const std::vector<std::string>& tokens) const
{
    const Reader* targetReader = dynamic_cast<const Reader*>(currentUser);

    if (tokens.size() >= 2)
    {
        std::string error;
        targetReader = resolveReader(tokens[1], error);
        if (!targetReader)
        {
            return error;
        }
    }

    if (!targetReader)
    {
        return formatPublisherProfile(currentUser);
    }
    return formatReaderProfile(targetReader);
}

std::string GoodreadsApp::cmdPublish(const std::vector<std::string>& tokens)
{
    return std::string();
}

std::string GoodreadsApp::cmdAddSynopsis(const std::vector<std::string>& tokens)
{
    return std::string();
}

std::string GoodreadsApp::cmdOffer(const std::vector<std::string>& tokens)
{
    return std::string();
}

std::string GoodreadsApp::cmdAcceptOffer(const std::vector<std::string>& tokens)
{
    return std::string();
}

std::string GoodreadsApp::cmdLeave(const std::vector<std::string>& tokens)
{
    Author* author = dynamic_cast<Author*>(currentUser);
    if (!author)
    {
        return "Only authors can leave a publisher.";
    }
    if (tokens.size() < 2)
    {
        return "leave <publisherName>";
    }

    const std::string& publisherName = tokens[1];
    if (!author->worksWithPublisher(publisherName))
    {
        return "You are not working with publisher " + publisherName + ".";
    }

    unlinkAuthorFromPublisher(author, publisherName);
    return "You left publisher " + publisherName + ".";
}

std::string GoodreadsApp::cmdFollowers()
{
    if (!currentUser)
    {
        return "Not logged in.";
    }
    const auto& followers = currentUser->getFollowers();
    std::string result = "Followers of " + currentUser->getUsername();
    result += " (" + FileManager::intToString((int)followers.size()) + "):\n";
    result += formatFollowersList(followers);
    return result;
}

