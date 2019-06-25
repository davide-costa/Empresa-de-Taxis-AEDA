#include "Date.h"
#include "utils.h"

//------------------------------------------------------------------------------
Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}
//------------------------------------------------------------------------------
Date::Date()
{

}
//------------------------------------------------------------------------------
int Date::GetDay() const
{
	return day;
}
//------------------------------------------------------------------------------
int Date::GetMonth() const
{
	return month;
}
//------------------------------------------------------------------------------
int Date::GetYear() const
{
	return year;
}
//------------------------------------------------------------------------------
void Date::SetDay(int day)
{
	this->day = day;
}
//------------------------------------------------------------------------------
void Date::SetMonth(int month)
{
	this->month = month;
}
//------------------------------------------------------------------------------
void Date::SetYear(int year)
{
	this->year = year;
}

//---------------------------------------Operator Overloads---------------------------------------
//------------------------------------------------------------------------------
bool operator==(const Date &date1, const Date &date2)
{
	if (date1.GetDay() != date2.GetDay())
		return false;

	if (date1.GetMonth() != date2.GetMonth())
		return false;

	if (date1.GetYear() != date2.GetYear())
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool operator!=(const Date & date1, const Date & date2)
{
	return !(date1 == date2);
}
//------------------------------------------------------------------------------
bool operator<(const Date &date1, const Date &date2)
{
	if (date1.GetYear() < date2.GetYear())
		return true;

	if (date1.GetYear() > date2.GetYear())
		return false;

	if (date1.GetMonth() < date2.GetMonth())
		return true;

	if (date1.GetMonth() > date2.GetMonth())
		return false;

	if (date1.GetDay() < date2.GetDay())
		return true;

	return false;
}
//------------------------------------------------------------------------------
bool operator>(const Date &date1, const Date &date2)
{
	return date2 < date1;
}
//------------------------------------------------------------------------------
bool operator<=(const Date &date1, const Date &date2)
{
	return !(date1 > date2);
}
//------------------------------------------------------------------------------
bool operator>=(const Date &date1, const Date &date2)
{
	return !(date1 < date2);
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Date &date)
{
	//In order for the setw to work properly, an entire string must be sent (all at once) to the ostream
	ostringstream date_oss;
	date_oss << MakeNeatDate(date.day) << "/" << MakeNeatDate(date.month) << "/" << MakeNeatDate(date.year);
	string date_str = date_oss.str();
	os << date_str;
	return os;
}
//------------------------------------------------------------------------------
istream &operator>>(istream &is, Date &date)
{
	//Declaring all the integers that will be extracted from the date string; they all are initialized as -1 for future error checking
	date.day = -1;
	date.month = -1;
	date.year = -1;

	char ch;
	is >> date.day >> ch;
	is >> date.month >> ch;
	is >> date.year;

	if (is.fail())
		throw Date::ErrorReadingDateFromStream();

	if (!IsDateValid(date))
		throw Date::InvalidDate();
	return is;
}