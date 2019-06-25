#include "Service.h"

#include "utils.h"

unsigned int Service::curr_service_id = 0;
float Service::base_price_day = 3.25; //Defined by ANTRAL
float Service::base_price_night = 3.9;//Defined by ANTRAL
float Service::average_speed_city = 30;
float Service::average_speed_off_city = 80;
float Service::price_per_minute = 0.25;
float Service::price_per_km_day = 0.47;
float Service::price_per_km_night = 0.56;
//------------------------------------------------------------------------------
Service::Service(unsigned int id, string start, string finish, unsigned int day_distance, unsigned int night_distance, time_t duration, TimeStamp start_time, TimeStamp finish_time, Taxi* taxi, float pre_price, float final_price, bool paid)
{
	this->id = id;
	this->start = start;
	this->finish = finish;
	this->day_distance = day_distance;
	this->night_distance = night_distance;
	this->duration = duration;
	this->start_time = start_time;
	this->finish_time = finish_time;
	this->taxi = taxi;
	this->pre_price = pre_price;
	this->final_price = final_price;
	this->paid = paid;
}
//------------------------------------------------------------------------------
Service::Service(string start, string finish, unsigned int day_distance, unsigned int night_distance, time_t duration, Taxi* taxi)
{
	id = (++curr_service_id);
	this->start = start;
	this->finish = finish;
	this->day_distance = day_distance;
	this->night_distance = night_distance;
	this->duration = duration;
	GetTimeStampFromWindows(start_time);
	this->finish_time = start_time + duration;
	this->taxi = taxi;
	ComputePrice();
	paid = true;
}
//------------------------------------------------------------------------------
Service::Service(Date date)
{
	TimeStamp time(date.GetDay(), date.GetMonth(), date.GetYear(), 0, 0, 0);
	start_time = time;
}
//------------------------------------------------------------------------------
Service::Service()
{

}
//------------------------------------------------------------------------------
unsigned int Service::GetId() const
{
	return id;
}
//------------------------------------------------------------------------------
string Service::GetStart() const
{
	return start;
}
//------------------------------------------------------------------------------
string Service::GetFinish() const
{
	return finish;
}
//------------------------------------------------------------------------------
unsigned int Service::GetDayDistance() const
{
	return day_distance;
}
//------------------------------------------------------------------------------
unsigned int Service::GetNightDistance() const
{
	return night_distance;
}
//------------------------------------------------------------------------------
unsigned int Service::GetDistance() const
{
	return day_distance + night_distance;
}
//------------------------------------------------------------------------------
unsigned int Service::GetDuration() const
{
	return duration;
}
//------------------------------------------------------------------------------
unsigned int Service::GetCurrServiceId()
{
	return curr_service_id;
}
//------------------------------------------------------------------------------
void Service::SetCurrServiceId(unsigned int curr_service_id)
{
	Service::curr_service_id = curr_service_id;
}
//------------------------------------------------------------------------------
const Date &Service::GetDate() const
{
	return start_time;
}
//------------------------------------------------------------------------------
const Date &Service::GetFinalDate() const
{
	return finish_time;
}
//------------------------------------------------------------------------------
const Taxi *Service::GetTaxi() const
{
	return taxi;
}
//------------------------------------------------------------------------------
float Service::GetPrePrice() const
{
	return pre_price;
}
//------------------------------------------------------------------------------
float Service::GetFinalPrice() const
{
	return final_price;
}
//------------------------------------------------------------------------------
bool Service::IsPaid() const
{
	return paid;
}
//------------------------------------------------------------------------------
void Service::SetFinalPrice(float final_price)
{
	this->final_price = roundf(final_price * 100) / 100;
}
//------------------------------------------------------------------------------
void Service::SetAsPaid()
{
	paid = true;
}
//------------------------------------------------------------------------------
void Service::SetAsUnPaid()
{
	paid = false;
}
//------------------------------------------------------------------------------
void Service::ComputePrice()
{
	//set the fare indicated by taximeter that depends on the time of the day it started
	if (day_distance > night_distance)
		pre_price = base_price_day;
	else if (day_distance < night_distance)
		pre_price = base_price_night;
	else
		pre_price = (base_price_day + base_price_night) / 2;

	float average_speed;
	if ((day_distance + night_distance) > 10)
		average_speed = average_speed_off_city;
	else
		average_speed = average_speed_city;

	//calculate price of daytime travel based on distance
	pre_price += price_per_km_day * day_distance;

	//calculate price of nigthtime travel based on distance
	pre_price += price_per_km_night * night_distance;

	//make the proper adjustment if the trip took more than the expected
	float max_expect_time = ((day_distance + night_distance) / average_speed) * 60;  //max_expected_time in minutes
	if (duration > max_expect_time)
		pre_price += (price_per_minute * (duration - max_expect_time));

	pre_price = roundf(pre_price * 100) / 100;
}
//------------------------------------------------------------------------------
void Service::SetBasePriceDay(float base_price_day)
{
	Service::base_price_day = base_price_day;
}
//------------------------------------------------------------------------------
void Service::SetBasePriceNight(float base_price_night)
{
	Service::base_price_night = base_price_night;
}
//------------------------------------------------------------------------------
void Service::SetAverageSpeedCity(float average_speed_city)
{
	Service::average_speed_city = average_speed_city;
}
//------------------------------------------------------------------------------
void Service::SetAverageSpeedOffCity(float average_speed_off_city)
{
	Service::average_speed_off_city = average_speed_off_city;
}
//------------------------------------------------------------------------------
void Service::SetPricePerMinute(float price_per_minute)
{
	Service::price_per_minute = price_per_minute;
}
//------------------------------------------------------------------------------
void Service::SetPricePerKmDay(float price_per_km_day)
{
	Service::price_per_km_day = price_per_km_day;
}
//------------------------------------------------------------------------------
void Service::SetPricePerKmNight(float price_per_km_night)
{
	Service::price_per_km_night = price_per_km_night;
}
//------------------------------------------------------------------------------
float Service::GetAverageSpeedCity()
{
	return average_speed_city;
}
//------------------------------------------------------------------------------
float Service::GetAverageSpeedOffCity()
{
	return average_speed_off_city;
}
//------------------------------------------------------------------------------
float Service::GetBasePriceDay()
{
	return base_price_day;
}
//------------------------------------------------------------------------------
float Service::GetBasePriceNight()
{
	return base_price_night;
}
//------------------------------------------------------------------------------
float Service::GetPricePerKmDay() 
{
	return price_per_km_day;
}
//------------------------------------------------------------------------------
float Service::GetPricePerKmNight()
{
	return price_per_km_night;
}
//------------------------------------------------------------------------------
float Service::GetPricePerMinute()
{
	return price_per_minute;
}
//------------------------------------------------------------------------------
bool operator<(const Service &service1, const Service &service2)
{
	return service1.start_time < service2.start_time;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Service &service)
{
	ostringstream service_oss;
	Date date = service.start_time;
	service_oss << "" << setw(12) << service.id << setw(12) << service.taxi->GetId() << setw(14) << service.GetDistance() << setw(12) << service.duration << setw(16) << date << setw(21) << service.final_price << setw(18);
	if (service.paid)
		service_oss << "Sim";
	else
		service_oss << "Nao";
	string service_str = service_oss.str();
	os << service_str;
	return os;
}
//------------------------------------------------------------------------------
ofstream &operator<<(ofstream &ofs, const Service &service)
{
	ofs << "" << service.taxi->GetId() << " taxi id ; " << service.start << " ; " << service.finish << " ; " << service.day_distance << " ; " << service.night_distance << " ; " << service.duration << " ; " << service.start_time << " start time" << " ; " << service.finish_time << " finish time" << " ; " << service.pre_price << " ; " << service.final_price << " ; " << service.paid;
	return ofs;
}