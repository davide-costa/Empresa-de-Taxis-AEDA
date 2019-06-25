/**
*
* @file
* @brief Contains class declaration that represents a driver
*
*/


#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

using namespace std;

/**
*
* @brief Represents a driver (of a taxi). A driver is always associated with a taxi. There cannot be a driver that has no taxi. A driver must always have a taxi.
*
*/

class Driver
{
	/**
	*
	* @brief Outputs a Driver to an ostream.
	* @param os The ostream to output to.
	* @param driver The Driver to output to the ostream.
	* @return the ostream after outputing the Driver.
	*
	*/
	friend ostream &operator<<(ostream &os, const Driver &driver);
	/**
	*
	* @brief Outputs a Driver to an ofstream.
	* @param os The ofstream to output to.
	* @param driver The Driver to output to the ofstream.
	* @return the ofstream after outputing the Driver.
	*
	*/
	friend ofstream &operator<<(ofstream &ofs, const Driver &driver);
private:
	/**
	*
	* @brief Drvier's unique identifier.
	*
	*/
	unsigned int id;
	/**
	*
	* @brief Driver's name.
	*
	*/
	string name;
	/**
	*
	* @brief Driver's adress (the place where he lives).
	*
	*/
	string adress;
	/**
	*
	* @brief Driver's NIF (Número de Identificação Fiscal).
	*
	*/
	unsigned int NIF;
	/**
	*
	* @brief The date when the driver was registered in the company.
	*
	*/
	Date regist_date;
	/**
	*
	* @brief The number that identifies the driver's license of the driver.
	*
	*/
	unsigned int drivers_license;
	/**
	*
	* @brief Stores the highest id assigned to a driver (this is used to know the id of the next driver to be added or extracted from the file, because the ids are incremental)
	*
	*/
	static unsigned int curr_driver_id;
public:
	/**
	*
	* @brief Creates a new Driver object based on information loaded from the file. Recieves all the attributes because it is called to create a new driver based on the information loaded from the file (that stores all the attributes).
	*
	*/
	Driver(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int drivers_license);
	/**
	*
	* @brief Creates a new Driver object based on input from the user. Recieves only some attributes because it is called when the driver is created using input from the user. The remaining attributes are initialized to their default values.
	*
	*/
	Driver(string name, string adress, unsigned int NIF, unsigned int drivers_license);
	/**
	*
	* @brief Default constructor.
	*
	*/
	Driver();
	const string& GetAdress() const;
	unsigned int GetDriversLicense() const;
	unsigned int GetId() const;
	const string& GetName() const;
	unsigned int GetNif() const;
	Date GetRegistDate() const;
	void SetAdress(const string& adress);
	void SetDriversLicense(unsigned int driversLicense);
	void SetId(unsigned int id);
	void SetName(const string& name);
	void SetNif(unsigned int nif);
	void SetRegistDate(Date registDate);
	static unsigned int GetCurrDriverId();
	static void SetCurrDriverId(unsigned int currDriverId);
};