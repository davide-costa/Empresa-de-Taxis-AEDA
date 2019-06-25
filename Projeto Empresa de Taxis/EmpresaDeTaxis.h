/**
*
* @file
* @brief Contains the System Class declaration.
*
*/

#pragma once


#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <queue>
#include "BST.h"

#include "Customer.h"
#include "TimeStamp.h"
#include "Date.h"
#include "Service.h"
#include "Taxi.h"
#include "Invoice.h"


typedef unordered_set<Customer*, CustomerH, CustomerH> CustomerHash;

/**
*
* @brief Represents the Taxi Company. It is a system class (the class that contains all the necessary information for representing the company (as attibutes) and all the actions that are performed in runtime (as methods).
*
*/

class EmpresaDeTaxis
{
	/**
	*
	* @brief Outputs the company statistics to an ostream
	*
	*/
	friend ostream &operator<<(ostream &os, const EmpresaDeTaxis &company);
private:
	/**
	*
	* @brief The value of this variable indicates if the particular customers were changed. The program uses it to know if it needs to save them to the file (only saves them if they were changed). It is set to true if they were changed during runtime; otherwise, remains false (the value to which it is set when the program starts)
	*
	*/
	bool customers_p_changed;
	/**
	*
	* @brief The value of this variable indicates if the business customers were changed. The program uses it to know if it needs to save them to the file (only saves them if they were changed). It is set to true if they were changed during runtime; otherwise, remains false (the value to which it is set when the program starts)
	*
	*/
	bool customers_b_changed;
	/**
	*
	* @brief The value of this variable indicates if the services were changed. The program uses it to know if it needs to save them to the file (only saves them if they were changed). It is set to true if they were changed during runtime; otherwise, remains false (the value to which it is set when the program starts)
	*
	*/
	bool services_changed;
	/**
	*
	* @brief The value of this variable indicates if the taxis were changed. The program uses it to know if it needs to save them to the file (only saves them if they were changed). It is set to true if they were changed during runtime; otherwise, remains false (the value to which it is set when the program starts)
	*
	*/
	bool taxis_changed;
	/**
	*
	* @brief The value of this variable indicates if the drivers were changed. The program uses it to know if it needs to save them to the file (only saves them if they were changed). It is set to true if they were changed during runtime; otherwise, remains false (the value to which it is set when the program starts)
	*
	*/
	bool drivers_changed;
	/**
	*
	* @brief The name of the taxi company that was read from the user in the beginning of the program.
	*
	*/
	string company_name;
	/**
	*
	* @brief The name of the file that stores the particular customers information.
	*
	*/
	string customers_p_fn;
	/**
	*
	* @brief The name of the file that stores the business customers information.
	*
	*/
	string customers_b_fn;
	/**
	*
	* @brief The name of the file that stores the services information.
	*
	*/
	string services_fn;
	/**
	*
	* @brief The name of the file that stores the taxis information.
	*
	*/
	string taxis_fn;
	/**
	*
	* @brief The name of the file that stores the drivers information.
	*
	*/
	string drivers_fn;
	/**
	*
	* @brief The name of the temporary file that stores the particular customers information. This is used to save them to a temporary file first and then, if no error ocurred, set its name as the original file name. Thus, avoiding loosing the information contained in the original file (by openning it as an ofstream, all the content on it is erased).
	*
	*/
	string customers_p_tmp_fn;
	/**
	*
	* @brief The name of the temporary file that stores the business customers information. This is used to save them to a temporary file first and then, if no error ocurred, set its name as the original file name. Thus, avoiding loosing the information contained in the original file (by openning it as an ofstream, all the content on it is erased).
	*
	*/
	string customers_b_tmp_fn;
	/**
	*
	* @brief The name of the temporary file that stores the services information. This is used to save them to a temporary file first and then, if no error ocurred, set its name as the original file name. Thus, avoiding loosing the information contained in the original file (by openning it as an ofstream, all the content on it is erased).
	*
	*/
	string services_tmp_fn;
	/**
	*
	* @brief The name of the temporary file that stores the taxis information. This is used to save them to a temporary file first and then, if no error ocurred, set its name as the original file name. Thus, avoiding loosing the information contained in the original file (by openning it as an ofstream, all the content on it is erased).
	*
	*/
	string taxis_tmp_fn;
	/**
	*
	* @brief The name of the temporary file that stores the drivers information. This is used to save them to a temporary file first and then, if no error ocurred, set its name as the original file name. Thus, avoiding loosing the information contained in the original file (by openning it as an ofstream, all the content on it is erased).
	*
	*/
	string drivers_tmp_fn;
	/**
	*
	* @brief The value of this variable indicates the number of particular customers the company currently has.
	*
	*/
	unsigned int num_of_p_customers;
	/**
	*
	* @brief The value of this variable indicates the number of business customers the company currently has.
	*
	*/
	unsigned int num_of_b_customers;
	/**
	*
	* @brief The value of this variable indicates the number of services the company currently has.
	*
	*/
	unsigned int num_of_services;
	/**
	*
	* @brief The value of this variable indicates the number of drivers the company currently has.
	*
	*/
	unsigned int num_of_drivers;
	/**
	*
	* @brief This vector contains pointers to all the customers in the company, which are particular and business.
	*
	*/
	vector<Customer *> customers;
	/**
	*
	* @brief This unordered set contains pointers to the customers of the company, which hadn´t used the company services for a long time.
	*
	*/
	CustomerHash inactive_customers;
	/**
	*
	* @brief This vector contains pointers to all the taxis in the company.
	*
	*/
	vector<Taxi *> taxis;
	/**
	*
	* @brief This BST contains pointers to all the invoices in the company.
	*
	*/
	BST<Invoice> invoices;
	/**
	*
	* @brief This queue contains pointers to customers that made a request for a service, sorted by the order in which the requests were made.
	*
	*/
	queue<Customer*> requests_queue;
	/**
	*
	* @brief This priority_queue contains Taxis that are in the active, sorted by the time they take to finish the current service. The costumer in the top of the queue is always the one that will take less time to be available to perform a service.
	*
	*/
	 priority_queue<TaxiPtr> taxis_queue;
public:
	/**
	*
	* @brief This is an exception class. It is thrown when an error is encountered while parsing the file.
	*
	*/
	class ErrorParsingFile
	{
		/**
		*
		* @brief Outputs the error message (string) to an ostream.
		*
		*/
		friend ostream &operator<<(ostream &os, const ErrorParsingFile &error);
	private:
		/**
		*
		* @brief An error message that contains information regarding the error that ocurred while parsing the file.
		*
		*/
		string error_msg;
		/**
		*
		* @brief The name of the file in which the error ocurred while parsing.
		*
		*/
		string file_name;
	public:
		/**
		*
		* @brief Creates a new ErrorParsingFile object based on information of the context when the error ocurred.
		*
		*/
		ErrorParsingFile(const string &error_msg, const string &file_name);
		const string &GetErrorMsg() const;
		const string &GetFileName() const;
	};
	/**
	*
	* @brief This is an exception class. It is thrown when an error is encountered when getting the local system time.
	*
	*/
	class ErrorGettingLocalTime {};
	/**
	*
	* @brief Creates a new company object based on the information the user introduces in the beginning of the program. Receives only some attributes of the company because the remaining ones will be calculated later and others will be added later in runtime.
	*
	*/
	EmpresaDeTaxis(string company_name, string customers_p_fn, string customers_b_fn, string services_fn, string taxis_fn, string drivers_fn);
	const string &GetCompanyName();

	/**
	*
	* @brief Computes the temporary file names and sets the respective attributes with the result of that computation.
	*
	*/
	void ComputeTmpFileNames();
	/**
	*
	* @brief Parses the contents of the beginning of the particular customers file (the number of customers in the file and the static attributes) and then calls the ParseParticularCustomers with call_id of 0. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param customers_fs the particular customers ifstream to extract the information from.
	*
	*/
	void ParseParticularCustomers(ifstream &customers_fs);
	/**
	*
	* @brief Parses the contents of the beginning of the business customers file (the number of customers in the file and the static attributes) and then calls the ParseParticularCustomers with call_id of 1. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param customers_fs the business customers ifstream to extract the information from.
	*
	*/
	void ParseBusinessCustomers(ifstream &customers_fs);
	/**
	*
	* @brief Parses the contents of the remaining lines of the customers file. This function is called by both the ParseParticularCustomers and the ParseBusinessCustomers functions and is able to know which one called it by the call id. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param customers_fs the customers' (that can be either particular or business) ifstream to extract the information from.
	* @param num_of_customers the number of customers that has been extracted either by ParseParticularCustomers or ParseBusinessCustomers function.
	* @param customers_fn The name of the file that contains the customers (that can be either particular or business).
	* @param call_id a number that the function uses to be able to determine if it was called by the ParseParticularCustomers, in which case this parameter is, 0 or by ParseBusinessCustomers, in which case this parameter is 1.
	*
	*/
	void ParseCustomers(ifstream &customers_fs, int num_of_customers, string customers_fn, int call_id);
	/**
	*
	* @brief Parses the contents of the services file. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param services_fs the services ifstream to extract the information from.
	*
	*/
	void ParseServices(ifstream &services_fs);
	/**
	*
	* @brief Parses the contents of the taxis file. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param taxis_fs the taxis ifstream to extract the information from.
	*
	*/
	void ParseTaxis(ifstream &taxis_fs);
	/**
	*
	* @brief Parses the contents of the drivers file. Extracts all information from the ifstream it receives as parameter. Verifies all kinds of errors in the files. Always checks the state of the .fail() flag of the stream after extracting anything from it. Checks if the data is valid (in the context), for example: when extracting a date or timestamp, it verifies if the Date or TimeStamp does not evaluate to a time after the time of the system (Windows OS). Thus, avoiding any incoherence during runtime. All kinds of other verifications are also performed.
	* @param drivers_fs the drivers ifstream to extract the information from.
	*
	*/
	void ParseDrivers(ifstream &drivers_fs);

	/**
	*
	* @brief Verifies if the object pointed to by the parameter it recieves is a Particular Customer.
	* @param customer the pointer to the customer which to verify if is Particular.
	* @return true if the customer is particular; false otherwise
	*
	*/
	bool IsParticularCustomer(Customer* customer) const;
	/**
	*
	* @brief Adds a Customer to the company, based on user input. Reads all the necessary info from the user and validates everything it reads, by using the functions declared in utils.h file. Gets the registration date of the customer from Windows OS (the date in that moment the customer was added).
	*
	*/
	void AddCustomer();
	/**
	*
	* @brief Removes a Customer from the company, based on its id. Reads the id of the customer to remove from the user and validates it, i. e., if the id introduced doesn't exist, keeps asking for a valid id. This verification is done by the function ReadCustomerId.
	*
	*/
	void RemoveCustomerById();
	/**
	*
	* @brief Removes a Customer from the company, based on its name. Reads the name of the customer to remove from the user and validates it, i. e., if the name introduced doesn't exist, keeps asking for a valid name. This verification is done by the function ReadCustomerName. If there are multiple customers with the given name, shows the list of those customers and prompts the user to introduce an id of the list.
	*
	*/
	void RemoveCustomerByName();
	/**
	*
	* @brief Erases a Customer from the company. This function is called by the functions RemoveCustomerById and RemoveCustomerByName and is responsible for completing their work.
	* @param cust_idx the index of the customer (in the vector of Customer *) that should be erased from that vector.
	* @param it the iterator to the customer (in the hash table) that should be erased from that hash table.
	*
	*/
	void EraseCustomer(int cust_idx, CustomerHash::iterator it);
	/**
	*
	* @brief Changes a customer's adress (the place where he lives), based on its id. Reads the id of the customer to remove from the user and validates it, i. e., if the id introduced doesn't exist, keeps asking for a valid id. This verification is done by the function ReadCustomerId.
	*
	*/
	void ChangeCustomerAdressById();
	/**
	*
	* @brief Changes a customer's adress (the place where he lives), based on its name. Reads the name of the customer to remove from the user and validates it, i. e., if the name introduced doesn't exist, keeps asking for a valid name. This verification is done by the function ReadCustomerName. If there are multiple customers with the given name, shows the list of those customers and prompts the user to introduce an id of the list.
	*
	*/
	void ChangeCustomerAdressByName();
	/**
	*
	* @brief Changes a customer's adress (the place where he lives).
	* @param cust_idx the index of the customer (in the vector of Customer *) whose adress should be changed from that vector.
	* @param it the iterator to the customer (in the hash table) whose adress should be changed from that hash table.
	*
	*/
	void ChangeCustomerAdress(int cust_idx, CustomerHash::iterator it);


	/**
	*
	* @brief Adds a new request to the company. Is called when the request was made for a registered customer. Reads the id of a customer to which the request should be added and calls the function AddRequest with the index of the customer that wishes to make a trip
	*
	*/
	void AddRequestToRegisteredCustomer();
	/**
	*
	* @brief Adds a new service to the company. The call_id allows it to distinguish if it was called to a add a service to a registered or non-registered customer. Calls the function that is responsible to calculate the price of the service and the function that is able to handle the payment for a customer.
	* @param call_id Is 0 if the function was called to add a service to a registered customer; 1 if the function was called to add a service to an unregistered customer
	* @param customer_idx The index of the customer (in the vector of Customer *) to which the service was provided.
	*
	*/
	void AddRequest(unsigned int customer_idx);
	/**
	*
	* @brief Processes all waiting requests made by the customers. When a customer makes a request, the program checks if it can be processed (if there are available taxis). The requests that don't find an available taxi, are put in a queue. This functions processes all the requests in the queue it can (as much as the currentlt available taxis).
	*
	*/
	void ProcessAllWaitingRequests();
	/**
	*
	* @brief Adds a new service to the company, the service that was in the beginning of the queue request_queue. The customer that made the request allows to distinguish if it was called to a add a service to a registered or non-registered customer. Calls the function that is responsible to calculate the price of the service and the function that is able to handle the payment for a customer.
	*
	*/
	void AddService(Customer *customer, Taxi *taxi);




	/**
	*
	* @brief Selects the payment method based on the call id it receives. If is a unregistered customer, the available methods are numeral or ATM. If the customer is registered, the available methods are numeral, ATM, credit card, or postpone to the end of the month. The call_id allows the function to be able to distinguish if the payment is to be made to a registered or unregistered customer.
	* @param customer_idx The index of the customer (in the vector of Customer *) to which the service was provided.
	* @param price The price that the customer paid for the service.
	*
	*/
	void SelectPaymentMethod(Customer *customer, float price);
	/**
	*
	* @brief Outputs the final price of the service (without any tax because it was a payment in numeral).
	* @param price The price that the customer paid for the service.
	*
	*/
	void PayInCash(float price);
	/**
	*
	* @brief Outputs the final price of the service (without any tax because it was a payment with ATM).
	* @param price The price that the customer paid for the service.
	*
	*/
	void PayWithATM(float price);
	/**
	*
	* @brief Outputs the final price of the service (with a tax of 5% because it was a payment with credit card).
	* @param price The price that the customer paid for the service before the tax was applied.
	*
	*/
	void PayWithCreditCard(float price);
	/**
	*
	* @brief Outputs the final price of the service (with a tax of 2% because the payment was postponed to the end of the month).
	* @param price The price that the customer paid for the service before the tax was applied.
	*
	*/
	void PostponePayment(Customer *customer, float price);
	/**
	*
	* @brief Liquidates the unpaid amount of a customer (the amount that he has postponed to the end of the month). Reads the customer id and sets all of it services to paid state and resets it unpaid amount to 0 (zero).
	*
	*/
	void LiquidateCustAmount();
	/**
	*
	* @brief Adds an invoice to the company. This is an internal process, that is genrated based on information already in the system
	*
	*/
	void AddInvoice(const Customer *customer, unsigned int service_idx);
	/**
	*
	* @brief Adds a taxi to the company. Asks the user to introduce some attributes that the taxi has and sets the others based on internal information. Validates each user input and checks if the lincense plate introduced is not already assigned to another taxi to avoid any error by negligence.
	*
	*/
	void AddTaxi();
	/**
	*
	* @brief Removes a Taxi from the company, based on its license plate. Reads the license plate of the taxi to remove from the user and validates it, i. e., if the introduced license plate is not valid or it doesn't exist, keeps asking for a valid license plate. This verification is done by the function ReadCustomerName.
	*
	*/
	void RemoveTaxiByLicensePlate();
	/**
	*
	* @brief Removes a Taxi from the company, based on its id. Reads the id of the taxi to remove from the user and validates it, i. e., if the introduced id doesn't exist, keeps asking for a valid id. This verification is done by the function ReadCustomerName.
	*
	*/
	void RemoveTaxiById();
	/**
	*
	* @brief Erases a Taxi from the company, based on its index. This function is called by the functions RemoveTaxiByLicensePlate and RemoveTaxiById.
	* @param taxi_idx The index of the taxi (in the vector of taxis) to remove.
	*
	*/
	void EraseTaxi(unsigned int taxi_idx);
	/**
	*
	* @brief Add's a driver to a taxi. Before adding a driver, all the taxis available are displayed and then the user need's to chose which one to associate the driver with.
	*
	*/
	void AddDriver();
	/**
	*
	* @brief Calls the function that changes a drivers adress, which is searched by his id.
	* 
	*/
	void ChangeDriverAdressById();
	/**
	*
	* @brief Calls the function that changes a drivers adress, which is searched by his name. If there there are multiple drivers with the same name, they are displayed and the user needs to chose which one to change using his id.
	*
	*/
	void ChangeDriverAdressByName();
	/**
	*
	* @brief Function that changes the drivers adress.
	* @param taxi_idx variable that contains the index in the vector of taxis which is used to change the wanted driver's adress. The variable value is changed by the functions that call this one.
	*
	*/
	void ChangeDriverAdress(unsigned int taxi_idx);
	/**
	*
	* @brief Calls the function that removes a driver, which is searched by his id.
	*
	*/
	void RemoveDriverById();
	/**
	*
	* @brief Calls the function that removes a driver, which is searched by his name. If there there are multiple drivers with the same name, they are displayed and the user needs to chose which one to remove using his id.
	*
	*/
	void RemoveDriverByName();
	/**
	*
	* @brief Function that removes the drivers.
	* @param taxi_idx variable that contains the index in the vector of taxis which is used to remove the wanted driver. The variable value is changed by the functions that call this one.
	*
	*/
	void EraseDriver(unsigned int taxi_idx);
	/**
	*
	* @brief Displays the information related to all of the customers (in the active customers vector and the inactive customers hash table), sorted by their name (alphabetically) (the same order as they are kept in vector in program runtime).
	*
	*/
	void DisplayAllCustomers() const;
	/**
	*
	* @brief Displays the information related to all of the customers (in the active customers vector and the inactive customers hash table), sorted by their registration date (the date when they joined the company). (Effectively calls function DisplayAllCustomersInSpecificOrder with the argument CompareCustomersRegistDates, which will call the sort function with the same argument as the comparison predicate).
	*
	*/
	void DisplayAllCustomersSortedByRegistDate() const;
	/**
	*
	* @brief Displays the information related to all of the customers (in the active customers vector and the inactive customers hash table), sorted by the points they have scored in the company. (Effectively calls function DisplayAllCustomersInSpecificOrder with the argument CompareCustomersPoints, which will call the sort function with the same argument as the comparison predicate).
	*
	*/
	void DisplayAllCustomersSortedByPoints() const;
	/**
	*
	* @brief Displays the information related to all of the customers (in the active customers vector and the inactive customers hash table), sorted by a specific order, indicated by the fucntion it recieves as parameter. It recieves a template function as parameter which will then be passed as parameter to the sort function. The sort function will use that to compare the customers and be able to tell if one is less than the other and, therefore, sort them.
	* @param comp A template function that compares two customers (recieving two Customer * as parameters), used to sort the customers and display them in the intended order.
	*
	*/
	template<class Compare>
	void DisplayAllCustomersInSpecificOrder(Compare comp) const;
	/**
	*
	* @brief Displays the customers that have the highest un paid amount, i.e., the amount they have accumulated of expenses that they haev postponed to the end of the month. The function currently displays the 10 customers with highest unpaid amount (if there are enough to display), but it can easily be modified to display a different number of customers (instead of 10), just by changing the value of a variable, in the implementation.
	*
	*/
	void DisplayBottomCustomersSortedByUnpaidAmount() const;
	/**
	*
	* @brief Displays the information related to a customer which was searched by his id.
	*
	*/
	void DisplayCustomerById() const;
	/**
	*
	* @brief Displays the information related to a customer which was searched by his name. If there are two or more clients with the same name, all of them are displayed.
	*
	*/
	void DisplayCustomerByName() const;
	/**
	*
	* @brief Displays all of the services present in the services vector.
	*
	*/
	void DisplayAllServices() const;
	/**
	*
	* @brief Displays a service which was searched by it's id.
	*
	*/
	void DisplayServiceById() const;
	/**
	*
	* @brief Displays all the services of a customer, which was searched by his name. If there are multiple clients with the same name, their services are displayed as well.
	*
	*/
	void DisplayServicesByName() const;
	/**
	*
	* @brief Displays all the services in a date (introduced by the user and properly validated).
	*
	*/
	void DisplayServicesByDate() const;
	/**
	*	
	* @brief Displays the information related to all services between two dates (introduced by the user and properly validated).
	*
	*/
	void DisplayServicesBetweenDates() const;
	/**
	*
	* @brief Displays the information related to all of the taxis in the taxi vector.
	*
	*/
	void DisplayAllTaxis() const;
	/**
	*
	* @brief Displays the information related to a taxi, which was searched by it's id.
	*
	*/
	void DisplayTaxiById() const;
	/**
	*
	* @brief Displays the information related to a taxi, which was searched by it's license plate.
	*
	*/
	void DisplayTaxiByLicensePlate() const;
	/**
	*
	* @brief Displays the information related to all of the drivers in the driver vector.
	*
	*/
	void DisplayAllDrivers() const;
	/**
	*
	* @brief Displays the information related to a driver, which was searched by it's id.
	*
	*/
	void DisplayDriverById() const;
	/**
	*
	* @brief Displays the information related to a driver, which was searched by it's name. If there are multiple drivers with the same name, their information is displayed as well.
	*
	*/
	void DisplayDriverByName() const;

	/**
	*
	* @brief Updates all customers states based on the time of his last service on the company. If it was more than min_time_to_inactive time ago, the customer becomes inactive, and is moved from the vector of active customers to the hash table of inactive customers.
	*
	*/
	void UpdateAllCustsState();
	/**
	*
	* @brief Moves a Customer to the hash table of inactive customers. Eliminates the customer from the vector of active customers.
	* @param cust_idx the index of customer to be erased in the vector of customers
	*
	*/
	void MoveCustomerToHash(unsigned int cust_idx);
	/**
	*
	* @brief Moves a Customer to the vector of active customers. Eliminates the customer from the hash table of inactive customers.
	* @param customer the customer* to be moved to the vector of active customers.
	* @return The index (of the vector) of active customers where the customer was inserted
	*/
	unsigned int MoveCustomerToVector(Customer *customer);
	/**
	*
	* @brief Adds a Customer to the hash hCustomers, if the customer doesn´t do trip in the campany for a long time.
	*
	*/
	void AddCustomerToHash(Customer *customer);
	/**
	*
	* @brief Updates the information of all customers used to determine if either the customers have the right to a discount or not based on the current date (windows date). If the discount is not valid anymore, invalidates it, setting the atributes to their default values.
	*
	*/
	void UpdateAllCustsDiscounts();
	/**
	*
	* @brief Resets the information regarding currently disabled discounts for all customers.
	*
	*/
	void ResetAllCustsDiscounts();
	/**
	*
	* @brief Toggles on or off, the minimum paid amount discount system for the particular customers.
	*
	*/
	void ToggleCustPMinPaidDiscount();
	/**
	*
	* @brief Toggles on or off, the minimum number of trips discount system for the particular customers.
	*
	*/
	void ToggleCustPMinTripsDiscount();
	/**
	*
	* @brief Toggles on or off, the minimum paid amount discount system for the business customers.
	*
	*/
	void ToggleCustBMinPaidDiscount();
	/**
	*
	* @brief Toggles on or off, the minimum number of trips discount system for the business customers.
	*
	*/
	void ToggleCustBMinTripsDiscount();
	/**
	*
	* @brief Replaces the minimum paid amount to get a discount, for the particular customers. The new amount is read from the user. 
	*
	*/
	void SetCustPMinPaidForDiscount();
	/**
	*
	* @brief Replaces the minimum number of trips to get a discount, for the particular customers. The new number is read from the user.
	*
	*/
	void SetCustPMinTripsForDiscount();
	/**
	*
	* @brief Replaces the minimum number of days for the customer to become inactive, for the particular customers. The new number is read from the user.
	*
	*/
	void SetCustPMinTimeToInactive();
	/**
	*
	* @brief Replaces the minimum paid amount to get a discount, for the business customers. The new amount is read from the user.
	*
	*/
	void SetCustBMinPaidForDiscount();
	/**
	*
	* @brief Replaces the minimum number of trips to get a discount, for the business customers. The new number is read from the user.
	*
	*/
	void SetCustBMinTripsForDiscount();
	/**
	*
	* @brief Replaces the minimum number of days for the customer to become inactive, for the business customers. The new number is read from the user.
	*
	*/
	void SetCustBMinTimeToInactive();

	/**
	*
	* @brief Reads an existing customer id from the user and validates it, i. e., if the id introduced doesn't exist, keeps asking for a valid id.
	* @param idx the index of the customer indicated by user
	* @param it the iterator to the customer indicated by the user, that will point past the end of CustomerHash
	*/
	void ReadCustomerId(unsigned int &idx, CustomerHash::iterator &it) const;
	/**
	*
	* @brief Reads an existing customer's name from the user and validates it, i. e., if the name introduced doesn't exist, keeps asking for a valid name. Since multiple customers may have the same name, there can be multiple indexes repecting to the name introduced. Since the vector of Customer * is sorted by the customers names, the customers with the same name are always in consecutive vector indexes. This function returns by reference the two indexes (the bounds) in which the customers with the same names are within. If there is only one customer with that name, the bounds are equal.
	* @param lower_idx The lower bound index, i. e., the index to the first Customer * (with the name read from the user) to appear in the vector of Customer * (returned by reference).
	* @param upper_idx The upper bound index, i. e., the index to the last Customer * (with the name read from the user) to appear in the vector of Customer * (returned by reference).
	* @param cust_its vector with iterators to the customers (in the customers hash table) with the name read from the user. (returned by reference).
	*
	*/
	void ReadCustomerName(unsigned int &initial_idx, unsigned int &final_idx, vector<CustomerHash::iterator> &cust_its) const;
	
	/**
	*
	* @brief Reads an existing service's id from the user and validates it, i. e., if the id introduced doesn't exist, keeps asking for a valid id. Since the vector of services is inside each customer, it must return the index of a customer (in the vector of Customer *) to which the service's id respects to and the index of the service (in the vector of Services that is inside a Customer)
	* @param customer_idx The index of the customer (in the vector of active customers) to which the service (that respects to the id introduced by the user) was provided to (returns by reference).
	* @param it The iterator of the customer (in the hash table of inactive customers) to which the service (that respects to the id introduced by the user) was provided to (returns by reference).
	* @param service_idx The index of the service (in the vector of services) to which the id respects.
	*
	*/
	void ReadServiceId(int &customer_idx, CustomerHash::iterator &it, unsigned int &service_idx) const;
	/**
	*
	* @brief Reads an existing invoice's id from the user and validates it, i.e., if the id introduced doesn't exist, keeps asking for a valid id.
	*
	*/
	BSTItrIn<Invoice> EmpresaDeTaxis::ReadInvoiceId() const;
	/**
	*
	* @brief Reads an existing taxi's id from the user and validates it, i. e., if the id introduced doesn't exist, keeps asking for a valid id.
	*
	*/
	unsigned int ReadTaxiId() const;
	/**
	*
	* @brief Reads an existing taxi's license plate from the user and validates it, i. e., checks if it is valid and if a taxi with that license plate exists, and keeps asking for a valid license plate. Returns it by reference.
	* @param plate The license plate read from the user (returns by reference).
	* @return The index of the Taxi (in the vector of taxis) with the given license plate.
	*
	*/
	unsigned int ReadTaxiLicensePlate(LicensePlate &plate) const;
	/**
	*
	* @brief checks if there is a driver with the id read from the user.
	* @return the index of the taxi to which the driver is assigned.
	*
	*/
	unsigned int ReadDriverId() const;
	/**
	*
	* @brief checks if there is a driver with the name read from the user.
	* @param drivers_indexes Vector used to contain all the drivers indexes (indexes to the vector of taxis) with the same name because there can be multiple customersw with the same name.
	*
	*/
	void ReadDriverName(vector<unsigned int> &drivers_indexes) const;

	/**
	*
	* @brief Searches in the vector of active customers and in the hash table of inactive customers for a customer with the same id it receives as parameter. (Effectively calls function SearchForActiveCustId and, if not found, calls function SearchForInactiveCustId.)
	* @param id The id of the customer to search for
	* @param idx The index of the customer with the same id it recieves as parameter (returns by reference). (If not found in the vector of active customers, is set to -1).
	* @param it The iterator to the customer with the same id it recieves as parameter (returns by reference). (If not found in the hash table of inactive customers, is set to past the end (iterator that points to nothing)).
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForCustId(unsigned int id, int &idx, CustomerHash::iterator &it) const;
	/**
	*
	* @brief Searches in the vector of active customers for a customer with the same id it receives as parameter using a sequential search algorithm (can't use binary search since it is not sorted by ids, but by names instead).
	* @param id The id of the customer to search for
	* @return If the customer with the given id was found, returns its index in the vector of Customer *; if it was not found, returns -1.
	*
	*/
	int SearchForActiveCustId(unsigned int id) const;
	/**
	*
	* @brief Searches in the inactive customers hash table (undorered_set) for a customer with the same id it receives as parameter using a sequential search algorithm.
	* @param id The id of the customer to search for
	* @return If the customer with the given id was found, returns the iterator to the Customer in the inactive customers has table ; if it was not found, an iterator past the end of the table.
	*
	*/
	CustomerHash::iterator SearchForInactiveCustId(unsigned int id) const;
	/**
	*
	* @brief Searches in the vector of active customers and in the hash table of inactive customers for a customer with the same name it receives as parameter. (Effectively calls function SearchForActiveCustName and, if not found, calls function SearchForInactiveCustName.)
	* @param name The customer name to search for.
	* @param lower_idx The lower bound index, i. e., the index to the first Customer * with the given name to appear in the vector of Customer * (returned by reference). This is set to -1 if no customer with the given name was found in the vector of customers
	* @param upper_idx The upper bound index, i. e., the index to the last Customer * with the given name to appear in the vector of Customer * (returned by reference). This is set to -1 if no customer with the given name was found in the vector of customers
	* @param cust_its vector with iterators to the customers (in the customers hash table) with the given name. (returned by reference). This is set to empty if no customer with the given name was found in the hash table of inactive customers.
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForCustName(string name, int &lower_idx, int &upper_idx, vector<CustomerHash::iterator> &cust_its) const;
	/**
	*
	* @brief Searches in vector of customers for customers with the name it receives as parameter using a binary search algorithm (lower_bound from STL).
	* @param name The customer name to search for.
	* @param lower_idx The lower bound index, i. e., the index to the first Customer * with the given name to appear in the vector of Customer * (returned by reference). This is set to -1 if no customer with the given name was found in the vector of customers
	* @param upper_idx The upper bound index, i. e., the index to the last Customer * with the given name to appear in the vector of Customer * (returned by reference). This is set to -1 if no customer with the given name was found in the vector of customers
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForActiveCustName(string name, int &lower_idx, int &upper_idx) const;
	/**
	*
	* @brief Searches in the inactive customers hash table for customers with the name it receives as parameter using a squential search algorithm.
	* @param name The customer name to search for.
	* @param cust_its vector with iterators to the customers (in the customers hash table) with the given name. (returned by reference). This is set to empty if no customer with the given name was found in the hash table of inactive customers.
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForInactiveCustName(string name, vector<CustomerHash::iterator> &cust_its) const;
	/**
	*
	* @brief Searches in the vector of active customers and in the hash table of inactive customers for a customer with the same NIF it receives as parameter. (Effectively calls function SearchForCustNIF and, if not found, calls function SearchForInactiveCustNIF.)
	* @param nif The NIF of the customer to search for
	* @param idx The index of the customer (in the vector of Customer*) (returns by reference). If a customer with the given NIF was not found in the vector of active customers, this is set to -1.
	* @param it The iterator to the customer with the same NIF it recieves as parameter (returns by reference). (If not found in the hash table of inactive customers, is set to past the end (iterator that points to nothing)).
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForCustNIF(unsigned int nif, int &idx, CustomerHash::iterator &it) const;
	/**
	*
	* @brief Searches in the vector of active customers for a customer with the same NIF it receives as parameter using a sequential search algorithm (can't use binary search since it is not sorted by NIFs, but by names instead).
	* @param nif The NIF of the customer to search for
	* @param idx The index of the customer (in the vector of Customer*) (returns by reference). If a customer with the given NIF was not found in the vector of active customers, this is set to -1.
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForActiveCustNIF(unsigned int nif, int &idx) const;
	/**
	*
	* @brief Searches in hash table of inactive customers for a customer with the same NIF it receives as parameter using a sequential search algorithm.
	* @param nif The NIF of the customer to search for
	* @param it The iterator to the customer with the same NIF it recieves as parameter (returns by reference). (If not found in the hash table of inactive customers, is set to past the end (iterator that points to nothing)).
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForInactiveCustNIF(unsigned int nif, CustomerHash::iterator &it) const;
	/**
	*
	* @brief Searches for an existing service's id. Since the vector of services is inside each customer, it must return the index of a customer (in the vector of Customer *) or the iterator to a Customer * in the inactive customers hash table to which the service's id respects to and the index of the service (in the vector of Services that is inside a Customer).
	* @param service_id The id of the service to search for.
	* @param customer_idx The index of the customer (in the vector of active customers) to which the service (that respects to the given id) was provided to (returns by reference). This is set to -1 if the service was not found in the customers of the vector of active customers
	* @param it The iterator of the customer (in the hash table of inactive customers) to which the service (that respects to the given id) was provided to (returns by reference). This is set to past the end (iterator that points to nothing) if the service was not found in the customers of the hash table of customers
	* @param service_idx The index of the service (in the vector of services) to which the id respects.
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForServiceId(unsigned int service_id, int &customer_idx, CustomerHash::iterator &it, unsigned int &service_idx) const;
	/**
	*
	* @brief Searches for services with the same Date as the one it receives as parameter. Since the vector of services is inside each customer and there can be multiple customers with services in the given date, so it must return a vector (by reference) with the services that match the given date.
	* @param date The date of the service to search for.
	* @desired_services A vector with the services it found (that were provided in the given date (the start time of the service)) (returns by reference). This is set to an empty vector if no services with the given date were found
	* @return true if it was found; false if not found
	*
	*/
	bool SearchForServiceDate(const Date &date, vector<Service> &desired_services) const;
	/**
	*
	* @brief Searches for services that were provided between date1 and date2 it receives as parameter. Since the vector of services is inside each customer and there can be multiple customers with services between the given dates, so it must return a vector (by reference) with the services that match the given dates.
	* @param date1 The first date of the service to search for (the temporal lower bound).
	* @param date2 The second date of the service to search for (the temporal upper bound).
	* @desired_services A vector with the services it found (that were provided between the given dates (the start time of the service)) (returns by reference)
	*
	*/
	void SearchForServicesBetweenDates(const Date &date1, const Date &date2, vector<Service> &desired_services) const;
	/**
	*
	* @brief Searches for an invoice with the same id it receives as parameter.
	* @param id The id of the invoice to search for
	* @return If the invoice with the given id was found, returns an iterator for it; if it was not found, returns -1.
	*
	*/
	BSTItrIn<Invoice> EmpresaDeTaxis::SearchForInvoiceId(unsigned int id) const;
	/**
	*
	* @brief Searches for a taxi with the same id it receives as parameter using a binary search algorithm(lower_bound from STL).
	* @param id The id of the taxi to search for
	* @return If the taxi with the given id was found, returns its index in the vector of taxis; if it was not found, returns -1.
	*
	*/
	int SearchForTaxiId(unsigned int id) const;
	/**
	*
	* @brief Searches for a taxi with the same license plate it receives as parameter using a sequential search algorithm (can't use binary search because the vecot of taxis is not sorted by license plate).
	* @param plate The license plate of the taxi to search for
	* @return If the taxi with the given license plate was found, returns its index in the vector of taxis; if it was not found, returns -1.
	*
	*/
	int SearchForTaxiLicensePlate(const LicensePlate &plate) const;
	/**
	*
	* @brief Searches for a driver with the same id it receives as parameter using a sequential search algorithm.
	* @param driver_id The id of the driver to search for.
	* @return If the driver with the given id was found, returns its index in the vector of taxis; if it was not found, returns -1.
	*
	*/
	int SearchForDriverId(unsigned int driver_id) const;
	/**
	*
	* @brief Searches for a driver with the same name it receives as parameter using a sequential search algorithm.
	* @param drivers_indexes The vector with the indexes of the drivers found (because there can be multiple drivers with the given name) (returns by reference).
	* @param driver_name The name of the driver to search for.
	*
	*/
	void SearchForDriverName(vector<unsigned int> &drivers_indexes, string driver_name) const;
	/**
	*
	* @brief Searches for a driver with the same NIF it receives as parameter using a sequential search algorithm.
	* @param nif The NIF of the driver to search for.
	* @return If the driver with the given NIF was found, returns its index in the vector of drivers; if it was not found, returns -1.
	*
	*/
	int SearchForDriverNIF(unsigned int nif) const;
	/**
	*
	* @brief Searches for a driver with the same driver's license it receives as parameter using a sequential search algorithm.
	* @param driver_license the driver's license number to search for.
	* @return If the driver with the given driver's license was found, returns its index in the vector of drivers; if it was not found, returns -1.
	*
	*/
	int SearchForDriverLicense(unsigned int driver_license) const;



	/**
	*
	* @brief Calls a method of the class given a pointer to it (EmpreseDeTaxis::*).
	*
	*/
	void CallConstFunction(void(EmpresaDeTaxis::*Function)());

	/**
	*
	* @brief Calls all the functions that will save all of the changes made to customers, services, taxis and drivers during the program's execution.
	*
	*/
	void SaveChanges() const;
	/**
	*
	* @brief Creates a temporary file that contains all of the customers information. If no problems occur, the original customers file is deleted and the temporary file is renamed after the original file.
	*
	*/
	void SaveCustomers() const;
	/**
	*
	* @brief Creates a temporary file that contains all the services. If no problems occur, the original services file is deleted and the temporary file is renamed after the original file.
	*
	*/
	void SaveServices() const;
	/**
	*
	* @brief Creates a temporary file that contains all of the taxis information. If no problems occur, the original taxis file is deleted and the temporary file is renamed after the original file.
	*
	*/
	void SaveTaxis() const;
	/**
	*
	* @brief Creates a temporary file that contains all of the drivers information. If no problems occur, the original drivers file is deleted and the temporary file is renamed after the original file.
	*
	*/
	void SaveDrivers() const;
};
//------------------------------------------------------------------------------
template<class Compare>
void EmpresaDeTaxis::DisplayAllCustomersInSpecificOrder(Compare comp) const
{
	vector<Customer*> customers_sorted = customers;
	customers_sorted.erase(customers_sorted.begin()); //erase the unregistered customer because it is not intended to be shown
	sort(customers_sorted.begin(), customers_sorted.end(), comp);

	unsigned int customers_size = customers.size();
	if (customers_size == 1 && inactive_customers.empty())
	{
		cout << "Nao existem clientes na empresa. Utilize a opcao do menu para adicionar clientes." << endl;
		return;
	}
	unsigned int customers_sorted_size = customers_sorted.size();
	if (customers_size != 1)
	{
		cout << "Active Customers:" << endl << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl;
		for (unsigned int i = 1; i < customers_sorted_size; i++)
			cout << *customers_sorted[i] << endl << endl;
	}

	customers_sorted.clear();
	if (!inactive_customers.empty())
	{
		//Fill the vector of sorted customers with the inactive customers (the ones in the hash table)
		//(in order to show all customers, temporary vector mus be filled with all the customers, that will be sorted by the intended order right after)
		for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
			customers_sorted.push_back(*it);

		sort(customers_sorted.begin(), customers_sorted.end(), comp);

		cout << "Inactive Customers:" << endl << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl;
		customers_sorted_size = customers_sorted.size();
		for (unsigned int i = 0; i < customers_sorted_size; i++)
			cout << *customers_sorted[i] << endl << endl;
	}
}