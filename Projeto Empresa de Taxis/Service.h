/**
*
* @file
* @brief Contains class declaration necessary to represent a service (trip)
*
*/

#pragma once

#include <string>
#include "TimeStamp.h"
#include "Taxi.h"

using namespace std;

/**
*
* @brief Represents a service (trip).
*
*/

class Service
{
	/**
	*
	* @brief Compares two Service objects. A first object Service is less than the second if the start time of the first (a timestamp) respects to a previous time than the second.
	* @param service1 The first Service object to be compared.
	* @param service2 The second Service object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const Service &service1, const Service &service2);
	/**
	*
	* @brief Outputs a Service to an ostream.
	* @param os The ostream to output to.
	* @param service The Service to output to the ostream.
	* @return the ostream after outputing the Service.
	*
	*/
	friend ostream &operator<<(ostream &os, const Service &service);
	/**
	*
	* @brief Outputs a Service to an ofstream.
	* @param os The ofstream to output to.
	* @param service The Service to output to the ofstream.
	* @return the ofstream after outputing the Service.
	*
	*/
	friend ofstream &operator<<(ofstream &os, const Service &service);
protected:
	/**
	*
	* @brief Service's unique identifier.
	*
	*/
	unsigned int id;
	/**
	*
	* @brief The adress where the taxi left from to perform the service.
	*
	*/
	string start;
	/**
	*
	* @brief The adress where the taxi arrived at to perform the service.
	*
	*/
	string finish;
	/**
	*
	* @brief Distance travelled by the taxi in day time, in km.
	*
	*/
	unsigned int day_distance;
	/**
	*
	* @brief Distance travelled by the taxi in night time, in km.
	*
	*/
	unsigned int night_distance;
	/**
	*
	* @brief The total elapsed time during the trip, in minutes.
	*
	*/
	unsigned int duration;
	/**
	*
	* @brief A timestamp indicating the date and time when the trip started. It is used to determine the Timestamp of the trip (and not the finish_time).
	*
	*/
	TimeStamp start_time;
	/**
	*
	* @brief A timestamp indicating the date and time when the trip ended.
	*
	*/
	TimeStamp finish_time;
	/**
	*
	* @brief A pointer to the taxi that was used to perform the service
	*
	*/
	Taxi *taxi;
	/**
	*
	* @brief The price of the service calculated based on the base price, price per km or price per minute.
	*
	*/
	float pre_price;
	/**
	*
	* @brief The price that the customer actually paid for the service, based on the discounts (if applicable).
	*
	*/
	float final_price;
	/**
	*
	* @brief Indicates whether the service has been paid or not. Is set to true if the service was already paid; false if the customer has not paid the service, i. e., if he postponed it to the end of the month.
	*
	*/
	bool paid;
	/**
	*
	* @brief Stores the highest id assigned to a service (this is used to know the id of the next service to be added or extracted from the file, because the ids are incremental)
	*
	*/
	static unsigned int curr_service_id;
	/**
	*
	* @brief The base price of a service in day time. (In portuguese: bandeirada durante o dia)
	*
	*/
	static float base_price_day;
	/**
	*
	* @brief The base price of a service in night time. (In portuguese: bandeirada durante a noite)
	*
	*/
	static float base_price_night;
	/**
	*
	* @brief The average speed inside the city. This attribute is used to calculate the average expected time of the trip inside the city (based also on the distance travlled)
	*
	*/
	static float average_speed_city;
	/**
	*
	* @brief The average speed outside the city. This attribute is used to calculate the average expected time of the trip outside the city (based also on the distance travlled)
	*
	*/
	static float average_speed_off_city;
	/**
	*
	* @brief Price of a service per minute
	*
	*/
	static float price_per_minute;
	/**
	*
	* @brief Price of a service per km in day time
	*
	*/
	static float price_per_km_day;
	/**
	*
	* @brief Price of a service per km in night time
	*
	*/
	static float price_per_km_night;
public:
	/**
	*
	* @brief Creates a new Service object based on information loaded from the file. Recieves all the attributes because it is called to create a new service based on the information loaded from the file (that stores all the attributes).
	*
	*/
	Service(unsigned int id, string start, string finish, unsigned int day_distance, unsigned int night_distance, time_t duration, TimeStamp start_time, TimeStamp finish_time, Taxi* taxi, float pre_price, float final_price, bool paid);
	/**
	*
	* @brief Creates a new Service object based on input from the user. Recieves only some attributes because it is called when the service is created using input from the user. The remaining attributes are initialized to their default values.
	*
	*/
	Service(string start, string finish, unsigned int day_distance, unsigned int night_distance, time_t duration, Taxi* taxi);
	/**
	*
	* @brief Creates a new Service object based on its name. Recieves only the date because it is used to create a temporary auxiliary service to use lower_bound to search for a service. The vector of Service* is sorted by their dates, so the temporary service only needs to have its name set. The remaining attributes are initialized to their default values.
	*
	*/
	Service(Date date);
	/**
	*
	* @brief Default constructor.
	*
	*/
	Service();
	unsigned int GetId() const;
	string GetStart() const;
	string GetFinish() const;
	unsigned int GetDayDistance() const;
	unsigned int GetNightDistance() const;
	unsigned int GetDistance() const;
	unsigned int GetDuration() const;
	static unsigned int GetCurrServiceId();
	static void SetCurrServiceId(unsigned int curr_service_id);
	const Date &GetDate() const;
	const Date &GetFinalDate() const;
	const Taxi *GetTaxi() const;
	float GetPrePrice() const;
	float GetFinalPrice() const;
	bool IsPaid() const;
	void SetFinalPrice(float final_price);
	/**
	*
	* @brief Sets the service as paid. (Sets the paid attribute to true)
	*
	*/
	void SetAsPaid();
	/**
	*
	* @brief Sets the service as unpaid. (Sets the paid attribute to false)
	*
	*/
	void SetAsUnPaid();
	/**
	*
	* @brief Calculates the price of a service based on the time it ocurred (day or night). It uses the appropriate base price (bandeirada) (day or night time) based on the highest travelled distance (day or night). It calculates the price based on kilometers travelled. But, if it takes longer than expected, starts adding the price by minute. When it's done computing the price, sets the pre_price attribute to the value it calculated.
	*
	*/
	void ComputePrice();
	static void SetBasePriceDay(float base_price_day);
	static void SetBasePriceNight(float base_price_night);
	static void SetAverageSpeedCity(float average_speed_city);
	static void SetAverageSpeedOffCity(float average_speed_off_city);
	static void SetPricePerMinute(float price_per_minute);
	static void SetPricePerKmDay(float price_per_km_day);
	static void SetPricePerKmNight(float price_per_km_night);
	static float GetAverageSpeedCity();
	static float GetAverageSpeedOffCity();
	static float GetBasePriceDay();
	static float GetBasePriceNight();
	static float GetPricePerKmDay();
	static float GetPricePerKmNight();
	static float GetPricePerMinute();
};