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


bool Search::matches(const std::string& query, const std::string& target)
{
    if (query.empty())
    {
        return true;
    }
    std::string smallQuery = toLowerCase(query);
    std::string smallTarget = toLowerCase(target);
    size_t position = smallTarget.find(smallQuery);
    if (position == -1)
    {
        return false;
    }
    return true;
}
