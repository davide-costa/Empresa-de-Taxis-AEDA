#include "Customer.h"

#include "EmpresaDeTaxis.h"
#include "utils.h"
//---------------------------------------Class CustomerDiscount---------------------------------------
//------------------------------------------------------------------------------
CustomerDiscount::CustomerDiscount(unsigned int voucher, unsigned int voucher_valid_month, unsigned int voucher_valid_year, bool free_trip, unsigned int free_trip_valid_month, unsigned int free_trip_valid_year, unsigned int num_trips, unsigned int amount_paid, unsigned int current_month, unsigned int current_year)
{
	this->voucher = voucher;
	this->voucher_valid_month = voucher_valid_month;
	this->voucher_valid_year = voucher_valid_year;
	this->free_trip = free_trip;
	this->free_trip_valid_month = free_trip_valid_month;
	this->free_trip_valid_year = free_trip_valid_year;
	this->num_trips = num_trips;
	this->amount_paid = amount_paid;
	this->current_month = current_month;
	this->current_year = current_year;
}
//------------------------------------------------------------------------------
CustomerDiscount::CustomerDiscount()
{
	voucher = 0;
	voucher_valid_month = 0;
	free_trip = false;
	free_trip_valid_month = 0;
	num_trips = 0;
	amount_paid = 0;

	Date curr_system_date;
	GetDateFromWindows(curr_system_date);
	current_month = curr_system_date.GetMonth();
	current_year = curr_system_date.GetYear();
}
//------------------------------------------------------------------------------
bool CustomerDiscount::IsFreeTrip() const
{
	return free_trip;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetFreeTripValidMonth() const
{
	return free_trip_valid_month;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetFreeTripValidYear() const
{
	return free_trip_valid_year;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetVoucher() const
{
	return voucher;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetVoucherValidMonth() const
{
	return voucher_valid_month;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetVoucherValidYear() const
{
	return voucher_valid_year;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetAmountPaid() const
{
	return amount_paid;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetCurrentMonth() const
{
	return current_month;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetCurrentYear() const
{
	return current_year;
}
//------------------------------------------------------------------------------
unsigned int CustomerDiscount::GetNumTrips() const
{
	return num_trips;
}
//------------------------------------------------------------------------------
bool CustomerDiscount::IsVoucherAvailable()
{
	Date windows_date;
	GetDateFromWindows(windows_date);

	if ((voucher > 0) && (windows_date.GetMonth() == voucher_valid_month))
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------
bool CustomerDiscount::IsFreeTripAvailable()
{
	Date windows_date;
	GetDateFromWindows(windows_date);

	if (free_trip && (windows_date.GetMonth() == voucher_valid_month))
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetFreeTrip(bool free_trip)
{
	this->free_trip = free_trip;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetFreeTripValidMonth(unsigned int free_trip_valid_month)
{
	this->free_trip_valid_month = free_trip_valid_month;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetFreeTripValidYear(unsigned int free_trip_valid_year)
{
	this->free_trip_valid_year = free_trip_valid_year;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetVoucher(unsigned int voucher)
{
	this->voucher = voucher;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetVoucherValidMonth(unsigned int voucher_valid_month)
{
	this->voucher_valid_month = voucher_valid_month;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetVoucherValidYear(unsigned int voucher_valid_year)
{
	this->voucher_valid_year = voucher_valid_year;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetAmountPaid(unsigned int amount_paid)
{
	this->amount_paid = amount_paid;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetCurrentMonth(unsigned int current_month)
{
	this->current_month = current_month;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetCurrentYear(unsigned int current_year)
{
	this->current_year = current_year;
}
//------------------------------------------------------------------------------
void CustomerDiscount::SetNumTrips(unsigned int num_trips)
{
	this->num_trips = num_trips;
}
//------------------------------------------------------------------------------
void CustomerDiscount::IncrementNumTrips()
{
	num_trips++;
}
//------------------------------------------------------------------------------
void CustomerDiscount::IncrementAmountPaid(float amount)
{
	amount_paid += amount;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const CustomerDiscount &discount)
{
	ostringstream oss;
	string discount_str;
	oss << setw(3) << discount.voucher << setw(3) << discount.voucher_valid_month << setw(3) << discount.voucher_valid_year << setw(3) << discount.free_trip << setw(3) << discount.free_trip_valid_month << setw(3) << discount.free_trip_valid_year << setw(3) << discount.num_trips << setw(3) << discount.amount_paid << setw(3) << discount.current_month << setw(3) << discount.current_year;
	discount_str = oss.str();
	os << discount_str;
	return os;
}
//------------------------------------------------------------------------------
ofstream &operator<<(ofstream &ofs, const CustomerDiscount &discount)
{
	ofs << "" << discount.voucher << " ; " << discount.voucher_valid_month << " ; " << discount.voucher_valid_year << " ; " << discount.free_trip << " ; " << discount.free_trip_valid_month << " ; " << discount.free_trip_valid_year << " ; " << discount.num_trips << " ; " << discount.amount_paid << " ; " << discount.current_month << " ; " << discount.current_year;
	return ofs;
}
//---------------------------------------Class Customer---------------------------------------
Customer::Customer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount)
{
	this->id = id;
	this->name = name;
	this->adress = adress;
	this->NIF = NIF;
	this->regist_date = regist_date;
	this->points = points;
	this->unpaid_amount = unpaid_amount;
	this->last_trip_time = last_trip_time;
	this->discount = discount;
}
//------------------------------------------------------------------------------
Customer::Customer(string name, string adress, unsigned int NIF)
{
	curr_cust_id++;
	this->id = curr_cust_id;
	this->name = name;
	this->adress = adress;
	this->NIF = NIF;
	last_trip_time = 0;
	points = 0;
	unpaid_amount = 0;
	GetDateFromWindows(regist_date);
}
//------------------------------------------------------------------------------
Customer::Customer(unsigned int id)
{
	this->id = id;
}
//------------------------------------------------------------------------------
Customer::Customer(string name)
{
	this->name = name;
}
//------------------------------------------------------------------------------
Customer::Customer()
{

}
//------------------------------------------------------------------------------
void Customer::GetCustomerDiscount(CustomerDiscount &discount) const
{
	discount = this->discount;
}
//------------------------------------------------------------------------------
void Customer::SetCustomerDiscount(const CustomerDiscount &discount)
{
	this->discount = discount;
}
//------------------------------------------------------------------------------
const string& Customer::GetAdress() const
{
	return adress;
}
//------------------------------------------------------------------------------
void Customer::SetAdress(const string& adress)
{
	this->adress = adress;
}
//------------------------------------------------------------------------------
unsigned int Customer::GetId() const
{
	return id;
}
//------------------------------------------------------------------------------
void Customer::SetId(unsigned int id)
{
	this->id = id;
}
//------------------------------------------------------------------------------
const string& Customer::GetName() const
{
	return name;
}
//------------------------------------------------------------------------------
void Customer::SetName(const string& name)
{
	this->name = name;
}
//------------------------------------------------------------------------------
unsigned int Customer::GetNif() const
{
	return NIF;
}
//------------------------------------------------------------------------------
void Customer::SetNif(unsigned int nif)
{
	NIF = nif;
}
//------------------------------------------------------------------------------
Date Customer::GetRegistDate() const
{
	return regist_date;
}
//------------------------------------------------------------------------------
void Customer::SetRegistDate(Date registDate)
{
	regist_date = registDate;
}
//------------------------------------------------------------------------------
void Customer::GetServices(vector<Service> &services) const
{
	services = this->services;
}
//------------------------------------------------------------------------------
void Customer::SetServices(const vector<Service> &services)
{
	this->services = services;
}
//------------------------------------------------------------------------------
unsigned int Customer::GetServicesSize() const
{
	return services.size();
}
//------------------------------------------------------------------------------
void Customer::AppendService(Service service)
{
	services.push_back(service);
}
//------------------------------------------------------------------------------
unsigned int Customer::GetPoints()
{
	return points;
}
//------------------------------------------------------------------------------
float Customer::GetUnPaidAmount()
{
	return unpaid_amount;
}
//------------------------------------------------------------------------------
time_t Customer::GetLastTripTime()
{
	return last_trip_time;
}
//------------------------------------------------------------------------------
unsigned int Customer::curr_cust_id = 0;
//------------------------------------------------------------------------------
unsigned int Customer::GetCurrCustId()
{
	return curr_cust_id;
}
//------------------------------------------------------------------------------
void Customer::SetCurrCustId(unsigned int new_curr_cust_id)
{
	curr_cust_id = new_curr_cust_id;
}
//------------------------------------------------------------------------------
const Service &Customer::GetServiceAtIdx(unsigned int idx) const
{
	return services[idx];
}
//------------------------------------------------------------------------------
bool operator<(const Customer &customer1, const Customer &customer2)
{
	return customer1.name < customer2.name;
}
//------------------------------------------------------------------------------
bool CompareCustomersNames(const Customer *customer1, const Customer *customer2)
{
	return customer1->name < customer2->name;
}
bool CompareCustomersRegistDates(const Customer * customer1, const Customer * customer2)
{
	return customer1->regist_date < customer2->regist_date;
}
bool CompareCustomersPoints(const Customer * customer1, const Customer * customer2)
{
	return customer1->points < customer2->points;
}
bool CompareCustomersUnPaidAmounts(const Customer * customer1, const Customer * customer2)
{
	return customer1->unpaid_amount < customer2->unpaid_amount;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Customer &customer)
{
	ostringstream oss;
	string customer_str;
	oss << setw(4) << customer.id << setw(18) << customer.name << setw(18) << customer.adress << setw(16) << customer.NIF << setw(18) << customer.regist_date << setw(12) << customer.points << setw(19) << fixed << setprecision(2) << customer.unpaid_amount;
	customer_str = oss.str();
	os << customer_str;
	return os;
}
//------------------------------------------------------------------------------
ofstream &operator<<(ofstream &ofs, const Customer &customer)
{
	ofs << "" << customer.id << " ; " << customer.name << " ; " << customer.adress << " ; " << customer.NIF << " ; " << customer.regist_date << " ; " << customer.points << " points balance" << " ; " << customer.unpaid_amount << " unpaid amount" << " ; " << customer.last_trip_time << " last trip time" << " ; ";
	ofs << customer.discount;
	return ofs;
}
//------------------------------------------------------------------------------
void Customer::SortServices()
{
	sort(services.begin(), services.end());
}
//------------------------------------------------------------------------------
void Customer::SetAllServicesAsPaid()
{
	unsigned int services_size = services.size();
	for (unsigned int i = 0; i < services_size; i++)
		services[i].SetAsPaid();

	points += unpaid_amount;
	unpaid_amount = 0;
}
//------------------------------------------------------------------------------
void Customer::SubPoints(unsigned int points)
{
	this->points -= points;
}
//------------------------------------------------------------------------------
bool Customer::VerifyUnpaidAmount()
{
	Date windows_date;
	GetDateFromWindows(windows_date);
	unsigned int current_month = windows_date.GetMonth();
	unsigned int unpaid_month = discount.GetCurrentMonth();
	if (unpaid_amount != 0)
		if (unpaid_month < current_month)
		{
			cout << "Tem despesas para pagar do mes " << unpaid_month << " no valor de " << unpaid_amount << " euros." << endl;
			cout << "O cliente deve efetuar o pagamento, nao podendo realizar quaisquer viagens nesta empresa enquanto a sua situacao nao estiver regularizada." << endl;
			cout << "Nestas condicoes, o cliente ira efetuar o pagamento agora? (escreva sim ou nao): ";
			if (ReadYesOrNo())
			{
				SetAllServicesAsPaid();
				return true;
			}
			else
				return false;
		}
	return true;
}
//------------------------------------------------------------------------------
void Customer::PostPoneLastServicePayment(float price)
{
	unsigned int service_idx = services.size() - 1;
	services[service_idx].SetAsUnPaid();
	unpaid_amount += price;
}
//------------------------------------------------------------------------------
void Customer::UpdateDiscount()
{
	Date windows_date;
	GetDateFromWindows(windows_date);
	unsigned int curr_month = windows_date.GetMonth();
	unsigned int curr_year = windows_date.GetYear();

	if (discount.GetCurrentMonth() < curr_month || discount.GetCurrentYear() < curr_year)
	{
		discount.SetCurrentMonth(curr_month);
		discount.SetCurrentYear(curr_year);
		discount.SetNumTrips(0);
		discount.SetAmountPaid(0);
	}
	if (discount.GetVoucherValidMonth() < curr_month || discount.GetCurrentYear() < curr_year)
	{
		discount.SetVoucher(0);
		discount.SetVoucherValidMonth(0);
		discount.SetVoucherValidYear(0);
	}
	if (discount.GetFreeTripValidMonth() < curr_month || discount.GetCurrentYear() < curr_year)
	{
		discount.SetFreeTrip(false);
		discount.SetFreeTripValidMonth(0);
		discount.SetFreeTripValidYear(0);
	}
}


//---------------------------------------Class ParticularCustomer---------------------------------------
bool ParticularCustomer::min_trips_discount = false;
bool ParticularCustomer::min_paid_discount = false;
unsigned int ParticularCustomer::min_trips_for_discount = 15;
unsigned int ParticularCustomer::min_paid_for_discount = 80;
time_t ParticularCustomer::min_time_to_inactive = 45 * 24 * 3600; //45 days in seconds
																  //------------------------------------------------------------------------------
ParticularCustomer::ParticularCustomer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount) : Customer(id, name, adress, NIF, regist_date, points, unpaid_amount, last_trip_time, discount)
{

}
//------------------------------------------------------------------------------
ParticularCustomer::ParticularCustomer(string name, string adress, unsigned int NIF) : Customer(name, adress, NIF)
{

}
//------------------------------------------------------------------------------
ParticularCustomer::ParticularCustomer(unsigned int id) : Customer(id)
{

}
//------------------------------------------------------------------------------
ParticularCustomer::ParticularCustomer(string name) : Customer(name)
{

}
//------------------------------------------------------------------------------
float ParticularCustomer::MakePayment()
{
	Date windows_date;
	GetDateFromWindows(windows_date);
	unsigned int current_month = windows_date.GetMonth();
	unsigned int current_year = windows_date.GetYear();
	time_t curr_system_time = time(NULL);
	if (curr_system_time == -1)
		EmpresaDeTaxis::ErrorGettingLocalTime();

	last_trip_time = curr_system_time;

	UpdateDiscount();
	unsigned int service_idx = services.size() - 1;
	bool free_trip = discount.IsFreeTrip();
	if (free_trip)
		if (discount.GetFreeTripValidMonth() == current_month || discount.GetFreeTripValidYear() == current_year) //check if the free trip is valid in the current month
		{
			cout << "O cliente possui uma viagem gratuita, portanto o custo desta viagem e nulo." << endl;
			services[service_idx].SetFinalPrice(0);
			discount.SetFreeTrip(false);
			discount.SetFreeTripValidMonth(0);
			services[service_idx].SetFinalPrice(0);
			return 0;
		}

	unsigned int voucher = discount.GetVoucher();
	float pre_price = services[service_idx].GetPrePrice();
	float final_price;
	if (voucher != 0)
		if (discount.GetVoucherValidMonth() == current_month) //check if the voucher is valid in the current month
		{
			final_price = roundf((pre_price - voucher) * 100) / 100;
			if (final_price < 0)
			{
				final_price = 0;
				voucher -= pre_price;
				cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto a viagem sera gratuita. Ficando ainda com um voucher no valor de " << voucher << " euros." << endl;
			}
			else
			{
				if (final_price == 0)
					cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto a viagem sera gratuita." << endl;
				else
					cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto o preco final desta viagem sera de " << final_price << " euros." << endl;

				voucher = 0;
				discount.SetVoucherValidMonth(0);
				discount.SetVoucherValidYear(0);
			}
			services[service_idx].SetFinalPrice(final_price);
			discount.SetVoucher(voucher);
			discount.IncrementNumTrips();
			discount.IncrementAmountPaid(final_price);
			points += final_price;
			services[service_idx].SetFinalPrice(final_price);
			return final_price;
		}

	final_price = roundf(pre_price * 100) / 100;
	points += final_price;


	if (current_month != services[service_idx].GetDate().GetMonth() || current_year != services[service_idx].GetDate().GetYear())
	{
		services[service_idx].SetFinalPrice(final_price);
		return final_price;
	}

	if (min_trips_discount)
	{
		discount.IncrementNumTrips();
		if (discount.GetNumTrips() == min_trips_for_discount)
		{
			discount.SetFreeTrip(true);
			discount.SetFreeTripValidMonth((current_month % 12) + 1);  //the remainder of the division by 12 wil give always the rigth month
			if (current_month == 12)
				discount.SetFreeTripValidYear(current_year + 1);
			else
				discount.SetFreeTripValidYear(current_year);
		}
	}
	if (min_paid_discount)
	{
		bool voucher_available = false;
		discount.IncrementAmountPaid(pre_price);

		if (discount.GetAmountPaid() >= min_paid_for_discount * 2)
		{
			discount.SetVoucher(15);
			voucher_available = true;
		}
		else if (discount.GetAmountPaid() >= min_paid_for_discount * 1.5)
		{
			discount.SetVoucher(10);
			voucher_available = true;
		}
		else if (discount.GetAmountPaid() >= min_paid_for_discount)
		{
			discount.SetVoucher(5);
			voucher_available = true;
		}

		if (voucher_available)
		{
			discount.SetVoucherValidMonth((current_month % 12) + 1);  //the remainder of the division by 12 wil give always the rigth month
			if (current_month == 12)
				discount.SetVoucherValidYear(current_year + 1);
			else
				discount.SetVoucherValidYear(current_year);
		}
	}
	services[service_idx].SetFinalPrice(final_price);
	return final_price; //if no discounts were applicable, the final price is equal to the pre_price
}
//------------------------------------------------------------------------------
void ParticularCustomer::ResetDisabledDiscounts()
{
	if (!min_trips_discount)
	{
		discount.SetFreeTrip(0);
		discount.SetFreeTripValidMonth(0);
		discount.SetFreeTripValidYear(0);
		discount.SetNumTrips(0);
	}

	if (!min_paid_discount)
	{
		discount.SetVoucher(0);
		discount.SetVoucherValidMonth(0);
		discount.SetVoucherValidYear(0);
		discount.SetAmountPaid(0);
	}

	if (!min_trips_discount || !min_paid_discount)
	{
		discount.SetCurrentMonth(0);
		discount.SetCurrentYear(0);
	}
}
//------------------------------------------------------------------------------
bool ParticularCustomer::IsMinPaidDiscount()
{
	return min_paid_discount;
}
//------------------------------------------------------------------------------
bool ParticularCustomer::IsMinTripsDiscount()
{
	return min_trips_discount;
}
//------------------------------------------------------------------------------
unsigned int ParticularCustomer::GetMinPaidForDiscount()
{
	return min_paid_for_discount;
}
//------------------------------------------------------------------------------
unsigned int ParticularCustomer::GetMinTripsForDiscount()
{
	return min_trips_for_discount;
}
//------------------------------------------------------------------------------
time_t ParticularCustomer::GetMinTimeToInactive()
{
	return min_time_to_inactive;
}
//------------------------------------------------------------------------------
void ParticularCustomer::SetMinPaidForDiscount(unsigned int min_paid_for_discount)
{
	ParticularCustomer::min_paid_for_discount = min_paid_for_discount;
}
//------------------------------------------------------------------------------
void ParticularCustomer::SetMinPaidDiscount(bool min_paid_discount)
{
	ParticularCustomer::min_paid_discount = min_paid_discount;
}
//------------------------------------------------------------------------------
void ParticularCustomer::SetMinTripsForDiscount(unsigned int min_trips_for_discount)
{
	ParticularCustomer::min_trips_for_discount = min_trips_for_discount;
}
//------------------------------------------------------------------------------
void ParticularCustomer::SetMinTripsDiscount(bool min_trips_discount)
{
	ParticularCustomer::min_trips_discount = min_trips_discount;
}
//------------------------------------------------------------------------------
void ParticularCustomer::SetMinTimeToInactive(time_t min_time_to_inactive)
{
	ParticularCustomer::min_time_to_inactive = min_time_to_inactive;
}
//---------------------------------------Class BusinessCustomer---------------------------------------
bool BusinessCustomer::min_trips_discount = false;
bool BusinessCustomer::min_paid_discount = false;
unsigned int BusinessCustomer::min_trips_for_discount = 15;
unsigned int BusinessCustomer::min_paid_for_discount = 80;
time_t BusinessCustomer::min_time_to_inactive = 45 * 24 * 3600; //45 days in seconds
																//------------------------------------------------------------------------------
BusinessCustomer::BusinessCustomer(unsigned int id, string name, string adress, unsigned int NIF, Date regist_date, unsigned int points, float unpaid_amount, time_t last_trip_time, CustomerDiscount discount) : Customer(id, name, adress, NIF, regist_date, points, unpaid_amount, last_trip_time, discount)
{

}
//------------------------------------------------------------------------------
BusinessCustomer::BusinessCustomer(string name, string adress, unsigned int NIF) : Customer(name, adress, NIF)
{

}
//------------------------------------------------------------------------------
float BusinessCustomer::MakePayment()
{
	Date windows_date;
	GetDateFromWindows(windows_date);
	unsigned int current_month = windows_date.GetMonth();
	unsigned int current_year = windows_date.GetYear();
	time_t curr_system_time = time(NULL);
	if (curr_system_time == -1)
		throw EmpresaDeTaxis::ErrorGettingLocalTime();

	last_trip_time = curr_system_time;

	UpdateDiscount();
	unsigned int service_idx = services.size() - 1;
	bool free_trip = discount.IsFreeTrip();
	if (free_trip)
		if (discount.GetFreeTripValidMonth() == current_month && discount.GetFreeTripValidYear() == current_year) //check if the free trip is valid in the current month
		{
			cout << "O cliente possui uma viagem gratuita, portanto o custo desta viagem e nulo." << endl;
			services[service_idx].SetFinalPrice(0);
			discount.SetFreeTrip(false);
			discount.SetFreeTripValidMonth(0);
			services[service_idx].SetFinalPrice(0);
			return 0;
		}

	unsigned int voucher = discount.GetVoucher();
	float pre_price = services[service_idx].GetPrePrice();
	float final_price;
	if (voucher != 0)
		if (discount.GetVoucherValidMonth() == current_month) //check if the voucher is valid in the current month
		{
			final_price = roundf((pre_price - voucher) * 100) / 100;
			if (final_price < 0)
			{
				final_price = 0;
				voucher -= pre_price;
				cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto a viagem sera gratuita. Ficando ainda com um voucher no valor de " << voucher << " euros." << endl;
			}
			else
			{
				if (final_price == 0)
					cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto a viagem sera gratuita." << endl;
				else
					cout << "O cliente possui um voucher no valor de " << voucher << " euros, portanto o preco final desta viagem sera de " << final_price << " euros." << endl;

				voucher = 0;
				discount.SetVoucherValidMonth(0);
				discount.SetVoucherValidYear(0);
			}
			services[service_idx].SetFinalPrice(final_price);
			discount.SetVoucher(voucher);
			discount.IncrementNumTrips();
			discount.IncrementAmountPaid(final_price);
			points += final_price;
			services[service_idx].SetFinalPrice(final_price);
			return final_price;
		}

	final_price = roundf(pre_price * 100) / 100;
	points += final_price;


	if (current_month != services[service_idx].GetDate().GetMonth() || current_year != services[service_idx].GetDate().GetYear())
	{
		services[service_idx].SetFinalPrice(final_price);
		return final_price;
	}

	if (min_trips_discount)
	{
		discount.IncrementNumTrips();
		if (discount.GetNumTrips() == min_trips_for_discount)
		{
			discount.SetFreeTrip(true);
			discount.SetFreeTripValidMonth((current_month % 12) + 1);  //the remainder of the division by 12 wil give always the rigth month
			if (current_month == 12)
				discount.SetFreeTripValidYear(current_year + 1);
			else
				discount.SetFreeTripValidYear(current_year);
		}
	}
	if (min_paid_discount)
	{
		bool voucher_available = false;
		discount.IncrementAmountPaid(pre_price);

		if (discount.GetAmountPaid() >= min_paid_for_discount * 2)
		{
			discount.SetVoucher(15);
			voucher_available = true;
		}
		else if (discount.GetAmountPaid() >= min_paid_for_discount * 1.5)
		{
			discount.SetVoucher(10);
			voucher_available = true;
		}
		else if (discount.GetAmountPaid() >= min_paid_for_discount)
		{
			discount.SetVoucher(5);
			voucher_available = true;
		}

		if (voucher_available)
		{
			discount.SetVoucherValidMonth((current_month % 12) + 1);  //the remainder of the division by 12 wil give always the rigth month
			if (current_month == 12)
				discount.SetVoucherValidYear(current_year + 1);
			else
				discount.SetVoucherValidYear(current_year);
		}
	}
	services[service_idx].SetFinalPrice(final_price);
	return final_price; //if no discounts were applicable, the final price is equal to the pre_price
}
//------------------------------------------------------------------------------
void BusinessCustomer::ResetDisabledDiscounts()
{
	if (!min_trips_discount)
	{
		discount.SetFreeTrip(0);
		discount.SetFreeTripValidMonth(0);
		discount.SetNumTrips(0);
	}

	if (!min_paid_discount)
	{
		discount.SetVoucher(0);
		discount.SetVoucherValidMonth(0);
		discount.SetAmountPaid(0);
	}

	if (!min_trips_discount || !min_paid_discount)
	{
		discount.SetCurrentMonth(0);
		discount.SetCurrentYear(0);
	}
}
//------------------------------------------------------------------------------
bool BusinessCustomer::IsMinTripsDiscount()
{
	return min_trips_discount;
}
//------------------------------------------------------------------------------
bool BusinessCustomer::IsMinPaidDiscount()
{
	return min_paid_discount;
}
//------------------------------------------------------------------------------
unsigned int BusinessCustomer::GetMinTripsForDiscount()
{
	return min_trips_for_discount;
}
//------------------------------------------------------------------------------
unsigned int BusinessCustomer::GetMinPaidForDiscount()
{
	return min_paid_for_discount;
}
//------------------------------------------------------------------------------
time_t BusinessCustomer::GetMinTimeToInactive()
{
	return min_time_to_inactive;
}
//------------------------------------------------------------------------------
void BusinessCustomer::SetMinPaidForDiscount(unsigned int min_paid_for_discount)
{
	BusinessCustomer::min_paid_for_discount = min_paid_for_discount;
}
//------------------------------------------------------------------------------
void BusinessCustomer::SetMinPaidDiscount(bool min_paid_discount)
{
	BusinessCustomer::min_paid_discount = min_paid_discount;
}
//------------------------------------------------------------------------------
void BusinessCustomer::SetMinTripsForDiscount(unsigned int min_trips_for_discount)
{
	BusinessCustomer::min_trips_for_discount = min_trips_for_discount;
}
//------------------------------------------------------------------------------
void BusinessCustomer::SetMinTripsDiscount(bool min_trips_discount)
{
	BusinessCustomer::min_trips_discount = min_trips_discount;
}
//------------------------------------------------------------------------------
void BusinessCustomer::SetMinTimeToInactive(time_t min_time_to_inactive)
{
	BusinessCustomer::min_time_to_inactive = min_time_to_inactive;
}


//---------------------------------------Class BusinessCustomer---------------------------------------
UnRegisteredCustomer::UnRegisteredCustomer()
{
	id = 0;
	NIF = 0;
	points = 0;
}
//------------------------------------------------------------------------------
float UnRegisteredCustomer::MakePayment()
{
	unsigned int service_idx = services.size() - 1;
	float final_price = services[service_idx].GetPrePrice();
	final_price = roundf(final_price * 100) / 100;
	services[service_idx].SetFinalPrice(final_price);
	return final_price; //if no discounts were applicable, the final price is equal to the pre_price
}