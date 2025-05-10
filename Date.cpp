#include "Date.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
}

bool Date::isValid() const
{
	return (day >= 1 && day <= 31) && (month >= 1 && month <= 12) && (year > 0);
}

std::string Date::toString() const
{
	return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

// Реализация операторов сравнения (упрощенно)
bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

bool Date::operator<(const Date& other) const
{
	if (year != other.year) return year < other.year;
	if (month != other.month) return month < other.month;
	return day < other.day;
}
bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}

bool Date::operator<=(const Date& other) const
{
	return (*this < other) || (*this == other);
}