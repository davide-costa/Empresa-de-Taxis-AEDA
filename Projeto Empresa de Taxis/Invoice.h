/**
*
* @file
* @brief Contains class declaration necessary to represent an invoice
*
*/


#pragma once

#include "Customer.h"
/**
*
* @brief Represents an Invoice.
*
*/
class Invoice
{
	/**
	*
	* @brief Compares two Invoice objects. A first Invoice object is less than the second if the customer to which the service was provided of the first's is less (his name is less alphabetically) than the second's. For the same customer or customers with the same name, the first Invoice object is less than the second if its service was providade before the second's.
	* @param invoice1 The first Invoice object to be compared.
	* @param invoice2 The second Invoice object to be compared.
	* @return a bool value indicating whether the first is lower than the second or not.
	*
	*/
	friend bool operator<(const Invoice &invoice1, const Invoice &invoice2);
private:
	/**
	*
	* @brief A pointer to the Customer to which the service respecting the Invoice was provided.
	*
	*/
	const Customer *customer;
	/**
	*
	* @brief The index of the service to which the Invoice respects to. (in the vector of services of the Customer to which the service was provided).
	*
	*/
	unsigned int service_idx;
public:
	/**
	*
	* @brief Creates a new Invoice object based on the customer and the service that it respects to.
	*
	*/
	Invoice(const Customer *customer, unsigned int service_idx);
	const Customer* GetCustomer() const;
	void SetCustomer(Customer *customer);
	unsigned int GetServiceIdx() const;
	void SetServiceIdx(unsigned int service_idx);
};