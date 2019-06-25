/**
*
* @file
* @brief Contains class declaration necessary to represent a date of the calendar
*
*/


# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>


using namespace std;


/**
*
* @brief Represents a date of the calendar: day, month and year.
*
*/
class Date
{
	/**
	*
	* @brief Compares two Date objects. A first Date object is equal to the second if they represent the exact same day in the calendar
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is equal to the second or not.
	*
	*/
	friend bool operator==(const Date &date1, const Date &date2);
	/**
	*
	* @brief Compares two Date objects. A first Date object is different than the second if they represent different days in the calendar
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is different than the second or not.
	*
	*/
	friend bool operator!=(const Date &date1, const Date &date2);
	/**
	*
	* @brief Compares two Date objects. A first Date object is less than the second if the day, month and year of the first respect to a previous date than the second
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const Date &date1, const Date &date2);
	/**
	*
	* @brief Compares two Date objects. A first Date object is higher than the second if the day, month and year of the first respect to a later date than the second
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is higher than the second or not.
	*
	*/
	friend bool operator>(const Date &date1, const Date &date2);
	/**
	*
	* @brief Compares two Date objects. A first Date object is less than or equal to the second if the day, month and year of the first respect to a previous or same date as the second
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is less than or equal to the second or not.
	*
	*/
	friend bool operator<=(const Date &date1, const Date &date2);
	/**
	*
	* @brief Compares two Date objects. A first Date object is higher than or equal to the second if the day, month and year of the first respect to a later or same date as the second
	* @param date1 The first Date object to be compared.
	* @param date2 The second Date object to be compared.
	* @return a bool value indicating whether the first is higher than or equal to the second or not.
	*
	*/
	friend bool operator>=(const Date &date1, const Date &date2);
	/**
	*
	* @brief Outputs a Date to an ostream
	* @param os The ostream to output to.
	* @param date The Date to output to the ostream.
	* @return the ostream after outputing the Date.
	*
	*/
	friend ostream &operator<<(ostream &os, const Date &date);
	/**
	*
	* @brief Extracts a Date from an istream
	* @param is The istream to input from.
	* @param date The Date to input from the istream.
	* @return the istream after inputting the Date.
	*
	*/
	friend istream &operator>>(istream &is, Date &date);
protected:
	/**
	*
	* @brief Represents the day of the month.
	*
	*/
	unsigned int day;
	/**
	*
	* @brief Represents the month.
	*
	*/
	unsigned int month;
	/**
	*
	* @brief Represents the year.
	*
	*/
	unsigned int year;
public:
	/**
	*
	* @brief Exception thrown when extracting a date from a stream fails (using the overloaded operator>>).
	*
	*/
	class ErrorReadingDateFromStream {};
	/**
	*
	* @brief Exception thrown when an invalid date is read from a stream (using the overloaded operator>>).
	*
	*/
	class InvalidDate {};
	/**
	*
	* @brief Creates a new Date object. Recieves all attributes of a Date as parameters.
	*
	*/
	Date(unsigned int day, unsigned int month, unsigned int year);
	/**
	*
	* @brief Default constructor.
	*
	*/
	Date();
	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);
};