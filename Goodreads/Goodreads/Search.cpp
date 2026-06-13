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

std::string Search::substring(const std::string& text, size_t start, size_t length)
{
    std::string result;

    for (size_t i = start; i < start + length && i < text.size(); i++)
    {
        result += text[i];
    }

    return result;
}

bool Search::matches(const std::string& query, const std::string& target)
{
    if (query.empty())
    {
        return true;
    }
    std::string smallQuery = toLowerCase(query);
    std::string smallTarget = toLowerCase(target);
    if (smallTarget.find(smallQuery) < smallTarget.size())
    {
        return true;
    }
    if (smallQuery.size() > smallTarget.size())
    {
        return false;
    }
    for (size_t i = 0; i <= smallTarget.size() - smallQuery.size(); ++i)
    {
        std::string targetSubstring = substring(smallTarget, i, smallQuery.size());
        if (countDifferences(smallQuery, targetSubstring) <= 2)
        {
            return true;
        }
    }
    return false;
}
