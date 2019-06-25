#include "Driver.h"

#include "utils.h"

unsigned int Driver::curr_driver_id = 0;

Driver::Driver()
{
	this->id = 0;
}
//------------------------------------------------------------------------------
Driver::Driver(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int drivers_license)
{
	this->id = id;
	this->name = name;
	this->adress = adress;
	this->NIF = NIF;
	this->regist_date = regist_date;
	this->drivers_license = drivers_license;
}
//------------------------------------------------------------------------------
Driver::Driver(string name, string adress, unsigned int NIF, unsigned int drivers_license)
{
	this->id = (++curr_driver_id);
	this->name = name;
	this->adress = adress;
	this->NIF = NIF;
	GetDateFromWindows(regist_date);
	this->drivers_license = drivers_license;
}
//------------------------------------------------------------------------------
const string& Driver::GetAdress() const 
{
	return adress;
}
//------------------------------------------------------------------------------
unsigned int Driver::GetDriversLicense() const
{
	return drivers_license;
}
//------------------------------------------------------------------------------
unsigned int Driver::GetId() const
{
	return id;
}
//------------------------------------------------------------------------------
const string& Driver::GetName() const
{
	return name;
}
//------------------------------------------------------------------------------
unsigned int Driver::GetNif() const
{
	return NIF;
}
//------------------------------------------------------------------------------
Date Driver::GetRegistDate() const
{
	return regist_date;
}
//------------------------------------------------------------------------------
void Driver::SetAdress(const string& adress) 
{
	this->adress = adress;
}
//------------------------------------------------------------------------------
void Driver::SetDriversLicense(unsigned int driversLicense) 
{
	drivers_license = driversLicense;
}
//------------------------------------------------------------------------------
void Driver::SetId(unsigned int id) 
{
	this->id = id;
}
//------------------------------------------------------------------------------
void Driver::SetName(const string& name) 
{
	this->name = name;
}
//------------------------------------------------------------------------------
void Driver::SetNif(unsigned int nif) 
{
	NIF = nif;
}
//------------------------------------------------------------------------------
void Driver::SetRegistDate(Date regist_date) 
{
	this->regist_date = regist_date;
}
//------------------------------------------------------------------------------
unsigned int Driver::GetCurrDriverId()
{
	return curr_driver_id;
}
//------------------------------------------------------------------------------
void Driver::SetCurrDriverId(unsigned int new_driver_id)
{
	curr_driver_id = new_driver_id;
}
//---------------------------------------Operator Overloads---------------------------------------
ostream &operator<<(ostream &os, const Driver &driver)
{
	//In order for the setw to work properly, an entire string must be sent (all at once) to the ostream
	ostringstream driver_oss;
	driver_oss << setw(4) << driver.id << setw(18) << driver.name << setw(37) << driver.adress << setw(16) << driver.NIF << setw(20) << driver.regist_date << setw(24) << driver.drivers_license;
	string driver_str = driver_oss.str();
	os << driver_str;

	return os;
}
//------------------------------------------------------------------------------
ofstream &operator<<(ofstream &ofs, const Driver &driver)
{
	ofs << driver.name << " ; " << driver.adress << " ; " << driver.NIF << " ; " << driver.regist_date << " ; " << driver.drivers_license;
	return ofs;
}