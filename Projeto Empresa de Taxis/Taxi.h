/**
*
* @file
* @brief Contains class declarations necessary to represent a Taxi and its license plate
*
*/


#pragma once

#include <string>

#include "Driver.h"

using namespace std;

/**
*
* @brief Represents a license plate. (In portuguese format)
*
*/

class LicensePlate
{
	/**
	*
	* @brief Compares two LicensePlate objects. A first LicensePlate object is equal to the second if the three groups of characters are exactly the same
	* @param license_plate1 The first LicensePlate object to be compared.
	* @param license_plate2 The second LicensePlate object to be compared.
	* @return a bool value indicating whether the first is equal to the second or not.
	*
	*/
	friend bool operator==(const LicensePlate &license_plate1, const LicensePlate &license_plate2);
	/**
	*
	* @brief Compares two LicensePlate objects. A first LicensePlate object is different than the second if at least one of the three groups of the characters is different (it returns the opposite of the == operator)
	* @param license_plate1 The first LicensePlate object to be compared.
	* @param license_plate2 The second LicensePlate object to be compared.
	* @return a bool value indicating whether the first is different than the second or not.
	*
	*/
	friend bool operator!=(const LicensePlate &license_plate1, const LicensePlate &license_plate2);
	/**
	*
	* @brief Compares two LicensePlate objects. A first LicensePlate object is less than the second if the month and year of the first respect to a previous date then the second
	* @param license_plate1 The first LicensePlate object to be compared.
	* @param license_plate2 The second LicensePlate object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const LicensePlate &license_plate1, const LicensePlate &license_plate2);
	/**
	*
	* @brief Outputs a LicensePlate to an ostream
	* @param os The ostream to output to.
	* @param license_plate The LicensePlate to output to the ostream.
	* @return the ostream after outputing the LicensePlate.
	*
	*/
	friend ostream &operator<<(ostream &os, const LicensePlate license_plate);
	/**
	*
	* @brief Extracts a LicensePlate from an istream
	* @param is The istream to input from.
	* @param license_plate The LicensePlate to input from the istream.
	* @return the istream after inputting the LicensePlate.
	*
	*/
	friend istream &operator>>(istream &is, LicensePlate &license_plate);
private:
	/**
	*
	* @brief The first group of 2 characters of a portuguese license plate
	*
	*/
	string first;
	/**
	*
	* @brief The second group of 2 characters of a portuguese license plate
	*
	*/
	string second;
	/**
	*
	* @brief The third group of 2 characters of a portuguese license plate
	*
	*/
	string third;
	/**
	*
	* @brief The month of a portuguese license plate
	*
	*/
	unsigned int month;
	/**
	*
	* @brief The year of a portuguese license plate
	*
	*/
	unsigned int year;
public:
	/**
	*
	* @brief Exception thrown when extracting a license plate from a stream fails (using the overloaded operator>>).
	*
	*/
	class ErrorReadingLicensePlate {};
	/**
	*
	* @brief Exception thrown when an invalid license plate is read from a stream (using the overloaded operator>>).
	*
	*/
	class InvalidLicensePlate {};
	/**
	*
	* @brief Creates a new LicensePlate object based on either information loaded from the file or read from the user. Recieves all the attributes of a LicensePlate object.
	*
	*/
	LicensePlate(string first, string second, string third, unsigned char month, unsigned int year);
	/**
	*
	* @brief Default constructor.
	*
	*/
	LicensePlate();
	const string& GetFirst() const;
	const string& GetSecond() const;
	const string& GetThird() const;
	unsigned char GetMonth() const;
	unsigned int GetYear() const;
	void SetFirst(const string& first);
	void SetSecond(const string& second);
	void SetThird(const string& third);
	void SetMonth(unsigned char month);
	void SetYear(unsigned int year);
};

/**
*
* @brief Represents a taxi.
*
*/

class Taxi
{
	/**
	*
	* @brief A Taxi is equal to another if their ids are the same (because the ids are unique).
	* @param taxi1 The first Taxi object to be compared.
	* @param taxi2 The second Taxi object to be compared.
	* @return a bool value indicating whether the first is equal to the second or not.
	*
	*/
	friend bool operator==(const Taxi &taxi1, const Taxi &taxi2);
	/**
	*
	* @brief Compares two Taxi objects. A first Taxi object is less than the second if the first's id is less (numerically, using the operator<) than the second's.
	* @param taxi1 The first Taxi object to be compared.
	* @param taxi2 The second Taxi object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const Taxi &taxi1, const Taxi &taxi2);
	/**
	*
	* @brief Compares two Taxi objects just like the operator< does. This function, instead of recieving two references for taxis, recieves two pointers for taxis. A first Taxi object is less than the second if the first's id is less (numerically, using the operator<) than the second's.
	* @param taxi1 A pointer to the first Taxi object to be compared.
	* @param taxi2 A pointer to the second Taxi object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool CompareTaxisIds(const Taxi *taxi1, const Taxi *taxi2);
	/**
	*
	* @brief Outputs a Taxi to an ostream.
	* @param os The ostream to output to.
	* @param taxi The Taxi to output to the ostream.
	* @return the ostream after outputing the Taxi.
	*
	*/
	friend ostream &operator<<(ostream &os, const Taxi &taxi);
	/**
	*
	* @brief Outputs a Taxi to an ofstream.
	* @param os The ofstream to output to.
	* @param taxi The Taxi to output to the ofstream.
	* @return the ofstream after outputing the Taxi.
	*
	*/
	friend ofstream &operator<<(ofstream &ofs, const Taxi &taxi);
private:
	/**
	*
	* @brief Taxi's unique identifier.
	*
	*/
	unsigned int id;
	/**
	*
	* @brief Taxi's driver. All drivers must have a taxi, but a taxi can have no driver (it may be associated later). If the taxi has no driver, this attribute's (Driver's) name is an empty string, that is how it is flagged.
	*
	*/
	Driver driver;
	/**
	*
	* @brief The kilometers travelled by the taxi.
	*
	*/
	unsigned int km;
	/**
	*
	* @brief The number of seats of the taxi, including the driver's seat.
	*
	*/
	unsigned int num_of_seats;
	/**
	*
	* @brief Taxi's license plate. (In portuguese format)
	*
	*/
	LicensePlate license_plate;
	/**
	*
	* @brief The date when the Taxi was registered in the company.
	*
	*/
	Date regist_date;
	/**
	*
	* @brief The time when the taxi will be available to perform a service in unix format (counted from the Epoch).
	*
	*/
	time_t time_when_available;
	/**
	*
	* @brief Stores the highest id assigned to a Taxi (this is used to know the id of the next Taxi to be added or extracted from the file, because the ids are incremental)
	*
	*/
	static unsigned int curr_taxi_id;
public:
	/**
	*
	* @brief Creates a new Driver object based on information loaded from the file. Recieves all the attributes because it is called to create a new Driver based on the information loaded from the file (that stores all the attributes).
	*
	*/
	Taxi(unsigned int id, Driver driver, unsigned int km, unsigned num_of_seats, LicensePlate license_plate, Date regist_date);
	/**
	*
	* @brief Creates a new Driver object based on input from the user. Recieves only some attributes because it is called when the Driver is created using input from the user. The remaining attributes are initialized to their default values.
	*
	*/
	Taxi(LicensePlate license_plate, unsigned int km, unsigned num_of_seats);
	/**
	*
	* @brief Creates a new Taxi object based on its id. Recieves only the id because it is used to create a temporary auxiliary customer to use lower_bound to search for a customer. The vector of Customer* is sorted by their ids, so the temporary customer only needs to have its id set. The remaining attributes are initialized to their default values.
	*
	*/
	Taxi(unsigned int id);
	/**
	*
	* @brief Default constructor.
	*
	*/
	Taxi();
	const Driver &GetDriver() const;
	unsigned int GetId() const;
	unsigned int GetKm() const;
	const LicensePlate& GetLicensePlate() const;
	unsigned int GetNumOfSeats() const;
	static unsigned int GetCurrTaxiId();
	void SetDriver(const Driver& driver);
	void SetId(unsigned int id);
	void SetKm(unsigned int km);
	void SetLicensePlate(const LicensePlate& licensePlate);
	void SetNumOfSeats(unsigned int numOfSeats);
	void SetRegistDate(const Date &date);
	time_t GetTimeWhenAvailable();
	static void SetCurrTaxiId(unsigned int curr_taxi_id);
	/**
	*
	* @brief Updates the attribute time_when_available of the Taxi object based on the time of the sevrice that it will perform. The time when the taxi will be available is equal to the current system time plus the duration of the service that it will perform.
	* @param service_duration the duration of the service that the taxi will perform. (the amount to add to the current system time).
	*
	*/
	void UpdateTimeWhenAvailable(time_t service_duration);
	/**
	*
	* @brief  Increments the current travelled distance of a taxi 
	* @param km_to_add the amount of the km to be added to the current km of the taxi
	*/
	void IncrementKm(unsigned int km_to_add);
};


/**
*
* @brief This class contains a pointer to a Taxi. This class is used to improve service performing. It is necessary to implement the taxis priority queue (a priority_queue that contains all the Taxis that can perform services, sorted by the time they take to be able to satisfy a customer request.
*
*/
class TaxiPtr
{
	/**
	*
	* @brief Dereferences a TaxiPtr object. Returns the content of the adress of memory pointed to by the data member taxi.
	* @param taxi_ptr The TaxiPtr to dereference.
	* @return the content of the memory adress pointed to by taxi attrib.
	*
	*/
	friend Taxi operator*(const TaxiPtr &taxi_ptr);
	/**
	*
	* @brief Compares two TaxiPtr objects. A first TaxiPtr object is less than the second if the first's available time is higher than the second's. This operator guarantees that the priority queue of available taxis remains sorted by the time when each taxi will be available (maintains the taxi that takes less time at the top).
	* @param taxi1_ptr The first TaxiPtr object to be compared.
	* @param taxi2_ptr The second TaxiPtr object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const TaxiPtr &taxi1_ptr, const TaxiPtr &taxi2_ptr);
private:
	/**
	*
	* @brief A pointer to the Taxi to which the objecto TaxiPtr refers to.
	*
	*/
	Taxi *taxi;
public:
	/**
	*
	* @brief Builds a new TaxiPtr object based on a pointer to the Taxi to which the TaxiPtr object will refer to.
	*
	*/
	TaxiPtr(Taxi *taxi);
	Taxi *GetTaxi() const;
};
