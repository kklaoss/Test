#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
	int day, month, year;

public:
	Date(int d, int m, int y);
	bool isValid() const;
	std::string toString() const;

	// Операторы сравнения
	bool operator==(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>=(const Date& other) const;  // Добавлено
	bool operator<=(const Date& other) const;  // Добавлено
};

#endif