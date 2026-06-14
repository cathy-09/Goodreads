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

    int getDay() const;
    int getMonth() const;
    int getYear() const; 

    bool operator==(const Date& otherDate) const;
    bool operator!=(const Date& otherDate) const;
};