#include "Invoice.h"


Invoice::Invoice(const Customer *customer, unsigned int service_idx)
{
	this->customer = customer;
	this->service_idx = service_idx;
}
//------------------------------------------------------------------------------
const Customer* Invoice::GetCustomer() const
{
	return customer;
}
//------------------------------------------------------------------------------
void Invoice::SetCustomer(Customer *customer)
{
	this->customer = customer;
}
//------------------------------------------------------------------------------
unsigned int Invoice::GetServiceIdx() const
{
	return service_idx;
}
//------------------------------------------------------------------------------
void Invoice::SetServiceIdx(unsigned int service_idx)
{
	this->service_idx = service_idx;
}
//------------------------------------------------------------------------------
bool operator<(const Invoice &invoice1, const Invoice &invoice2)
{
	if (invoice1.customer->GetName() != invoice2.customer->GetName())
	{
		return invoice1.customer->GetName() < invoice2.customer->GetName();
	}
	else
	{
		Service serv1 = invoice1.customer->GetServiceAtIdx(invoice1.service_idx);
		Service serv2 = invoice2.customer->GetServiceAtIdx(invoice2.service_idx);
		return serv1 < serv2;
	}
}
