#include "Date.h"
#include "GoodreadsException.h"
#include "DateException.h"
#include <string>
#include <stdexcept>

Date::Date(int day, int month, int year) :day(day), month(month), year(year)
{
    validate();
}

Date Date::parserForDates(const std::string& string)
{
    if (string.size() != 10 || string[2] != '.' || string[5] != '.')
    {
        throw DateException("Date format: DD.MM.YYYY");
    }
    int days = (string[0] - '0') * 10 + (string[1] - '0');
    int months = (string[3] - '0') * 10 + (string[4] - '0');
    int years = (string[6] - '0') * 1000 + (string[7] - '0') * 100 + (string[8] - '0') * 10 + (string[9] - '0');
    return Date(days, months, years);
}

int Date::daysInMonth(int month, int year)
{
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        return 29;
    }
    return days[month - 1];
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
        throw DateException("Invalid month");
    }
    if (year < 1 || year > 2026)
    {
        throw DateException("Invalid year");
    }
    if (day < 1 || day > daysInMonth(month, year))
    {
        throw DateException("Invalid date for that month");
    }
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

bool Date::operator==(const Date& otherDate) const
{
    return day == otherDate.day && month == otherDate.month && year == otherDate.year;
}

bool Date::operator!=(const Date& otherDate) const
{
    return  !(*this == otherDate);
}