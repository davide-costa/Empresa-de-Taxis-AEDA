/**
*
* @file
* @brief Contains class declaration necessary to represent a timestamp (date and time) of the calendar
*
*/


#pragma once

#include "Date.h"

/**
*
* @brief Represents a timestamp of the calendar: day, month, year, hours, minutes and seconds.
*
*/


class TimeStamp : public Date
{
	/**
	*
	* @brief A first TimeStamp object is equal to the second if they represent the exact same time
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is equal to the second or not.
	*
	*/
	friend bool operator==(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief A first TimeStamp object is different than the second if they represent different times
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is different than the second or not.
	*
	*/
	friend bool operator!=(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief A first TimeStamp object is lower than the second if the day, month, year, hours, minutes and seconds of the first respect to a previous time than the second
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief A first TimeStamp object is higher than the second if the day, month, year, hours, minutes and seconds of the first respect to a previous time than the second
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is higher than the second or not.
	*
	*/
	friend bool operator>(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief A first TimeStamp object is less than or equal to the second if the day, month, year, hours, minutes and seconds of the first respect to a previous or same date and time as the second
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is less than or equal to the second or not.
	*
	*/
	friend bool operator<=(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief A first TimeStamp object is higher than or equal to the second if the day, month, year, hours, minutes and seconds of the first respect to a later or same date and time as the second
	* @param time1 The first TimeStamp object to be compared.
	* @param time2 The second TimeStamp object to be compared.
	* @return a bool value indicating whether the first is higher than or equal to the second or not.
	*
	*/
	friend bool operator>=(const TimeStamp &time1, const TimeStamp &time2);
	/**
	*
	* @brief Adds the seconds it recieves as argument to time1 TimeStamp. And returns the result in TimeStamp format.
	* @param time1 The TimeStamp to which the seconds will be added.
	* @param seconds The amount of seconds to be added to time1 TimeStamp.
	* @return A TimeStamp with the result of the adition of seconds to time1 TimeStamp.
	*
	*/
	friend TimeStamp operator+(const TimeStamp &time1, time_t seconds);
	/**
	*
	* @brief Adds the seconds it recieves as argument to time1 TimeStamp.  And returns the result in TimeStamp format. (Same as the above operator, but with the arguments in the reverse order).
	* @param time1 The TimeStamp to which the seconds will be added.
	* @param seconds The amount of seconds to be added to time1 TimeStamp.
	* @return A TimeStamp with the result of the adition of seconds to time1 TimeStamp.
	*
	*/
	friend TimeStamp operator+(time_t seconds, const TimeStamp &time1);

	/**
	*
	* @brief Outputs a TimeStamp to an ostream.
	* @param os The ostream to output to.
	* @param time The TimeStamp to output to the ostream.
	* @return the ostream after outputing the TimeStamp.
	*
	*/
	friend ostream &operator<<(ostream &os, const TimeStamp &time);
	/**
	*
	* @brief Extracts a TimeStamp from an istream
	* @param is The istream to input from.
	* @param time The TimeStamp to input from the istream.
	* @return the istream after inputting the TimeStamp.
	*
	*/
	friend istream &operator>>(istream &is, TimeStamp &time);
protected:
	/**
	*
	* @brief Represents the hour of the day.
	*
	*/
	unsigned int hours;
	/**
	*
	* @brief Represents the minutes.
	*
	*/
	unsigned int minutes;
	/**
	*
	* @brief Represents the seconds.
	*
	*/
	unsigned int seconds;
public:
	/**
	*
	* @brief Exception thrown when extracting a TimeStamp from a stream fails (using the overloaded operator>>).
	*
	*/
	class ErrorReadingTimeStampFromStream {};
	/**
	*
	* @brief Exception thrown when an invalid TimeStamp is read from a stream (using the overloaded operator>>).
	*
	*/
	class InvalidTimeStamp {};
	/**
	*
	* @brief Creates a new TimeStamp object based either on information loaded from the file or read from the user. Recieves all the attributes of a TimeStamp object.
	*
	*/
	TimeStamp(unsigned int day, unsigned int month, unsigned int year, unsigned int hours, unsigned int minutes, unsigned int seconds);
	/**
	*
	* @brief Copy constructor that creates a new TimeStamp objectbased on a tm time struct to a TimeStamp object performing the necessary conversions.
	*
	*/
	TimeStamp(const tm &tm_time);
	/**
	*
	* @brief Default constructor.
	*
	*/
	TimeStamp();
	unsigned int GetHours() const;
	unsigned int GetMinutes() const;
	unsigned int GetSeconds() const;
	void SetHours(int hours);
	void SetMinutes(int minutes);
	void SetSeconds(int seconds);
	/**
	*
	* @brief Returns the equivalent tm struct of the TimeStamp object (performs the necessary conversions).
	* @return The equivalent tm struct of the TimeStamp object.
	*
	*/
	tm GetTm() const;
	/**
	*
	* @brief Assignment operator that assigns a tm time struct to a TimeStamp object performing the necessary conversions.
	* @param The tm time struct to be assigned to the TimeStamp object.
	* @return The TimeStamp object after the assignment took place. (The this pointer dereferenced).
	*
	*/
	TimeStamp &operator=(const tm &tm_time);
};
