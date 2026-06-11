#include "Search.h"

std::string Search::toLowerCase(const std::string& text)
{
    std::string result;
    for (char character : text)
    {
        if (character >= 'A' && character <= 'Z')
        {
            character = character - 'A' + 'a';
        }
        result += character;
    }
    return result;
}

int Search::countDifferences(const std::string& firstString, const std::string& secondString)
{
    int differences = 0;
    for (size_t i = 0; i < firstString.size(); ++i)
    {
        if (firstString[i] != secondString[i])
        {
            ++differences;
        }
    }
    return differences;
}


bool Search::matches(const std::string& query, const std::string& target)
{
    if (query.empty())
    {
        return true;
    }
    std::string smallQuery = toLowerCase(query);
    std::string smallTarget = toLowerCase(target);
    size_t position = smallTarget.find(smallQuery);
    return position != static_cast<size_t>(-1);
}
