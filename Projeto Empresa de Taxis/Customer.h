/**
*
* @file
* @brief Contains class declarations necessary to represent all informations regarding a customer
*
*/


#pragma once
#include <string>
#include <vector>
#include <iomanip>

#include "Date.h"
#include "Service.h"

using namespace  std;

/**
*
* @brief Contains all the information necessary for the customer discount system (that allows customers to enjoy vouchers and free trips in the next month). It represents the discount information for each customer.
*
*/

class CustomerDiscount
{
	/**
	*
	* @brief Outputs a CustomerDiscount to an ostream.
	* @param os The ostream to output to.
	* @param customer The CustomerDiscount to output to the ostream.
	* @return the ostream after outputing the CustomerDiscount.
	*
	*/
	friend ostream &operator<<(ostream &os, const CustomerDiscount &customer);
	/**
	*
	* @brief Outputs a CustomerDiscount to an ofstream.
	* @param os The ofstream to output to.
	* @param customer The CustomerDiscount to output to the ofstream.
	* @return the ofstream after outputing the CustomerDiscount.
	*
	*/
	friend ofstream &operator<<(ofstream &os, const CustomerDiscount &customer);
private:
	/**
	*
	* @brief This atribute stores the amount in voucher that the customer has the right to enjoy
	*
	*/
	unsigned int voucher;
	/**
	*
	* @brief This atribute stores the month in which the customer can enjoy the voucher (if applicable). If no voucher is applicable, this atribute is set to 0 (zero).
	*
	*/
	unsigned int voucher_valid_month;
	/**
	*
	* @brief This atribute stores the year in which the customer can enjoy the voucher (if applicable). If no voucher is applicable, this atribute is set to 0 (zero).
	*
	*/
	unsigned int voucher_valid_year;
	/**
	*
	* @brief This atribute stores whether the customer has the right to enjoy a free trip of not
	*
	*/
	bool free_trip;
	/**
	*
	* @brief This atribute stores the month in which the customer can enjoy the free_trip (if applicable). If no free trip is applicable, this atribute is set to 0 (zero).
	*
	*/
	unsigned int free_trip_valid_month;
	/**
	*
	* @brief This atribute stores the year in which the customer can enjoy the voucher (if applicable). If no voucher is applicable, this atribute is set to 0 (zero).
	*
	*/
	unsigned int free_trip_valid_year;
	/**
	*
	* @brief This atribute stores the number of trips that the customer has done in the current month.
	*
	*/
	unsigned int num_trips;
	/**
	*
	* @brief This atribute stores the amount that the customer has spent in the Taxi Company in the current month.
	*
	*/
	float amount_paid;
	/**
	*
	* @brief This atribute stores the current month (the month in which the last atributes are valid)
	*
	*/
	unsigned int current_month;	
	/**
	*
	* @brief This atribute stores the current year (the year in which the last atributes are valid)
	*
	*/
	unsigned int current_year;
public:
	/**
	*
	* @brief Creates a new CustomerDiscount object based on information loaded from the file. Recieves all the attributes because it is called to create a new customer based on the information loaded from the file (that stores all the attributes).
	*
	*/
	CustomerDiscount(unsigned int voucher, unsigned int voucher_valid_month, unsigned int voucher_valid_year, bool free_trip, unsigned int free_trip_valid_month, unsigned int free_trip_valid_year, unsigned int num_trips, unsigned int amount_paid, unsigned int current_month, unsigned int current_year);
	/**
	*
	* @brief Default constructor.
	*
	*/
	CustomerDiscount();
	bool IsFreeTrip() const;
	unsigned int GetFreeTripValidMonth() const;
	unsigned int GetFreeTripValidYear() const;
	unsigned int GetVoucher() const;
	unsigned int GetVoucherValidMonth() const;
	unsigned int GetVoucherValidYear() const;
	unsigned int GetAmountPaid() const;
	unsigned int GetCurrentMonth() const;
	unsigned int GetCurrentYear() const;
	unsigned int GetNumTrips() const;
	bool IsVoucherAvailable();
	bool IsFreeTripAvailable();
	void SetFreeTrip(bool free_trip);
	void SetFreeTripValidMonth(unsigned int free_trip_valid_month);
	void SetFreeTripValidYear(unsigned int free_trip_valid_year);
	void SetVoucher(unsigned int voucher);
	void SetVoucherValidMonth(unsigned int voucher_valid_month);
	void SetVoucherValidYear(unsigned int voucher_valid_year);
	void SetAmountPaid(unsigned int amount_paid);
	void SetCurrentMonth(unsigned int current_month);
	void SetCurrentYear(unsigned int current_year);
	void SetNumTrips(unsigned int num_trips);
	/**
	*
	* @brief Increments the number of trips of the customer in the current month (adds 1 to the counter).
	*
	*/
	void IncrementNumTrips();
	/**
	*
	* @brief Increments the amount that the customer has spent in the Taxi Company in the current month.
	* @param amount The number to add to the amount spent in the Company counter.
	*
	*/
	void IncrementAmountPaid(float amount);
};


/**
*
* @brief Represents a customer. Stores all the information regarding a customer
*
*/

class Customer
{
	/**
	*
	* @brief Compares two Customer objects. A first Customer object is less than the second if the first's name is less (alphabetically, using the string class's operator<) than the second's.
	* @param customer1 The first Customer object to be compared.
	* @param customer2 The second Customer object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const Customer &customer1, const Customer &customer2);
	/**
	*
	* @brief Compares two Customer objects just like the operator< does. This function, instead of recieving two references for customers, recieves two pointers for customers. A first customer object is less than the second if the first's name is less (alphabetically, using the string class's operator<) than the second's.
	* @param customer1 A pointer to the first Customer object to be compared.
	* @param customer2 A pointer to the second Customer object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool CompareCustomersNames(const Customer *customer1, const Customer *customer2);
	/**
	*
	* @brief Compares two Customer objects's regist dates. This function, instead of recieving two references for customers, recieves two pointers for customers. By this function, a first customer object is less than the second if the first's regist date is less (respects to a time before the second's), using the Date class's operator<) than the second's.
	* @param customer1 A pointer to the first Customer object to be compared.
	* @param customer2 A pointer to the second Customer object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool CompareCustomersRegistDates(const Customer *customer1, const Customer *customer2);
	/**
	*
	* @brief Compares two Customer objects's points. This function, instead of recieving two references for customers, recieves two pointers for customers. By this function, a first customer object is less than the second if the first's points are less (numerically) than the second's.
	* @param customer1 A pointer to the first Customer object to be compared.
	* @param customer2 A pointer to the second Customer object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool CompareCustomersPoints(const Customer *customer1, const Customer *customer2);
	/**
	*
	* @brief Compares two Customer objects's unpaid amounts. This function, instead of recieving two references for customers, recieves two pointers for customers. By this function, a first customer object is less than the second if the first's unpaid amount is less (numerically) than the second's.
	* @param customer1 A pointer to the first Customer object to be compared.
	* @param customer2 A pointer to the second Customer object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool CompareCustomersUnPaidAmounts(const Customer *customer1, const Customer *customer2);
	/**
	*
	* @brief Outputs a Customer to an ostream.
	* @param os The ostream to output to.
	* @param customer The Customer to output to the ostream.
	* @return the ostream after outputing the Customer.
	*
	*/
	friend ostream &operator<<(ostream &os, const Customer &customer);
	/**
	*
	* @brief Outputs a Customer to an ofstream.
	* @param os The ofstream to output to.
	* @param customer The Customer to output to the ofstream.
	* @return the ofstream after outputing the Customer.
	*
	*/
	friend ofstream &operator<<(ofstream &ofs, const Customer &customer);
protected:
	/**
	*
	* @brief Customer's unique identifier.
	*
	*/
	unsigned int id;
	/**
	*
	* @brief Customer's name.
	*
	*/
	string name;
	/**
	*
	* @brief Customer's adress (the place where he lives).
	*
	*/
	string adress;
	/**
	*
	* @brief Customer's NIF (Número de Identificação Fiscal).
	*
	*/
	unsigned int NIF;
	/**
	*
	* @brief The date when the customer was registered in the company.
	*
	*/
	Date regist_date;
	/**
	*
	* @brief Vector of all the services that the customer has (A service is when a customer is transported by the company).
	*
	*/
	vector<Service> services;
	/**
	*
	* @brief The points that the customer has scored in the company. (It is equal to the total amoun the customer has spent)
	*
	*/
	unsigned int points;
	/**
	*
	* @brief The total unpaid expenses amount of the customer i. e. the total amount he has postponed to pay in the end of the mount.
	*
	*/
	float unpaid_amount;
	/**
	*
	* @brief This object stores when the last trip of the customer ocurred (in unix format)
	*
	*/
	time_t last_trip_time;
	/**
	*
	* @brief This object stores all the information necessary to determine if the customer has the right to a discount based in all the variants.
	*
	*/
	CustomerDiscount discount;
	/**
	*
	* @brief Stores the highest id assigned to a customer (this is used to know the id of the next customer to be added or extracted from the file, because the ids are incremental)
	*
	*/
	static unsigned int curr_cust_id;
public:
	/**
	*
	* @brief Creates a new Customer object based on information loaded from the file. Recieves all the attributes because it is called to create a new customer based on the information loaded from the file (that stores all the attributes).
	*
	*/
	Customer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount);
	/**
	*
	* @brief Creates a new Customer object based on input from the user. Recieves only some attributes because it is called when the customer is created using input from the user. The remaining attributes are initialized to their default values.
	*
	*/
	Customer(string name, string adress, unsigned int NIF);
	/**
	*
	* @brief Creates a new Customer object based on its id. Recieves only the id because it is used to create a temporary auxiliary customer to search for a customer. The remaining attributes are initialized to their default values.
	*
	*/
	Customer(unsigned int id);
	/**
	*
	* @brief Creates a new Customer object based on its name. Recieves only the name because it is used to create a temporary auxiliary customer to use lower_bound to search for a customer. The vector of Customer* is sorted by their names, so the temporary customer only needs to have its name set. The remaining attributes are initialized to their default values.
	*
	*/
	Customer(string name);
	/**
	*
	* @brief Default constructor.
	*
	*/
	Customer();
	void GetCustomerDiscount(CustomerDiscount &discount) const;
	void SetCustomerDiscount(const CustomerDiscount &discount);
	const string& GetAdress() const;
	void SetAdress(const string& adress);
	unsigned int GetId() const;
	void SetId(unsigned int id);
	const string& GetName() const;
	void SetName(const string& name);
	unsigned int GetNif() const;
	void SetNif(unsigned int nif);
	Date GetRegistDate() const;
	void SetRegistDate(Date registDate);
	void GetServices(vector<Service> &services) const;
	void SetServices(const vector<Service> &services);
	unsigned int GetServicesSize() const;
	void AppendService(Service service);
	unsigned int GetPoints();
	float GetUnPaidAmount();
	time_t GetLastTripTime();
	static unsigned int GetCurrCustId();
	static void SetCurrCustId(unsigned int new_curr_cust_id);
	/**
	*
	* @brief Returns the service with the index idx (in the vector of services) of this Customer object
	* @param idx the index of the service to return (in the vector of services)
	*
	*/
	const Service &GetServiceAtIdx(unsigned int idx) const;
	/**
	*
	* @brief Sorts all the services of the customer using the sort function based on the function that compares two Service*. (Couldn't use the overload because the overload can recieve pointers)
	*
	*/
	void SortServices();
	/**
	*
	* @brief Sets all the services as paid by calling the SetAsPaid method in the class service. Is called whenever the customer pays its unpaid expenses (the ones that he postponed to the end of the month)
	*
	*/
	void SetAllServicesAsPaid();
	/**
	*
	* @brief Decrements the points that the customer has alread scored in the company.
	* @param points The points to sub to the customer's current points.
	*
	*/
	void SubPoints(unsigned int points);
	/**
	*
	* @brief Is called whenever a customer makes a payment and is reponsible to handle it and show the discounts that the customer has the right to (if applicable). It is only implemented in the derived classes to be able to distinguish between particular and business customers in terms of discounts. (It is a pure virtual function)
	* @return The price that the customer has to pay fro the service.
	*
	*/
	virtual float MakePayment() = 0;
	/**
	*
	* @brief Is called whenever a customer makes a payment and is responsible for checking if the customer has any unpaid expenses. If yes, asks the user if the customer will pay them or not and informs the function that called it, by the return value
	* @return returns true if the either the customer had no unpaid expenses or he paid them; returns false if the customer had unpaid expenses and did not pay them.
	*
	*/
	bool VerifyUnpaidAmount();
	/**
	*
	* @brief Is called whenever the discounts of any type for any type of customer are disabled and resets the variables respecting to that discount type of that customer type to their default values (the values they assume when the discounts are disabled). It is only implemented in the derived classes to be able to distinguish between particular and business customers in terms of discounts. (It is a pure virtual function)
	*
	*/
	virtual void ResetDisabledDiscounts() = 0;
	/**
	*
	* @brief Postpones the last service payment until the end of the month. It sets the service as unpaid and increments the customer unpaid amount.
	* @param price The price of the service that will be postponed to the end of the month (the amount that will be added to the unpaid amount of the customer).
	*
	*/
	void PostPoneLastServicePayment(float price);
	/**
	*
	* @brief Updates the information used to determine if the customer whether the customer has the right to a discount or not based on the current date (windows date). If the discount is not valid anymore, invalidates it, setting the atributes to their default values.
	*
	*/
	void UpdateDiscount();
};

/**
*
* @brief Represents a particular customer. Stores all the information regarding a particular customer
*
*/

class ParticularCustomer : public Customer
{
protected:
	/**
	*
	* @brief Stores the current state of the minimum trips discount for particular customers (that allows them to enjoy free trips). It is set to true if this type of discount is enbaled and false if it is disabled.
	*
	*/
	static bool min_trips_discount;
	/**
	*
	* @brief Stores the current state of the minimum paid discount for particular customers (that allows them to enjoy vouchers). It is set to true if this type of discount is enbaled and false if it is disabled.
	*
	*/
	static bool min_paid_discount;
	/**
	*
	* @brief Stores the minimum value of trips necessary for the particular customer to have the right to enjoy a free trip. If this type of discount is disabled for this type of customer, this variable is set to 0 (zero).
	*
	*/
	static unsigned int min_trips_for_discount;
	/**
	*
	* @brief Stores the minimum value of invested amount necessary for the particular customer to have the right to enjoy a voucher. If this type of discount is disabled for this type of customer, this variable is set to 0 (zero).
	*
	*/
	static unsigned int min_paid_for_discount;
	/**
	*
	* @brief Stores the minimum time (in seconds) without making any trip for the particular customer to be considered inactive and to be put in the inactive customers unordered_set
	*
	*/
	static time_t min_time_to_inactive;
public:
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameters.
	*
	*/
	ParticularCustomer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount);
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameters.
	*
	*/
	ParticularCustomer(string name, string adress, unsigned int NIF);
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameter.
	*
	*/
	ParticularCustomer(unsigned int id);
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameter.
	*
	*/
	ParticularCustomer(string name);
	/**
	*
	* @brief Is called whenever a particular customer makes a payment and is reponsible to handle it and show the discounts that the customer has the right to (if applicable).
	* @return The price that the customer has to pay for the service.
	*
	*/
	virtual float MakePayment();
	/**
	*
	* @brief Resets the information regarding currently disabled discounts for particular customers.
	*
	*/
	virtual void ResetDisabledDiscounts();
	static bool IsMinTripsDiscount();
	static bool IsMinPaidDiscount();
	static unsigned int GetMinPaidForDiscount();
	static unsigned int GetMinTripsForDiscount();
	static void SetMinPaidForDiscount(unsigned int min_paid_for_discount);
	static void SetMinPaidDiscount(bool min_paid_discount);
	static void SetMinTripsForDiscount(unsigned int min_trips_for_discount);
	static void SetMinTripsDiscount(bool min_trips_discount);
	static time_t GetMinTimeToInactive();
	static void SetMinTimeToInactive(time_t min_time_to_inactive);
};

/**
*
* @brief Represents a business customer. Stores all the information regarding a business customer
*
*/

class BusinessCustomer : public Customer
{
protected:
	/**
	*
	* @brief Stores the current state of the minimum trips discount for business customers (that allows them to enjoy free trips). It is set to true if this type of discount is enabled and false if it is disabled.
	*
	*/
	static bool min_trips_discount;
	/**
	*
	* @brief Stores the current state of the minimum paid discount for business customers (that allows them to enjoy vouchers). It is set to true if this type of discount is enabled and false if it is disabled.
	*
	*/
	static bool min_paid_discount;
	/**
	*
	* @brief Stores the minimum value of trips necessary for the business customer to have the right to enjoy a free trip. If this type of discount is disabled for this type of customer, this variable is set to 0 (zero).
	*
	*/
	static unsigned int min_trips_for_discount;
	/**
	*
	* @brief Stores the minimum value of invested amount necessary for the business customer to have the right to enjoy a voucher. If this type of discount is disabled for this type of customer, this variable is set to 0 (zero).
	*
	*/
	static unsigned int min_paid_for_discount;
	/**
	*
	* @brief Stores the minimum time (in seconds) without making any trip for the business customer to be considered inactive and to be put in the inactive customers unordered_set
	*
	*/
	static time_t min_time_to_inactive;
public:
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameters.
	*
	*/
	BusinessCustomer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount);
	/**
	*
	* @brief Invokes the constructor of the base class with the exact same parameters.
	*
	*/
	BusinessCustomer(string name, string adress, unsigned int NIF);
	/**
	*
	* @brief Is called whenever a business customer makes a payment and is reponsible to handle it and show the discounts that the customer has the right to (if applicable).
	* @return The price that the customer has to pay for the service.
	*
	*/
	virtual float MakePayment();
	/**
	*
	* @brief Resets the information regarding currently disabled discounts for business customers.
	*
	*/
	virtual void ResetDisabledDiscounts();
	static bool IsMinPaidDiscount();
	static bool IsMinTripsDiscount();
	static unsigned int GetMinPaidForDiscount();
	static unsigned int GetMinTripsForDiscount();
	static void SetMinPaidForDiscount(unsigned int min_paid_for_discount);
	static void SetMinPaidDiscount(bool min_paid_discount);
	static void SetMinTripsForDiscount(unsigned int min_trips_for_discount);
	static void SetMinTripsDiscount(bool min_trips_discount);
	static time_t GetMinTimeToInactive();
	static void SetMinTimeToInactive(time_t min_time_to_inactive);
};

/**
*
* @brief Represents an unregistered customer. Does not have aditional attributes
*
*/

class UnRegisteredCustomer : public Customer
{
public:
	UnRegisteredCustomer();
	/**
	*
	* @brief Is called whenever an unregistered customer makes a payment and is reponsible to handle it. Does not handle any discounts, because no discounts are applicable for any unregistered customer.
	* @return The price that the customer has to pay for the service.
	*
	*/
	virtual float MakePayment();
	/**
	*
	* @brief Is only implemented in the derived classes ParticularCustomer and BusinessCustomer. Does not make sense to be implemented in this class, because unregistered customers don't have the right to 
	*
	*/
	virtual void ResetDisabledDiscounts() {};
};


/**
*
* @brief This struct contains all the necessary functions (implemented as operator() overloads) required to implement a hash table (unordered_set) of Customer objects.
*
*/
struct CustomerH
{
	/**
	*
	* @brief Hasher function. The hash code of a Customer is given by its Id. The id is an guaranteed unique identifier of a Customer. This makes the hash function very efficient, since, within the referred context, it guarantees that callisions will never occur in the hash table.
	* @param cust The Customer of which to calculate the hash of.
	* @return The hash code associated with the Customer it recieves as parameter (its Id).
	*
	*/
	int operator()(const Customer *cust) const
	{
		return cust->GetId();
	}
	/**
	*
	* @brief KeyEqual function. The function checks whether two Customer objects are equal. They are equal if their id's are the same, becasue the Id is an unique identifier.
	* @param cust1 The first Customer object to be compared.
	* @param cust2 The second Customer object to be compared.
	* @return a bool value indicating whether the first is equal to the second or not.
	*
	*/
	bool operator()(const Customer *cust1, const Customer *cust2) const
	{
		if (cust1->GetId() == cust2->GetId())
			return true;
		else
			return false;
	}
};