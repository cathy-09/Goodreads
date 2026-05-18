#include "Date.h"
#include <string>
#include <stdexcept>

Date::Date(int day, int month, int year) :day(day), month(month), year(year)
{
    validate();
}

std::string Date::toDateString() const
{
    std::string resultTemplate = "  .  .    ";
    resultTemplate[0] = (day / 10) + '0';
    resultTemplate[1] = (day % 10) + '0';
    resultTemplate[3] = (month / 10) + '0';
    resultTemplate[4] = (month % 10) + '0';
    resultTemplate[6] = (year / 1000) + '0';
    resultTemplate[7] = ((year / 100) % 10) + '0';
    resultTemplate[8] = ((year / 10) % 10) + '0';
    resultTemplate[9] = (year % 10) + '0';
    return resultTemplate;
}

bool Date::empty() const
{
    return day == 0;
}

void Date::validate() const
{
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument("Invalid month");
    }
    if (year < 1 || year > 2026)
    {
        throw std::invalid_argument("Invalid year");
    }
    if (day < 1 || day > daysInMonth(month, year))
    {
        throw std::invalid_argument("Invalid date for that month");
    }
}