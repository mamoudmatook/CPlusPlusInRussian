#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <memory>
#include <tuple>
#include <vector>

class Date
{
public:
	Date();
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	std::string DateToStr() const;
private:
	int year;
	int month;
	int day;
};
Date ParseDate(std::istream& is);
std::ostream& operator << (std::ostream& os, const Date& date);
std::ostream& operator << (std::ostream& os, const std::pair<Date, std::string>& pair);

bool operator < (const Date& lsh, const Date& rhs);
bool operator <= (const Date& lsh, const Date& rhs);
bool operator > (const Date& lsh, const Date& rhs);
bool operator >= (const Date& lsh, const Date& rhs);
bool operator == (const Date& lsh, const Date& rhs);
bool operator != (const Date& lsh, const Date& rhs);
