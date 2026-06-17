#include "Search.h"
#include <vector>
#include <algorithm>

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
    int diffs = 0;
    for (size_t i = 0; i < firstString.size(); ++i)
    {
        if (firstString[i] != secondString[i])
        {
            ++diffs;
        }
    }
    return diffs;
}

int Search::bestDistance(const std::string& query, const std::string& target)
{
    if (query.size() > target.size())
    {
        return static_cast<int>(query.size());
    }

    int minDistance = static_cast<int>(query.size());
    size_t windowSize = query.size();

    for (size_t i = 0; i <= target.size() - windowSize; ++i)
    {
        std::string window = target.substr(i, windowSize);
        int currentDistance = countDifferences(query, window);

        if (currentDistance < minDistance)
        {
            minDistance = currentDistance;
        }
    }
    return minDistance;
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
    if (smallQuery.size() < 5 || smallQuery.size() > smallTarget.size())
    {
        return false;
    }
    int maxErrors;
    if (smallQuery.size() >= 8)
    {
        maxErrors = 2;
    }
    else
    {
        maxErrors = 1;
    }
    return bestDistance(smallQuery, smallTarget) <= maxErrors;
}
