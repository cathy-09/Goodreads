#include "FileManager.h"
#include <iostream>
#include <fstream>
#include "Author.h"
#include "Publisher.h"

void FileManager::save(const std::string& filename, const std::vector<std::unique_ptr<User>>& users, const std::vector<Book>& books)
{
	std::ofstream file(filename);
	if (!file)
	{
		throw std::runtime_error("Cannot open file for writing: " + filename);
	}
	writeLine(file, intToString(users.size()));
	for (const auto& userSave : users)
	{
		const User* user = userSave.get();
		writeLine(file, User::userTypeString(user->type()));
		writeLine(file, user->getUsername());
		writeLine(file, user->getPassword());
		writeLine(file, user->getRegistrationDate().toDateString());
		writeLine(file, encodeList(user->getFollowers()));
		saveInbox(file, user->getInbox());
		if (user->type() == UserType::Reader || user->type() == UserType::Author)
		{
			saveReader(file, static_cast<const Reader*>(user));
		}
		if (user->type() == UserType::Author)
		{
			const Author* author = static_cast<const Author*>(user);
			writeLine(file, encodeList(author->getPublishedBooks()));
			writeLine(file, encodeList(author->getPublishers()));
		}
		if (user->type() == UserType::Publisher)
		{
			const Publisher* publisher = static_cast<const Publisher*>(user);
			writeLine(file, encodeList(publisher->getAuthors()));
			writeLine(file, encodeList(publisher->getPublishedBooks()));
		}
	}
	writeLine(file, intToString(books.size()));
	for (const auto& book : books)
	{
		writeLine(file, book.getTitle());
		writeLine(file, book.getAuthor());
		writeLine(file, book.getPublisher());
		writeLine(file, book.getSummary());
		writeLine(file, encodeList(book.getGenres()));
		writeLine(file, doubleToString(book.getAverageRating()));
		writeLine(file, intToString(book.getRatingCount()));
		writeLine(file, book.getReleaseDate().toDateString());
		writeLine(file, intToString(book.getPageCount()));
	}
}

void FileManager::load(const std::string& filename, std::vector<std::unique_ptr<User>>& users, std::vector<Book>& books)
{
	std::ifstream inputFile(filename);
	if (!inputFile)
	{
		return;
	}
	int totalUsers = parseIntString(readLine(inputFile));
	for (int i = 0; i < totalUsers; ++i)
	{
		std::string userTypeString = readLine(inputFile);
		std::string username = readLine(inputFile);
		std::string password = readLine(inputFile);
		std::string registrationDateString = readLine(inputFile);
		std::string followersListString = readLine(inputFile);
		Date registrationDate;
		if (!registrationDateString.empty())
		{
			registrationDate = Date::parserForDates(registrationDateString);
		}
		std::unique_ptr<User> user;

		if (userTypeString == "Reader")
		{
			user = std::make_unique<Reader>();
		}
		else if (userTypeString == "Author")
		{
			user = std::make_unique<Author>();
		}
		else
		{
			user = std::make_unique<Publisher>();
		}
		user->setUsername(username);
		user->setPassword(password);
		user->setRegistrationDate(registrationDate);
		for (const auto& followerName : splitByDelimiterList(followersListString))
		{
			user->addFollower(followerName);
		}
		loadInbox(inputFile, user.get());
		if (userTypeString == "Reader" || userTypeString == "Author")
		{
			loadReader(inputFile, static_cast<Reader*>(user.get()));
		}
		if (userTypeString == "Author")
		{
			auto* author = static_cast<Author*>(user.get());
			for (const auto& publishedBookTitle : splitByDelimiterList(readLine(inputFile)))
			{
				author->addPublishedBook(publishedBookTitle);
			}
			for (const auto& publisherName : splitByDelimiterList(readLine(inputFile)))
			{
				author->addPublisher(publisherName);
			}
		}
		if (userTypeString == "Publisher")
		{
			auto* publisher = static_cast<Publisher*>(user.get());
			for (const auto& authorName : splitByDelimiterList(readLine(inputFile)))
			{
				publisher->addAuthor(authorName);
			}
			for (const auto& publishedBookTitle : splitByDelimiterList(readLine(inputFile)))
			{
				publisher->addPublishedBook(publishedBookTitle);
			}
		}
		users.push_back(std::move(user));
	}
	int totalBooks = parseIntString(readLine(inputFile));
	for (int i = 0; i < totalBooks; ++i)
	{
		std::string bookTitle = readLine(inputFile);
		std::string bookAuthor = readLine(inputFile);
		std::string bookPublisher = readLine(inputFile);
		std::string bookSummary = readLine(inputFile);
		auto bookGenres = splitByDelimiterList(readLine(inputFile));
		double averageRating = parseDouble(readLine(inputFile));
		int ratingsCount = parseIntString(readLine(inputFile));
		std::string releaseDateString = readLine(inputFile);
		int pageCount = parseIntString(readLine(inputFile));
		Date releaseDate;
		if (!releaseDateString.empty())
		{
			releaseDate = Date::parserForDates(releaseDateString);
		}
		Book book(bookTitle, bookAuthor, bookPublisher, releaseDate, pageCount, bookGenres);
		book.setSummary(bookSummary);
		book.setAverageRating(averageRating);
		book.setRatingCount(ratingsCount);
		books.push_back(book);
	}
}

std::string FileManager::intToString(int value)
{
	if (value == 0)
	{
		return "0";
	}
	bool negative = value < 0;
	if (negative)
	{
		value = -value;
	}
	std::string result;
	while (value > 0)
	{
		char digit = char('0' + (value % 10));
		result.insert(result.begin(), digit);
		value /= 10;
	}
	if (negative)
	{
		result.insert(result.begin(), '-');
	}
	return result;
}

std::string FileManager::doubleToString(double value, int precision)
{
	std::string result;
	if (value < 0)
	{
		result += '-';
		value = -value;
	}
	int intPart = (int)value;
	result += FileManager::intToString(intPart);
	result += '.';
	double frac = value - intPart;
	for (int i = 0; i < precision; ++i)
	{
		frac *= 10;
		int digit = (int)frac;
		result += char('0' + digit);
		frac -= digit;
	}
	return result;
}

void FileManager::writeLine(std::ofstream& outFile, const std::string& line)
{
	outFile << line << '\n';
}

std::string FileManager::readLine(std::ifstream& inFile)
{
	std::string string;
	std::getline(inFile, string);
	if (!string.empty() && string.back() == '\r')
	{
		string.pop_back();
	}
	return string;
}

std::string FileManager::encodeList(const std::vector<std::string>& items)
{
	std::string result;
	for (const auto& item : items)
	{
		if (!result.empty())
		{
			result += "|";
		}
		result += item;
	}
	return result;
}

std::vector<std::string> FileManager::splitByDelimiterList(const std::string& encodedList)
{
	std::vector<std::string> result;
	std::string token;
	for (char charche : encodedList)
	{
		if (charche == '|')
		{
			result.push_back(token);
			token.clear();
			continue;
		}
		token += charche;
	}
	result.push_back(token);
	return result;
}

void FileManager::saveMessage(std::ofstream& outFile, const Message& message)
{
	writeLine(outFile, message.getFrom());
	writeLine(outFile, message.getContent());
	writeLine(outFile, Message::typeToString(message.getType()));

	if (message.isRead())
	{
		writeLine(outFile, "1");
	}
	else
	{
		writeLine(outFile, "0");
	}
}

void FileManager::saveInbox(std::ofstream& outFile, const std::vector<Message>& inboxMessages)
{
	writeLine(outFile, intToString(inboxMessages.size()));
	for (const auto& message : inboxMessages)
	{
		saveMessage(outFile, message);
	}
}

void FileManager::saveShelf(std::ofstream& outFile, const Shelf& shelf)
{
	writeLine(outFile, shelf.getName());
	writeLine(outFile, shelf.getCreatedAt().toDateString());
	writeLine(outFile, encodeList(shelf.getBooks()));
}

void FileManager::saveReader(std::ofstream& outFile, const Reader* reader)
{
	auto books = reader->getBooks();
	writeLine(outFile, intToString(books.size()));
	for (const auto& book : books)
	{
		writeLine(outFile, book.getBookTitle());
		writeLine(outFile, BookEntry::statusToString(book.getStatus()));
		writeLine(outFile, intToString(book.getRating()));
	}
	auto shelves = reader->getShelves();
	writeLine(outFile, intToString(shelves.size()));
	for (const auto& shelf : shelves)
	{
		saveShelf(outFile, shelf);
	}
	writeLine(outFile, encodeList(reader->getFavorites()));
	if (reader->getBirthday())
	{
		writeLine(outFile, reader->getBirthday()->toDateString());
	}
	else
	{
		writeLine(outFile, "");
	}
}

Message FileManager::loadMessage(std::ifstream& inFile)
{
	std::string from = readLine(inFile);
	std::string content = readLine(inFile);
	std::string typeStr = readLine(inFile);
	std::string readString = readLine(inFile);

	MessageType type = Message::typeFromString(typeStr);
	Message message(from, content, type);

	if (readString == "1")
	{
		message.markRead();
	}
	return message;
}

void FileManager::loadInbox(std::ifstream& inFile, User* user)
{
	int n = parseIntString(readLine(inFile));
	for (int i = 0; i < n; ++i)
	{
		user->receiveMessage(loadMessage(inFile));
	}
}

void FileManager::loadReader(std::ifstream& inFile, Reader* reader)
{
	int bookCount = parseIntString(readLine(inFile));
	for (int i = 0; i < bookCount; ++i)
	{
		std::string title = readLine(inFile);
		std::string status = readLine(inFile);
		int rating = parseIntString(readLine(inFile));
		reader->addBook(BookEntry(title, BookEntry::parseStatus(status), rating));
	}
	int shelfCount = parseIntString(readLine(inFile));
	for (int i = 0; i < shelfCount; ++i)
	{
		std::string shelfName = readLine(inFile);
		std::string shelfDate = readLine(inFile);
		std::string shelfBooksString = readLine(inFile);
		Date date;
		if (!shelfDate.empty())
		{
			date = Date::parserForDates(shelfDate);
		}
		Shelf shelf(shelfName, date);
		for (const auto& bookTitle : splitByDelimiterList(shelfBooksString))
		{
			shelf.addBook(bookTitle);
		}
		reader->createShelf(shelf);
	}
	for (const auto& favorite : splitByDelimiterList(readLine(inFile)))
	{
		reader->addFavorite(favorite);
	}
	std::string birthdayString = readLine(inFile);
	if (!birthdayString.empty())
	{
		reader->setBirthday(Date::parserForDates(birthdayString));
	}
}

double FileManager::parseDouble(const std::string& text)
{
	double integerPart = 0.0;
	double fractionalPart = 0.0;
	bool isAfterDecimalPoint = false;
	double fractionalMultiplier = 0.1;
	bool isNegative = false;
	size_t index = 0;
	if (!text.empty() && text[0] == '-')
	{
		isNegative = true;
		index = 1;
	}
	for (; index < text.size(); ++index)
	{
		if (text[index] == '.')
		{
			isAfterDecimalPoint = true;
			continue;
		}
		if (text[index] < '0' || text[index] > '9')
		{
			break;
		}
		if (!isAfterDecimalPoint)
		{
			integerPart = integerPart * 10 + (text[index] - '0');
		}
		else
		{
			fractionalPart += (text[index] - '0') * fractionalMultiplier;
			fractionalMultiplier *= 0.1;
		}
	}
	double result = integerPart + fractionalPart;
	if (isNegative)
	{
		return -result;
	}
	return result;
}

int FileManager::parseIntString(const std::string& text)
{
	int result = 0;
	for (char charche : text)
	{
		if (charche < '0' || charche > '9')
		{
			break;
		}
		result = result * 10 + (charche - '0');
	}
	return result;
}
