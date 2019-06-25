#include "Taxi.h"
#include "utils.h"
#include <algorithm>

#include "EmpresaDeTaxis.h"

//---------------------------------------Class LicensePlate---------------------------------------
LicensePlate::LicensePlate(string first, string second, string third, unsigned char month, unsigned int year)
{
	this->first = first;
	this->second = second;
	this->third = third;
	this->month = month;
	this->year = year;
}
//------------------------------------------------------------------------------
LicensePlate::LicensePlate()
{

}
//------------------------------------------------------------------------------
const string& LicensePlate::GetFirst() const 
{
	return first;
}
//------------------------------------------------------------------------------
const string& LicensePlate::GetSecond() const
{
	return second;
}
//------------------------------------------------------------------------------
const string& LicensePlate::GetThird() const
{
	return third;
}
//------------------------------------------------------------------------------
unsigned char LicensePlate::GetMonth() const
{
	return month;
}
//------------------------------------------------------------------------------
unsigned int LicensePlate::GetYear() const
{
	return year;
}
//------------------------------------------------------------------------------
void LicensePlate::SetFirst(const string& first) 
{
	this->first = first;
}
//------------------------------------------------------------------------------
void LicensePlate::SetSecond(const string& second) 
{
	this->second = second;
}
//------------------------------------------------------------------------------
void LicensePlate::SetThird(const string& third)
{
	this->third = third;
}
//------------------------------------------------------------------------------
void LicensePlate::SetMonth(unsigned char month)
{
	this->month = month;
}
//------------------------------------------------------------------------------
void LicensePlate::SetYear(unsigned int year) 
{
	this->year = year;
}
//---------------------------------------Operator Overloads---------------------------------------
//------------------------------------------------------------------------------
bool operator==(const LicensePlate &license_plate1, const LicensePlate &license_plate2)
{
	if (license_plate1.first != license_plate2.first)
		return false;

	if (license_plate1.second != license_plate2.second)
		return false;

	if (license_plate1.third != license_plate2.third)
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool operator!=(const LicensePlate & license_plate1, const LicensePlate & license_plate2)
{
	return !(license_plate1 == license_plate2);
}
//------------------------------------------------------------------------------
bool operator<(const LicensePlate &license_plate1, const LicensePlate &license_plate2)
{
	if (license_plate1.GetYear() < license_plate1.GetYear())
		return true;

	if (license_plate1.GetYear() > license_plate1.GetYear())
		return false;

	if (license_plate1.GetMonth() < license_plate1.GetMonth())
		return true;

	if (license_plate1.GetMonth() > license_plate1.GetMonth())
		return false;

	return false;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const LicensePlate license_plate)
{
	//In order for the setw to work properly, an entire string must be sent (all at once) to the ostream
	ostringstream license_plate_oss;
	string neat_month;
	if (license_plate.month < 10)
		neat_month = "0";
	license_plate_oss << license_plate.first << "-" << license_plate.second << "-" << license_plate.third << " " << neat_month << license_plate.month << "/" << license_plate.year;
	string license_plate_str = license_plate_oss.str();
	os << license_plate_str;

	return os;
}
//------------------------------------------------------------------------------
istream &operator>>(istream &is, LicensePlate &license_plate)
{
	char ch;
	getline(is, license_plate.first, '-');
	RemoveSpacesFromWord(license_plate.first);
	getline(is, license_plate.second, '-');
	RemoveSpacesFromWord(license_plate.second);
	getline(is, license_plate.third, ' ');
	is >> license_plate.month >> ch;
	is >> license_plate.year;

	transform(license_plate.first.begin(), license_plate.first.end(), license_plate.first.begin(), toupper);
	transform(license_plate.second.begin(), license_plate.second.end(), license_plate.second.begin(), toupper);
	transform(license_plate.third.begin(), license_plate.third.end(), license_plate.third.begin(), toupper);

	if (is.fail())
		throw LicensePlate::ErrorReadingLicensePlate();

	if (!IsLicensePlateValid(license_plate))
		throw LicensePlate::InvalidLicensePlate();

	return is;
}
//---------------------------------------Class Taxi---------------------------------------
//------------------------------------------------------------------------------
unsigned int Taxi::curr_taxi_id = 0;
//------------------------------------------------------------------------------
unsigned int Taxi::GetCurrTaxiId()
{
	return curr_taxi_id;
}
//------------------------------------------------------------------------------
Taxi::Taxi(unsigned int id, Driver driver, unsigned int km, unsigned num_of_seats, LicensePlate license_plate, Date regist_date)
{
	this->id = id;
	this->driver = driver;
	this->km = km;
	this->num_of_seats = num_of_seats;
	this->license_plate = license_plate;
	this->regist_date = regist_date;
	time_when_available = time(NULL);
	if (time_when_available == -1)
		throw EmpresaDeTaxis::ErrorGettingLocalTime();
}
//------------------------------------------------------------------------------
Taxi::Taxi(LicensePlate license_plate, unsigned int km, unsigned num_of_seats)
{
	Driver driver;
	driver.SetId(0);
	Date date;
	GetDateFromWindows(date);
	id = (++curr_taxi_id);
	this->driver = driver;
	this->license_plate = license_plate;
	this->km = km;
	this->num_of_seats = num_of_seats;
	regist_date = date;
	time_when_available = time(NULL);
	if (time_when_available == -1)
		throw EmpresaDeTaxis::ErrorGettingLocalTime();
}
//------------------------------------------------------------------------------
Taxi::Taxi(unsigned int id)
{
	this->id = id;
}
//------------------------------------------------------------------------------
Taxi::Taxi()
{

}
//------------------------------------------------------------------------------
const Driver& Taxi::GetDriver() const 
{
	return driver;
}
//------------------------------------------------------------------------------
void Taxi::SetDriver(const Driver& driver) 
{
	this->driver = driver;
}
//------------------------------------------------------------------------------
unsigned int Taxi::GetId() const 
{
	return id;
}
//------------------------------------------------------------------------------
void Taxi::SetId(unsigned int id) 
{
	this->id = id;
}
//------------------------------------------------------------------------------
unsigned int Taxi::GetKm() const 
{
	return km;
}
//------------------------------------------------------------------------------
void Taxi::SetKm(unsigned int km) 
{
	this->km = km;
}
//------------------------------------------------------------------------------
const LicensePlate& Taxi::GetLicensePlate() const 
{
	return license_plate;
}
//------------------------------------------------------------------------------
void Taxi::SetLicensePlate(const LicensePlate& license_plate) 
{
	this->license_plate = license_plate;
}
//------------------------------------------------------------------------------
unsigned int Taxi::GetNumOfSeats() const 
{
	return num_of_seats;
}
//------------------------------------------------------------------------------
void Taxi::SetNumOfSeats(unsigned int num_of_seats)
{
	this->num_of_seats = num_of_seats;
}
//------------------------------------------------------------------------------
void Taxi::SetRegistDate(const Date &date)
{
	regist_date = date;
}
//------------------------------------------------------------------------------
time_t Taxi::GetTimeWhenAvailable()
{
	return time_when_available;
}
//------------------------------------------------------------------------------
void Taxi::SetCurrTaxiId(unsigned int curr_taxi_id)
{
	Taxi::curr_taxi_id = curr_taxi_id;
}
//------------------------------------------------------------------------------
void Taxi::UpdateTimeWhenAvailable(time_t service_duration)
{
	time_t curr_system_time = time(NULL);
	if (curr_system_time == -1)
		throw EmpresaDeTaxis::ErrorGettingLocalTime();
	time_when_available = curr_system_time + service_duration;
}
//------------------------------------------------------------------------------
void Taxi::IncrementKm(unsigned int km_to_add)
{
	km += km_to_add;
}
//---------------------------------------Operator Overloads---------------------------------------
//------------------------------------------------------------------------------
bool operator==(const Taxi &taxi1, const Taxi &taxi2)
{
	return taxi1.id == taxi2.id;
}
//------------------------------------------------------------------------------
bool operator<(const Taxi &taxi1, const Taxi &taxi2)
{
	return taxi1.id < taxi2.id;
}
//------------------------------------------------------------------------------
bool CompareTaxisIds(const Taxi *taxi1, const Taxi *taxi2)
{
	return taxi1->id < taxi2->id;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Taxi &taxi)
{
	//In order for the setw to work properly, an entire string must be sent (all at once) to the ostream
	ostringstream taxi_oss;
	taxi_oss << setw(4) << taxi.id << setw(19);
	if (taxi.driver.GetName().empty())
		taxi_oss << "Nao Atribuido";
	else
		taxi_oss << taxi.driver.GetId();
	taxi_oss << setw(15) << taxi.km << setw(25) << taxi.num_of_seats << setw(25) << taxi.license_plate << setw(24) << taxi.regist_date;
	string taxi_str = taxi_oss.str();
	os << taxi_str;

	return os;

}
//------------------------------------------------------------------------------
ofstream &operator<<(ofstream &ofs, const Taxi &taxi)
{
	ofs << "" << taxi.id << " ; " << taxi.km << " km" << " ; " << taxi.num_of_seats << " seats" << " ; " << taxi.license_plate << " ; " << taxi.regist_date;
	return ofs;
}
//------------------------------------------------------------------------------
Taxi operator*(const TaxiPtr &taxi_ptr)
{
	return *taxi_ptr.taxi;
}
//------------------------------------------------------------------------------
bool operator<(const TaxiPtr &taxi1_ptr, const TaxiPtr &taxi2_ptr)
{
	return (*taxi1_ptr).GetTimeWhenAvailable() > (*taxi2_ptr).GetTimeWhenAvailable();  //for the taxi which is the first to be available to be in the top of the priority queue (because stl's priority queue it´s implemented as a max heap)
}
//------------------------------------------------------------------------------
TaxiPtr::TaxiPtr(Taxi *taxi)
{
	this->taxi = taxi;
}
//------------------------------------------------------------------------------
Taxi *TaxiPtr::GetTaxi() const
{
	return taxi;
}