#pragma once
#include "User.h"
#include "BookEntry.h"
#include "Shelf.h"
#include <optional>
#include "Message.h"

class Reader : public User
{
private:
	std::vector<BookEntry> books;
	std::vector<Shelf> shelves;
	std::vector<std::string> favorites;
	std::optional<Date> birthday;
	std::vector<Message> inbox;

public:
	Reader() = default;
	Reader(const std::string& username, const std::string& password, const Date& registrationDate);
	UserType type() const override;

	void receiveMessage(const Message& message);
	const std::vector<Message>& getInbox() const;
	std::vector<Message>& getInbox();

	BookEntry* findBook(const std::string& title);
	const BookEntry* findBook(const std::string& title) const;
	void addBook(const BookEntry& book);
	void deleteBook(const std::string& title);
	bool hasBook(const std::string& title) const;
	bool hasFavorite(const std::string& title) const;

	Shelf* findShelf(const std::string& name);
	const Shelf* findShelf(const std::string& name) const;
	bool shelfExists(const std::string& name) const;
	void removeBookFromAllShelves(const std::string& title);
	void createShelf(const Shelf& shelf);
	void deleteShelf(const std::string& name);

	bool isFavorite(const std::string& title) const;
	void addFavorite(const std::string& title);
	void removeFavorite(const std::string& title);

	const std::vector<BookEntry>& getBooks() const;
	std::vector<BookEntry>& getBooks();
	const std::vector<Shelf>& getShelves() const;
	std::vector<Shelf>& getShelves();
	const std::vector<std::string>& getFavorites() const;
	const std::optional<Date>& getBirthday() const;

	void setBirthday(const Date& birthday);
	void clearBirthday();
};

