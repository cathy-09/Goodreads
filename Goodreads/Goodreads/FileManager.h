#pragma once
#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Book.h"
#include "User.h"
#include "Shelf.h"
#include "Reader.h"
class FileManager
{
private:
    static void writeLine(std::ofstream& outFile, const std::string& line);
    static std::string readLine(std::ifstream& inFile);

    static std::string encodeList(const std::vector<std::string>& items);
    static std::vector<std::string> splitByDelimiterList(const std::string& encodedList);

    static void saveMessage(std::ofstream& outFile, const Message& message);
    static void saveInbox(std::ofstream& outFile, const std::vector<Message>& inboxMessages);
    static void saveShelf(std::ofstream& outFile, const Shelf& shelf);
    static void saveReader(std::ofstream& outFile, const Reader* reader);

    static Message loadMessage(std::ifstream& inFile);
    static void loadInbox(std::ifstream& inFile, User* user);
    static void loadReader(std::ifstream& inFile, Reader* reader);

    static double parseDouble(const std::string& text);
    static int parseIntString(const std::string& text);
public:
    static void save(const std::string& filename, const std::vector<std::unique_ptr<User>>& users, const std::vector<Book>& books);
    static void load(const std::string& filename, std::vector<std::unique_ptr<User>>& users, std::vector<Book>& books);
    static std::string intToString(int value);
    static std::string doubleToString(double value, int precision = 2);
};
