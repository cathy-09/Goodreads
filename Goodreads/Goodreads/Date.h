#pragma once
#include <string>
#include <stdexcept>

class Date
{
private:
	int day = 0;
	int month = 0;
	int year = 0;
public:
	Date() = default;
	Date(int day, int month, int year);
	static Date parserForDates(const std::string& string);
    static int daysInMonth(int month, int year);
	std::string toDateString() const;
    bool empty() const;
    void validate() const;
};

inline Date parserForDates(const std::string& string)
{
    if (string.size() != 10 || string[2] != '.' || string[5] != '.')
    {
        throw std::invalid_argument("Date format: DD.MM.YYYY");
    }
    int days = (string[0] - '0') * 10 + (string[1] - '0');
    int months = (string[3] - '0') * 10 + (string[4] - '0');
    int years = (string[6] - '0') * 1000 + (string[7] - '0') * 100 + (string[8] - '0') * 10 + (string[9] - '0');
    return Date(days, months, years);
}

inline int daysInMonth(int month, int year)
{
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        return 29;
    }
    return days[month - 1];
}