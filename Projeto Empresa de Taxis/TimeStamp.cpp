#include "TimeStamp.h"
#include "utils.h"


//------------------------------------------------------------------------------
TimeStamp::TimeStamp(unsigned int day, unsigned int month, unsigned int year, unsigned int hours, unsigned int minutes, unsigned int seconds) : Date(day, month, year)
{
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}
//------------------------------------------------------------------------------
TimeStamp::TimeStamp(const tm &tm_time)
{
	year = tm_time.tm_year + 1900;
	month = tm_time.tm_mon + 1;
	day = tm_time.tm_mday;
	hours = tm_time.tm_hour;
	minutes = tm_time.tm_min;
	seconds = tm_time.tm_sec;
}
//------------------------------------------------------------------------------
TimeStamp::TimeStamp()
{

}
//------------------------------------------------------------------------------
unsigned int TimeStamp::GetHours() const
{
	return hours;
}
//------------------------------------------------------------------------------
unsigned int TimeStamp::GetMinutes() const
{
	return minutes;
}
//------------------------------------------------------------------------------
unsigned int TimeStamp::GetSeconds() const
{
	return seconds;
}
//------------------------------------------------------------------------------
void TimeStamp::SetHours(int hours)
{
	this->hours = hours;
}
//------------------------------------------------------------------------------
void TimeStamp::SetMinutes(int minutes)
{
	this->minutes = minutes;
}
//------------------------------------------------------------------------------
void TimeStamp::SetSeconds(int seconds)
{
	this->seconds = seconds;
}
//------------------------------------------------------------------------------
tm TimeStamp::GetTm() const
{
	tm tm_time;
	tm_time.tm_year = year - 1900;
	tm_time.tm_mon = month - 1;
	tm_time.tm_mday = day;
	tm_time.tm_hour = hours;
	tm_time.tm_min = minutes;
	tm_time.tm_sec = seconds;

	return tm_time;
}
//---------------------------------------Operator Overloads---------------------------------------
TimeStamp &TimeStamp::operator=(const tm &tm_time)
{
	year = tm_time.tm_year + 1900;
	month = tm_time.tm_mon + 1;
	day = tm_time.tm_mday;
	hours = tm_time.tm_hour;
	minutes = tm_time.tm_min;
	seconds = tm_time.tm_sec;
	return *this;
}
//------------------------------------------------------------------------------
bool operator==(const TimeStamp &time1, const TimeStamp &time2)
{
	if (time1.GetDay() != time2.GetDay())
		return false;

	if (time1.GetMonth() != time2.GetMonth())
		return false;

	if (time1.GetYear() != time2.GetYear())
		return false;

	if (time1.hours != time2.hours)
		return false;

	if (time1.minutes != time2.minutes)
		return false;

	if (time1.seconds != time2.seconds)
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool operator!=(const TimeStamp & time1, const TimeStamp & time2)
{
	return !(time1 == time2);
}
//------------------------------------------------------------------------------
bool operator<(const TimeStamp &time1, const TimeStamp &time2)
{
	if (time1.GetYear() < time2.GetYear())
		return true;

	if (time1.GetYear() > time2.GetYear())
		return false;

	if (time1.GetMonth() < time2.GetMonth())
		return true;

	if (time1.GetMonth() > time2.GetMonth())
		return false;

	if (time1.GetDay() < time2.GetDay())
		return true;

	if (time1.GetDay() > time2.GetDay())
		return false;

	if (time1.hours < time2.hours)
		return true;

	if (time1.hours > time2.hours)
		return false;

	if (time1.minutes < time2.minutes)
		return true;

	if (time1.minutes > time2.minutes)
		return false;

	if (time1.seconds < time2.seconds)
		return true;

	return false;
}
//------------------------------------------------------------------------------
bool operator>(const TimeStamp &time1, const TimeStamp &time2)
{
	return time2 < time1;
}
//------------------------------------------------------------------------------
bool operator<=(const TimeStamp &time1, const TimeStamp &time2)
{
	return !(time1 > time2);
}
//------------------------------------------------------------------------------
bool operator>=(const TimeStamp &time1, const TimeStamp &time2)
{
	return !(time1 < time2);
}
//------------------------------------------------------------------------------
TimeStamp operator+(const TimeStamp &time1, time_t seconds)
{
	tm time1_tm = time1.GetTm();

	time_t time1_secs = mktime(&time1_tm);
	time_t result_secs = time1_secs + seconds;
	tm result_tm;
	localtime_s(&result_tm, &result_secs);
	TimeStamp result = result_tm; //using the overloaded operator to assign a tm time to a TimeStamp object

	return result;
}
//------------------------------------------------------------------------------
TimeStamp operator+(time_t seconds, const TimeStamp &time1)
{
	return time1 + seconds;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const TimeStamp &time)
{
	//In order for the setw to work properly, an entire string must be sent (all at once) to the ostream
	ostringstream time_stamp_oss;
	Date date_from_time_stamp = time; //taking advantage of slicing problem
	time_stamp_oss << date_from_time_stamp << " " << time.hours << ":" << time.minutes << ":" << time.seconds;
	string time_stamp_str = time_stamp_oss.str();
	os << time_stamp_str;
	return os;
}
//------------------------------------------------------------------------------
istream &operator>>(istream &is, TimeStamp &time)
{
	char ch;

	is >> time.day >> ch;
	is >> time.month >> ch;
	is >> time.year;
	is >> time.hours >> ch;
	is >> time.minutes >> ch;
	is >> time.seconds;

	if (is.fail())
		throw TimeStamp::ErrorReadingTimeStampFromStream();

	if (!IsTimeStampValid(time))
		throw TimeStamp::InvalidTimeStamp();

	return is;
}