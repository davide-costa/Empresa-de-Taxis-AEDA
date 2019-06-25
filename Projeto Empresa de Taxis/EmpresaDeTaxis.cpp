#include "EmpresaDeTaxis.h"

#include "TimeStamp.h"
#include "Date.h"
#include "Service.h"
#include "utils.h"

//------------------------------------------------------------------------------
EmpresaDeTaxis::EmpresaDeTaxis(string company_name, string customers_p_fn, string customers_b_fn, string services_fn, string taxis_fn, string drivers_fn) :invoices(BST<Invoice>(Invoice(NULL, 0)))
{
	this->company_name = company_name;
	this->customers_p_fn = customers_p_fn;
	this->customers_b_fn = customers_b_fn;
	this->services_fn = services_fn;
	this->taxis_fn = taxis_fn;
	this->drivers_fn = drivers_fn;
}
//------------------------------------------------------------------------------
EmpresaDeTaxis::ErrorParsingFile::ErrorParsingFile(const string &error_msg, const string &file_name)
{
	this->error_msg = error_msg;
	this->file_name = file_name;
}
//------------------------------------------------------------------------------
const string &EmpresaDeTaxis::ErrorParsingFile::GetErrorMsg() const
{
	return error_msg;
}
//------------------------------------------------------------------------------
const string &EmpresaDeTaxis::ErrorParsingFile::GetFileName() const
{
	return file_name;
}
//------------------------------------------------------------------------------
const string &EmpresaDeTaxis::GetCompanyName()
{
	return company_name;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ComputeTmpFileNames()
{
	customers_p_tmp_fn = GetTmpFileName(customers_p_fn);
	customers_b_tmp_fn = GetTmpFileName(customers_b_fn);
	services_tmp_fn = GetTmpFileName(services_fn);
	taxis_tmp_fn = GetTmpFileName(taxis_fn);
	drivers_tmp_fn = GetTmpFileName(drivers_fn);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseParticularCustomers(ifstream &customers_fs)
{
	int num_of_customers; //the number of customers that will be extracted from the file
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of customers specified in the beggining of the file

	if (customers_fs.peek() == std::ifstream::traits_type::eof())
	{
		cout << "O ficheiro de clientes particulares esta vazio. O programa nao carregou quaisquer clientes do ficheiro.\nUtilize a opcao do Menu Principal para adicionar clientes a empresa." << endl;
		return;
	}

	customers_fs >> num_of_customers;
	customers_fs.ignore(INT_MAX, ';');
	//Check if the number of customers was successfully read from the file
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero de clientes do ficheiro.\nPor favor, verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}

	//Extract the data that is common to every ParticularCustomer object
	bool curr_static_bool;
	unsigned int curr_static_uint;

	//Extract a bool that indicates if the customer has the minimum number of trips for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero que identifica se os descontos para minimos de viagens estao ativos para clientes particulares do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint != 0 && curr_static_uint != 1)
	{
		throw ErrorParsingFile("O numero que identifica se os descontos para minimos de viagens estao ativos para clientes particulares lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	curr_static_bool = curr_static_uint;
	ParticularCustomer::SetMinTripsDiscount(curr_static_bool);

	//Extract a bool that indicates if the customer has the minimum paid for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero que identifica se estao ativos os descontos para minimos de totais pagos para o cliente particular obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint != 0 && curr_static_uint != 1)
	{
		throw ErrorParsingFile("O numero que identifica se estao ativos os descontos para minimos de totais pagos para o cliente particular obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	curr_static_bool = curr_static_uint;
	ParticularCustomer::SetMinPaidDiscount(curr_static_bool);

	//Extract minimum number of trips necessary for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero minimo de viagens necessario para o cliente particular obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O numero minimo de viagens necessarias para o cliente particular obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	ParticularCustomer::SetMinTripsForDiscount(curr_static_uint);

	//Extract minimum value paid necessary for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o valor minimo total de pagamentos realizados necessario para o cliente particular obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O valor minimo total de pagamentos realizados necessario para o cliente particular obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	ParticularCustomer::SetMinPaidForDiscount(curr_static_uint);

	//Extract minimum time (in seconds) for the customer to be considered inactive
	customers_fs >> curr_static_uint;
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o tempo minimo necessario para o cliente particular ser considerado inativo do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O tempo minimo necessario para o cliente particular ser considerado inativo lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	ParticularCustomer::SetMinTimeToInactive(curr_static_uint);

	ParseCustomers(customers_fs, num_of_customers, customers_p_fn, 0);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseBusinessCustomers(ifstream &customers_fs)
{
	int num_of_customers; //the number of customers that will be extracted from the file
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of customers specified in the beggining of the file

	if (customers_fs.peek() == std::ifstream::traits_type::eof())
	{
		cout << "O ficheiro de clientes empresariais esta vazio. O programa nao carregou quaisquer clientes do ficheiro.\nUtilize a opcao do Menu Principal para adicionar clientes a empresa." << endl;
		return;
	}

	customers_fs >> num_of_customers;
	customers_fs.ignore(INT_MAX, ';');

	//Check if the number of customers was successfully read from the file
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero de clientes do ficheiro.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}


	//Extract the data that is common to every BusinessCustomer object
	bool curr_static_bool;
	unsigned int curr_static_uint;

	//Extract a bool that indicates if the discounts for minimum number of trips are enabled
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero que identifica se os descontos para minimos de viagens estao ativos para clientes empresariais estao ativos do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	else if (curr_static_uint != 0 && curr_static_uint != 1)
	{
		throw ErrorParsingFile("O numero que identifica se os descontos para minimos de viagens estao ativos para clientes empresariais estao ativos lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	curr_static_bool = curr_static_uint;
	BusinessCustomer::SetMinTripsDiscount(curr_static_bool);

	//Extract a bool that indicates if the discounts for minimum value paid are enalbed
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero que identifica se os descontos para minimos de totais pagos para o cliente empresariais obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	else if (curr_static_uint != 0 && curr_static_uint != 1)
	{
		throw ErrorParsingFile("O numero que identifica se os descontos para minimos de totais pagos para o cliente empresariais obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	curr_static_bool = curr_static_uint;
	BusinessCustomer::SetMinPaidDiscount(curr_static_bool);

	//Extract minimum number of trips necessary for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero minimo de viagens necessario para o cliente empresariais obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O numero minimo de viagens necessarias para o cliente empresariais obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	BusinessCustomer::SetMinTripsForDiscount(curr_static_uint);

	//Extract minimum value paid necessary for discount
	customers_fs >> curr_static_uint;
	customers_fs.ignore(INT_MAX, ';');
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o valor minimo total de pagamentos realizados necessario para o cliente empresariais obter desconto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O valor minimo total de pagamentos realizados necessario para o cliente empresariais obter desconto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_b_fn);
	}
	BusinessCustomer::SetMinPaidForDiscount(curr_static_uint);

	//Extract minimum time (in seconds) for the customer to be considered inactive
	customers_fs >> curr_static_uint;
	if (customers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o tempo minimo necessario para o cliente empresarial ser considerado inativo do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	else if (curr_static_uint < 0)
	{
		throw ErrorParsingFile("O tempo minimo necessario para o cliente empresarial ser considerado inativo lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_p_fn);
	}
	BusinessCustomer::SetMinTimeToInactive(curr_static_uint);

	ParseCustomers(customers_fs, num_of_customers, customers_b_fn, 1);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseCustomers(ifstream &customers_fs, int num_of_customers, string customers_fn, int call_id)
{
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of customers specified in the beggining of the file

	if (call_id == 0)
	{
		Customer *unregistered_customer = new UnRegisteredCustomer();
		customers.push_back(unregistered_customer);
	}

	time_t curr_system_time; //this variable stores the current system time (in unix format, i.e., counted from the Epoch)
	time_t inactive_time;

	unsigned int curr_static_uint;
	string curr_customer_str;
	istringstream curr_customer_iss;
	int id;
	unsigned int unsigned_id;
	string name;
	string adress;
	unsigned int NIF;
	Date regist_date;
	float amount;
	int points_balance;
	unsigned int unsigned_points_balance;
	float unpaid_amount;
	int last_trip_time;
	unsigned int unsigned_last_trip_time;
	int voucher;
	unsigned int unsigned_voucher;
	int voucher_valid_month;
	unsigned int unsigned_voucher_valid_month;
	int voucher_valid_year;
	unsigned int unsigned_voucher_valid_year;
	bool free_trip;
	unsigned int unsigned_free_trip;
	int free_trip_valid_month;
	unsigned int unsigned_free_trip_valid_month;
	int free_trip_valid_year;
	unsigned int unsigned_free_trip_valid_year;
	int num_trips;
	unsigned int unsigned_num_trips; //number of trips in the current month
	float amount_paid;
	int current_month;
	unsigned int unsigned_current_month;
	int current_year;
	unsigned int unsigned_current_year;
	Date windows_date;
	GetDateFromWindows(windows_date);
	vector<unsigned int> unique_ids;
	vector<unsigned int> unique_nifs;
	vector<unsigned int>::iterator unique_it;

	customers_fs.ignore(INT_MAX, '\n');
	while (getline(customers_fs, curr_customer_str))
	{
		line_count++;
		name.clear();

		//Fill the input string stream curr_customer_iss with the content of the current line
		curr_customer_iss.str(curr_customer_str);

		//Extract the id from the istringstream and check it's validity; if it's not valid, throw exception
		curr_customer_iss >> id;
		curr_customer_iss.ignore(INT_MAX, ';');
		if (curr_customer_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id de um cliente do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if (id < 0)
		{
			throw ErrorParsingFile("O id de um cliente lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if (id == 0)
		{
			throw ErrorParsingFile("O id de um cliente lido do ficheiro e igual a um valor reservado (0), na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		unique_it = lower_bound(unique_ids.begin(), unique_ids.end(), id);
		//check if there are repeated ids in the file (an id must be unique)
		if (unique_it != unique_ids.end())
		{
			if (*unique_it == id)
			{
				throw ErrorParsingFile("O id de um cliente, lido do ficheiro na linha " + to_string(line_count + 1) + ", e igual ao de outro cliente ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
		}
		unique_ids.insert(unique_it, id);
		unsigned_id = id;

		//Extract the name from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_customer_iss, name, ';');
		RemoveSpacesFromPhrase(name);
		if (name.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o nome do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}

		//Extract the adress from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_customer_iss, adress, ';');
		RemoveSpacesFromPhrase(adress);
		if (adress.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler a morada do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}

		//Extract the NIF from the istringstream and check it's validity; if it's not valid, throw exception
		curr_customer_iss >> NIF;
		curr_customer_iss.ignore(INT_MAX, ';');

		if (curr_customer_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o NIF do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if ((NIF < 0) || !IsNifValid(NIF))
		{
			throw ErrorParsingFile("O NIF do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + "nao e valido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		unique_it = lower_bound(unique_nifs.begin(), unique_nifs.end(), NIF);
		//check if there are repeated nifs in the file (a nif must be unique)
		if (unique_it != unique_nifs.end())
		{
			if (*unique_it == NIF)
			{
				throw ErrorParsingFile("O nif de um cliente, lido do ficheiro na linha " + to_string(line_count + 1) + ", e igual ao de outro cliente ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
		}
		unique_nifs.insert(unique_it, NIF);

		//Extract the date from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_customer_iss >> regist_date;
			curr_customer_iss.ignore(INT_MAX, ';');
		}
		catch (Date::ErrorReadingDateFromStream &error)
		{
			cout << "Ocorreu um erro ao ler a data de registo do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.";
		}
		catch (Date::InvalidDate &error)
		{
			cout << "A data de registo do cliente com id " + to_string(id) + ", lida do ficheiro na linha " + to_string(line_count + 1) + ", e invalida.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.";
		}
		if (regist_date > windows_date)
		{
			throw ErrorParsingFile("A data de registo do cliente com id " + to_string(id) + ", lida do ficheiro na linha " + to_string(line_count + 1) + ", diz respeito a uma data posterior a do seu sistema.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}

		//Extract the points balance from the istringstream and check it's validity; if it's not valid, throw exception
		curr_customer_iss >> points_balance;
		curr_customer_iss.ignore(INT_MAX, ';');
		if (curr_customer_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o numero de pontos do cliente com id " + to_string(id) + "do ficheiro na linha " + to_string(line_count + 1) + ", e invalida.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if (points_balance < 0)
		{
			throw ErrorParsingFile("O numero de pontos do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		unsigned_points_balance = points_balance;

		//Extract the unpaid amount balance from the istringstream and check it's validity; if it's not valid, throw exception
		curr_customer_iss >> unpaid_amount;
		curr_customer_iss.ignore(INT_MAX, ';');
		if (curr_customer_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o numero de pontos do cliente com id " + to_string(id) + "do ficheiro na linha " + to_string(line_count + 1) + ", e invalida.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if (unpaid_amount < 0)
		{
			throw ErrorParsingFile("O numero de pontos do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}

		//Extract when the last trip of the customer ocurred (in unix format)
		curr_customer_iss >> last_trip_time;
		curr_customer_iss.ignore(INT_MAX, ';');
		if (curr_customer_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o tempo (em formato unix) em que ocorreu a ultima viagem do cliente com id " + to_string(id) + "do ficheiro na linha " + to_string(line_count + 1) + ", e invalida.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		else if (last_trip_time < 0)
		{
			throw ErrorParsingFile("O tempo (em formato unix) em que ocorreu a ultima viagems do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
		}
		curr_system_time = time(NULL); //get the system time in unix format (this access is performed at each customer read to ensure that no errors occur (in case the file takes longer than second to parse))
		if (curr_system_time == -1)
		{
			throw ErrorParsingFile("Ocorreu um erro ao obter o tempo do sistema. Tal informaçao é vital para o bom funcionamento do programa.\n Por favor reinicie o programa.", customers_fn);
		}
		inactive_time = curr_system_time - last_trip_time;

		CustomerDiscount discount;
		//check if the customer is considered inactive; if not, extract discount information
		time_t min_time_to_inactive;
		if (call_id == 0)
			min_time_to_inactive = ParticularCustomer::GetMinTimeToInactive();
		else
			min_time_to_inactive = BusinessCustomer::GetMinTimeToInactive();

		if (inactive_time < min_time_to_inactive)
		{
			//Extract information related to the discounts of this customer
			//Extract the amount in voucher from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> voucher;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o valor em voucher do cliente com id " + to_string(id) + "do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (voucher < 0)
			{
				throw ErrorParsingFile("O valor em voucher do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido (menor que 0).\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_voucher = voucher;

			//Extract the month in which the voucher is valid from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> voucher_valid_month;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o mes em que o voucher do cliente com id " + to_string(id) + ", e valido, lido do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if ((voucher_valid_month < 0) || (voucher_valid_month > 12))
			{
				throw ErrorParsingFile("O mes em que o voucher do cliente com id " + to_string(id) + ", e valido, lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_voucher_valid_month = voucher_valid_month;

			//Extract the year in which the voucher is valid from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> voucher_valid_year;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o ano em que o voucher do cliente com id " + to_string(id) + ", e valido, lido do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (voucher_valid_year < 0)
			{
				throw ErrorParsingFile("O ano em que o voucher do cliente com id " + to_string(id) + ", e valido, lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_voucher_valid_year = voucher_valid_year;

			//Extract the boolean that indicates if the customer has a free trip
			curr_customer_iss >> unsigned_free_trip;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o numero que identifica se o cliente com id " + to_string(id) + "tem direito a uma viagem gratuita, lido do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (unsigned_free_trip != 0 && unsigned_free_trip != 1)
			{
				throw ErrorParsingFile("O numero que identifica se se o cliente com id " + to_string(id) + " tem direito a uma viagem gratuita, lido do ficheiro na linha " + to_string(line_count + 1) + " e invalido.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			free_trip = unsigned_free_trip;

			//Extract the month in which the free trip is valid from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> free_trip_valid_month;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o mes em que a viagem gratuita do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if ((free_trip_valid_month < 0) || (free_trip_valid_month > 12))
			{
				throw ErrorParsingFile("O mes da viagem gratuita do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_free_trip_valid_month = free_trip_valid_month;


			//Extract the month in which the free trip is valid from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> free_trip_valid_year;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o ano em que a viagem gratuita do cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (free_trip_valid_year < 0)
			{
				throw ErrorParsingFile("O ano da viagem gratuita do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_free_trip_valid_year = free_trip_valid_year;

			//Extract the number of trips that the customer has done in the current month from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> num_trips;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o numero de viagens do mes atual do cliente com id " + to_string(id) + " na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (num_trips < 0)
			{
				throw ErrorParsingFile("O numero de viagens do mes atual do cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido (menor que 0).\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_num_trips = num_trips;

			//Extract the amount that the customer has paid in the current month from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> amount_paid;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o montante pago pelo cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (amount_paid < 0)
			{
				throw ErrorParsingFile("O montante pago pelo cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido (menor que 0).\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}

			//Extract the current month (the month to which the last two informations respect to) the customer has done in the current month from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> current_month;
			curr_customer_iss.ignore(INT_MAX, ';');
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o mes a que diz respeito o numero de viagens e o montante pago pelo cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if ((current_month < 0) || (current_month > 12))
			{
				throw ErrorParsingFile("O mes a que diz respeito o numero de viagens e o montante pago pelo cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_current_month = current_month;

			//Extract the current year (the year to which the last two informations respect to) the customer has done in the year month from the istringstream and check it's validity; if it's not valid, throw exception
			curr_customer_iss >> current_year;
			if (curr_customer_iss.fail())
			{
				throw ErrorParsingFile("Ocorreu um erro ao ler o ano a que diz respeito o numero de viagens e o montante pago pelo cliente com id " + to_string(id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			else if (current_year < 0)
			{
				throw ErrorParsingFile("O ano a que diz respeito o numero de viagens e o montante pago pelo cliente com id " + to_string(id) + ", lido do ficheiro na linha " + to_string(line_count + 1) + ", e invalido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", customers_fn);
			}
			unsigned_current_year = current_year;

			CustomerDiscount temp_discount(unsigned_voucher, unsigned_voucher_valid_month, unsigned_voucher_valid_year, free_trip, unsigned_free_trip_valid_month, unsigned_free_trip_valid_year, unsigned_num_trips, amount_paid, unsigned_current_month, unsigned_current_year);
			discount = temp_discount;
		}
		else //if the customer is considered inactive, don't extract any discounts information and leave it with the default values
		{
			CustomerDiscount temp_discount;
			discount = temp_discount;
		}

		//Build the class that will handle the new customer, append it to the vector of customers
		unsigned_id = id;
		Customer *customer;
		if (call_id == 0)
			customer = new ParticularCustomer(unsigned_id, name, adress, NIF, regist_date, unsigned_points_balance, unpaid_amount, last_trip_time, discount);
		else
			customer = new BusinessCustomer(unsigned_id, name, adress, NIF, regist_date, unsigned_points_balance, unpaid_amount, last_trip_time, discount);

		//Insert the customer in the correct (either on the active customers vector or the inactive customers hash table) place according to the time elapsed from the last trip
		if (inactive_time < min_time_to_inactive || last_trip_time == 0)
			customers.push_back(customer);
		else
			inactive_customers.insert(customer);

		if (unsigned_id > Customer::GetCurrCustId())
			Customer::SetCurrCustId(unsigned_id);

		//Clear the string stream to use in next iteration
		curr_customer_iss.clear();
	}

	if (num_of_customers != line_count)
	{
		num_of_customers = line_count;
		if (call_id == 0)
		{
			cout << "O numero de clientes particulares apresentado no inicio do ficheiro é inconsistente com o numero de clientes exixtentes" << endl;
			cout << "O numero de clientes particulares ira ser assumido como " << line_count << endl;
			customers_p_changed = true;
		}
		else
		{
			cout << "O numero de clientes empresariais apresentado no inicio do ficheiro é inconsistente com o numero de clientes exixtentes" << endl;
			cout << "O numero de clientes empresariais ira ser assumido como " << line_count << endl;
			customers_b_changed = true;
		}
	}

	if (call_id == 0)
		num_of_p_customers = line_count;
	else
		num_of_b_customers = line_count;

	if (num_of_customers == 0)
	{
		cout << "O numero de clientes foi indicado como 0 (zero). O programa nao carregou quaisquer clientes do ficheiro.\nUtilize a opcao do Menu Principal para adicionar clientes a empresa." << endl;
		return;
	}
	cout << endl;

	sort(customers.begin(), customers.end(), CompareCustomersNames);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseServices(ifstream &services_fs)
{
	int num_of_services; //the number of services that will be extracted from the file
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of services specified in the beggining of the file

	if (services_fs.peek() == std::ifstream::traits_type::eof())
	{
		cout << "O ficheiro de servicos esta vazio. O programa nao carregou quaisquer servicos do ficheiro.\nUtilize a opcao do Menu Principal para adicionar servicos a empresa." << endl;
		return;
	}

	services_fs >> num_of_services;
	services_fs.ignore(INT_MAX, ';');
	//Check if the number of customers was successfully read from the file
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero de servicos do ficheiro.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}

	float curr_static_float;

	//Extract the data that is common to every Service object (static members)

	//Extract base day price
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o preco base (bandeirada) do servico durante o dia do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("O preco base (bandeirada) do servico durante o dia lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetBasePriceDay(curr_static_float);

	//Extract base night price
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o preco base (bandeirada) do servico durante a noite do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("O preco base (bandeirada) do servico durante a noite lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetBasePriceNight(curr_static_float);

	//Extract average city speed
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler a velocidade media de cidade do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("A velocidade media de cidade lida do ficheiro e invalida na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetAverageSpeedCity(curr_static_float);

	//Extract average out of city speed
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler a velocidade media fora de cidade do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("A velocidade media fora de cidade lida do ficheiro e invalida na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetAverageSpeedOffCity(curr_static_float);

	//Extract price per minute
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o preco por minuto do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("O preco por minuto lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetPricePerMinute(curr_static_float);

	//Extract price per kilometer in day time
	services_fs >> curr_static_float;
	services_fs.ignore(INT_MAX, ';');
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o preco por kilometro durante o dia do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("O preco por kilometro durante o dia lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetPricePerKmDay(curr_static_float);

	//Extract price per kilometer in night time
	services_fs >> curr_static_float;
	if (services_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o preco por kilometro durante a noite do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	else if (curr_static_float < 0)
	{
		throw ErrorParsingFile("O preco por kilometro durante a noite lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
	}
	Service::SetPricePerKmNight(curr_static_float);


	CustomerHash::iterator customer_it;
	string curr_service_str;
	istringstream curr_service_iss;
	int service_id;
	int cust_id;
	int taxi_id;
	int cust_idx;
	int taxi_idx;
	string start;
	string finish;
	unsigned int day_distance;
	unsigned int night_distance;
	unsigned int elapsed_time;
	TimeStamp start_time;
	TimeStamp finish_time;
	float pre_price;
	float final_price;
	unsigned int unsigned_paid;
	bool paid;
	TimeStamp windows_time;
	GetTimeStampFromWindows(windows_time);
	vector<unsigned int> unique_ids;
	vector<unsigned int>::iterator unique_it;

	services_fs.ignore(INT_MAX, '\n');
	while (getline(services_fs, curr_service_str))
	{
		line_count++;
		start.clear();
		finish.clear();

		//Fill the input string stream curr_customer_iss with the content of the current line
		curr_service_iss.str(curr_service_str);

		//Extract the service id from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> service_id;
		curr_service_iss.ignore(INT_MAX, ';');

		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id do servico do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (service_id < 0)
		{
			throw ErrorParsingFile("O id do servico lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		unique_it = lower_bound(unique_ids.begin(), unique_ids.end(), service_id);
		//check if there are repeated ids in the file (an id must be unique)
		if (unique_it != unique_ids.end())
		{
			if (*unique_it == service_id)
			{
				throw ErrorParsingFile("O id de um servico, lido do ficheiro na linha " + to_string(line_count + 1) + ", e igual ao de outro servico ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
			}
		}
		unique_ids.insert(unique_it, service_id);

		//Extract the id of the costumer to which service respects to from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> cust_id;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id do servico do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (cust_id < 0)
		{
			throw ErrorParsingFile("O id de um cliente lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		if (!SearchForCustId(cust_id, cust_idx, customer_it))
			throw ErrorParsingFile("Nao existe o cliente com o id " + to_string(cust_id) + " lido do ficheiro de servicos na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		//Extract the id of the taxi to which service respects to from the istringstream and check it's validity; if it's not valid, throw exception

		curr_service_iss >> taxi_id;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id do taxi a que diz respeito o servico com id " + to_string(line_count + 1) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (taxi_id < 0)
		{
			throw ErrorParsingFile("O id de um taxi a que diz respeito o servico com id " + to_string(line_count + 1) + ",lido do ficheiro, e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		if ((taxi_idx = SearchForTaxiId(taxi_id)) == -1)
		{
			throw ErrorParsingFile("O id de um taxi a que diz respeito o servico com id " + to_string(line_count + 1) + ", lido do ficheiro, nao existe, na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		Taxi *taxi = taxis[taxi_idx];

		//Extract the start adress from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_service_iss, start, ';');
		RemoveSpacesFromPhrase(start);
		if (start.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o endereco inicial do servico com id " + to_string(service_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the finish adress from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_service_iss, finish, ';');
		RemoveSpacesFromPhrase(finish);
		if (finish.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o endereco inicial do servico com id" + to_string(service_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the distance traveled by day of the service from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> day_distance;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, a distancia percorrida durante o dia no servico, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (day_distance < 0)
		{
			throw ErrorParsingFile("A distancia percorrida durante o dia no servico, lida do ficheiro e invalida na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the distance traveled by night of the service from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> night_distance;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, a distancia percorrida durante a noite no servico, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (night_distance < 0)
		{
			throw ErrorParsingFile("A distancia percorrida durante a noite no servico, lida do ficheiro e invalida na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the elpsed time of the service from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> elapsed_time;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, o tempo gasto no servico, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (elapsed_time < 0)
		{
			throw ErrorParsingFile("O tempo gasto no servico, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the start time of the service from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_service_iss >> start_time;
			curr_service_iss.ignore(INT_MAX, ';');
		}
		catch (TimeStamp::ErrorReadingTimeStampFromStream &error)
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o tempo de inicio de um servico do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		catch (TimeStamp::InvalidTimeStamp &error)
		{
			throw ErrorParsingFile("O tempo de inicio de um servico, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the finish time of the service from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_service_iss >> finish_time;
			curr_service_iss.ignore(INT_MAX, ';');
		}
		catch (TimeStamp::ErrorReadingTimeStampFromStream &error)
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o tempo de fim de um servico do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		catch (TimeStamp::InvalidTimeStamp & error)
		{
			throw ErrorParsingFile("O tempo de fim de um servico, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		if (start_time >= finish_time)
		{
			throw ErrorParsingFile("O tempo de fim de um servico diz respeito a uma data/hora anterior ao tempo de inicio, lido do ficheiro, na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		if (finish_time > windows_time)
		{
			throw ErrorParsingFile("O tempo de fim de um servico diz respeito a uma data/hora posterior ao tempo do sistema, lido do ficheiro, na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the pre price of the service from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> pre_price;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, o preco inicial do servico, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (pre_price < 0)
		{
			throw ErrorParsingFile("O preco inicial do servico, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the final price of the service from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> final_price;
		curr_service_iss.ignore(INT_MAX, ';');
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, o preco final do servico, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (final_price < 0)
		{
			throw ErrorParsingFile("O preco final do servico, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}

		//Extract the bool that indicates if the service has been already from the istringstream and check it's validity; if it's not valid, throw exception
		curr_service_iss >> unsigned_paid;
		if (curr_service_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler, o numero que indica se o servico esta pago, do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		else if (unsigned_paid != 0 && unsigned_paid != 1)
		{
			throw ErrorParsingFile("O numero que indica se o servico esta pago, lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", services_fn);
		}
		paid = unsigned_paid;


		//Build the class that will handle the new service, append it to the vector of services
		unsigned int unsigned_service_id = service_id;
		Service service(unsigned_service_id, start, finish, day_distance, night_distance, elapsed_time, start_time, finish_time, taxi, pre_price, final_price, paid);

		if (cust_idx != -1)
		{
			customers[cust_idx]->AppendService(service);
		}
		else
		{
			(*customer_it)->AppendService(service);
		}

		if (unsigned_service_id > Service::GetCurrServiceId())
			Service::SetCurrServiceId(unsigned_service_id);

		//Clear the string stream to use in next iteration
		curr_service_iss.clear();
	}

	unsigned int customers_size = customers.size();
	unsigned int services_size;
	//Sort all the services of each active customer and Add the respective invoices to the BST.
	for (unsigned int cust_idx = 0; cust_idx < customers_size; cust_idx++)
	{
		customers[cust_idx]->SortServices();
		services_size = customers[cust_idx]->GetServicesSize();
		for (unsigned int serv_idx = 0; serv_idx < services_size; serv_idx++)
			AddInvoice(customers[cust_idx], serv_idx);
	}

	//Sort all the services of each inactive customer and Add the respective invoices to the BST.
	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		(*it)->SortServices();
		services_size = (*it)->GetServicesSize();
		for (unsigned int serv_idx = 0; serv_idx < services_size; serv_idx++)
			AddInvoice(*it, serv_idx);
	}

	if (num_of_services != line_count)
	{
		cout << "O numero de servicos apresentado no inicio do ficheiro é inconsistente com o numero de servicos exixtentes" << endl;
		cout << "O numero de servicos ira ser assumido como " << line_count << endl;
		num_of_services = line_count;
		services_changed = true;
	}

	this->num_of_services = num_of_services;

	if (num_of_services == 0)
	{
		cout << "O numero de servicos foi indicado como 0 (zero). O programa nao carregou quaisquer servicos do ficheiro.\nUtilize a opcao do Menu Principal para adicionar clientes a empresa." << endl;
		return;
	}
	cout << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseTaxis(ifstream &taxis_fs)
{
	int num_of_taxis; //the number of taxis that will be extracted from the file
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of taxis specified in the beggining of the file

	if (taxis_fs.peek() == std::ifstream::traits_type::eof())
	{
		cout << "O ficheiro de taxis esta vazio. O programa nao carregou quaisquer taxis do ficheiro.\nUtilize a opcao do Menu Principal para adicionar taxis a empresa." << endl;
		return;
	}

	taxis_fs >> num_of_taxis;

	//Check if the number of taxis was successfully read from the file
	if (taxis_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero de taxis do ficheiro.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
	}

	string curr_taxi_str;
	istringstream curr_taxi_iss;
	int id;
	unsigned int unsigned_id;
	Driver driver;
	Date regist_date;
	int km;
	unsigned int unsigned_km;
	int num_of_seats;
	unsigned int unsigned_num_of_seats;
	LicensePlate license_plate;
	Date windows_date;
	GetDateFromWindows(windows_date);
	vector<unsigned int> unique_ids;
	vector<LicensePlate> unique_plates;
	vector<unsigned int>::iterator unique_ids_it;
	vector<LicensePlate>::iterator unique_plates_it;

	taxis_fs.ignore(INT_MAX, '\n');
	while (getline(taxis_fs, curr_taxi_str))
	{
		line_count++;

		//Fill the input string stream curr_taxi_iss with the content of the current line
		curr_taxi_iss.str(curr_taxi_str);

		//Extract the id from the istringstream and check it's validity; if it's not valid, throw exception
		curr_taxi_iss >> id;
		curr_taxi_iss.ignore(INT_MAX, ';');
		if (curr_taxi_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id de um taxi do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		else if (id < 0)
		{
			throw ErrorParsingFile("O id de um taxi lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		unique_ids_it = lower_bound(unique_ids.begin(), unique_ids.end(), id);
		//check if there are repeated ids in the file (an id must be unique)
		if (unique_ids_it != unique_ids.end())
		{
			if (*unique_ids_it == id)
			{
				throw ErrorParsingFile("O id de um taxi, lido do ficheiro de taxis na linha " + to_string(line_count + 1) + ", e igual ao de outro taxi ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
			}
		}
		unique_ids.insert(unique_ids_it, id);
		unsigned_id = id;

		//Extract the number of kilometers traveled by the taxi from the istringstream and check it's validity; if it's not valid, throw exception
		curr_taxi_iss >> km;
		curr_taxi_iss.ignore(INT_MAX, ';');
		if (curr_taxi_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o numero de kilometros percorridos por um taxi do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		else if (km < 0)
		{
			throw ErrorParsingFile("O numero de kilometros percorridos por um taxi lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}

		//Extract the number of seats of the taxi from the istringstream and check it's validity; if it's not valid, throw exception
		curr_taxi_iss >> num_of_seats;
		curr_taxi_iss.ignore(INT_MAX, ';');
		if (curr_taxi_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o nuemro de lugares de um taxi do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		else if (num_of_seats < 0)
		{
			throw ErrorParsingFile("O numero de lugares de um taxi lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}

		//Extract the license plate from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_taxi_iss >> license_plate;
			curr_taxi_iss.ignore(INT_MAX, ';');
		}
		catch (LicensePlate::ErrorReadingLicensePlate &error)
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler a matricula de um taxi do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		catch (LicensePlate::InvalidLicensePlate &error)
		{
			throw ErrorParsingFile("A matricula de um taxi lida do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		unique_plates_it = lower_bound(unique_plates.begin(), unique_plates.end(), license_plate);
		//check if there are repeated license plate in the file (an id must be unique)
		if (unique_plates_it != unique_plates.end())
		{
			if (*unique_plates_it == license_plate)
			{
				throw ErrorParsingFile("A matricula de um taxi, lida do ficheiro de taxis na linha " + to_string(line_count + 1) + ", e igual a de outro taxi ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
			}
		}
		unique_plates.insert(unique_plates_it, license_plate);

		//Extract the registration date from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_taxi_iss >> regist_date;
		}
		catch (Date::ErrorReadingDateFromStream &error)
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler a data de registo de um taxi do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		catch (Date::InvalidDate &error)
		{
			throw ErrorParsingFile("A data de registo de um taxi lida do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}
		if (regist_date > windows_date)
		{
			throw ErrorParsingFile("A data de registo do taxi com id " + to_string(id) + ", lida do ficheiro na linha " + to_string(line_count + 1) + ", diz respeito a uma data posterior a do seu sistema.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", taxis_fn);
		}

		//Build the class that will handle the new taxi, append it to the vector of taxis
		unsigned_id = id;
		unsigned_km = km;
		unsigned_num_of_seats = num_of_seats;
		Taxi *taxi = new Taxi(unsigned_id, driver, unsigned_km, unsigned_num_of_seats, license_plate, regist_date);
		taxis.push_back(taxi);

		if (unsigned_id > Taxi::GetCurrTaxiId())
			Taxi::SetCurrTaxiId(unsigned_id);

		//Clear the string stream to use in next iteration
		curr_taxi_iss.clear();
	}

	if (num_of_taxis != line_count)
	{
		cout << "O numero de taxis apresentado no inicio do ficheiro é inconsistente com o numero de taxis exixtentes" << endl;
		cout << "O numero de taxis ira ser assumido como " << line_count << endl;
		num_of_taxis = line_count;
		taxis_changed = true;
	}

	if (num_of_taxis == 0)
	{
		cout << "O numero de taxis foi indicado como 0 (zero). O programa nao carregou quaisquer taxis do ficheiro.\nUtilize a opcao do Menu Principal para adicionar taxis a empresa." << endl;
		return;
	}
	cout << endl;

	sort(taxis.begin(), taxis.end(), CompareTaxisIds);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ParseDrivers(ifstream &drivers_fs)
{
	int num_of_drivers; //the number of drivers that will be extracted from the file
	unsigned int line_count = 0; //this variable counts the number of lines in the file to check if it corresponds to the number of drivers specified in the beggining of the file

	if (drivers_fs.peek() == std::ifstream::traits_type::eof())
	{
		cout << "O ficheiro de condutors esta vazio. O programa nao carregou quaisquer condutors do ficheiro.\nUtilize a opcao do Menu Principal para adicionar condutors a empresa." << endl;
		return;
	}

	drivers_fs >> num_of_drivers;
	//Check if the number of customers was successfully read from the file
	if (drivers_fs.fail())
	{
		throw ErrorParsingFile("Ocorreu um erro ao ler o numero de condutors do ficheiro.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
	}

	unsigned int taxi_idx;
	string curr_driver_str;
	istringstream curr_driver_iss;
	int driver_id;
	unsigned int unsigned_driver_id;
	int taxi_id;
	unsigned int unsigned unsigned_taxi_id;
	string name;
	string adress;
	int NIF;
	unsigned int unsigned_NIF;
	Date regist_date;
	Date windows_date;
	int drivers_license;
	unsigned int unsigned_drivers_license;
	GetDateFromWindows(windows_date);
	vector<unsigned int> unique_driver_ids;
	vector<unsigned int> unique_taxi_ids;
	vector<unsigned int> unique_driver_nifs;
	vector<unsigned int>::iterator unique_it;

	drivers_fs.ignore(INT_MAX, '\n');
	while (getline(drivers_fs, curr_driver_str))
	{
		line_count++;
		name.clear();
		adress.clear();

		//Fill the input string stream curr_driver_iss with the content of the current line
		curr_driver_iss.str(curr_driver_str);

		//Extract the driver id from the istringstream and check it's validity; if it's not valid, throw exception
		curr_driver_iss >> driver_id;
		curr_driver_iss.ignore(INT_MAX, ';');
		if (curr_driver_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id do condutor do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		else if (driver_id < 0)
		{
			throw ErrorParsingFile("O id do condutor lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		unique_it = lower_bound(unique_driver_ids.begin(), unique_driver_ids.end(), driver_id);
		//check if there are repeated ids in the file (an id must be unique)
		if (unique_it != unique_driver_ids.end())
		{
			if (*unique_it == driver_id)
			{
				throw ErrorParsingFile("O id de um condutor, lido do ficheiro de condutores na linha " + to_string(line_count + 1) + ", e igual ao de outro condutor ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
			}
		}
		unique_driver_ids.insert(unique_it, driver_id);
		unsigned_driver_id = driver_id;

		//Extract the id of the taxi to which the driver respects to from the istringstream and check it's validity; if it's not valid, throw exception
		curr_driver_iss >> taxi_id;
		curr_driver_iss.ignore(INT_MAX, ';');
		if (curr_driver_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o id do taxi ao qual o condutor diz respeito do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		else if (taxi_id < 0)
		{
			throw ErrorParsingFile("O id do taxi ao qual o condutor diz respeito lido do ficheiro e invalido na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		unique_it = lower_bound(unique_taxi_ids.begin(), unique_taxi_ids.end(), taxi_id);
		//check if there are repeated ids in the file (an id must be unique)
		if (unique_it != unique_taxi_ids.end())
		{
			if (*unique_it == taxi_id)
			{
				throw ErrorParsingFile("O id de um taxi, lido do ficheiro de condutores na linha " + to_string(line_count + 1) + ", e igual ao de outro taxi ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
			}
		}
		unique_taxi_ids.insert(unique_it, taxi_id);

		//Extract the name from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_driver_iss, name, ';');
		RemoveSpacesFromPhrase(name);
		if (name.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o nome do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}

		//Extract the adress from the istringstream and check it's validity; if it's not valid, throw exception
		getline(curr_driver_iss, adress, ';');
		RemoveSpacesFromPhrase(adress);
		if (adress.empty())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler a morada do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}

		//Extract the NIF from the istringstream and check it's validity; if it's not valid, throw exception
		curr_driver_iss >> NIF;
		curr_driver_iss.ignore(INT_MAX, ';');

		if (curr_driver_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o NIF do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		else if ((NIF < 0) || !IsNifValid(NIF))
		{
			throw ErrorParsingFile("O NIF do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + "nao e valido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		unique_it = lower_bound(unique_driver_nifs.begin(), unique_driver_nifs.end(), NIF);
		//check if there are repeated nifs in the file (a nif must be unique)
		if (unique_it != unique_driver_nifs.end())
		{
			if (*unique_it == NIF)
			{
				throw ErrorParsingFile("O nif de um condutor, lido do ficheiro na linha " + to_string(line_count + 1) + ", e igual ao de outro condutor ja lido anteriormente.\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
			}
		}
		unique_driver_nifs.insert(unique_it, NIF);

		//Extract the date from the istringstream and check it's validity; if it's not valid, throw exception
		try
		{
			curr_driver_iss >> regist_date;
			curr_driver_iss.ignore(INT_MAX, ';');
		}
		catch (Date::ErrorReadingDateFromStream &error)
		{
			cout << "Ocorreu um erro ao ler a data de registo do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.";
		}
		catch (Date::InvalidDate &error)
		{
			cout << "A data de registo do condutor com id " + to_string(driver_id) + ", lida do ficheiro na linha " + to_string(line_count + 1) + ", e invalida.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.";
		}
		if (regist_date > windows_date)
		{
			throw ErrorParsingFile("A data de registo do condutor com id " + to_string(driver_id) + ", lida do ficheiro na linha " + to_string(line_count + 1) + ", diz respeito a uma data posterior a do seu sistema.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}

		//Extract the driver's license number from the istringstream and check it's validity; if it's not valid, throw exception
		curr_driver_iss >> drivers_license;
		if (curr_driver_iss.fail())
		{
			throw ErrorParsingFile("Ocorreu um erro ao ler o numero da carta de conducao do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}
		else if (drivers_license < 0 || to_string(drivers_license).length() != 9)
		{
			throw ErrorParsingFile("O numero da carta de conducao do condutor com id " + to_string(driver_id) + " do ficheiro na linha " + to_string(line_count + 1) + "nao e valido.\nPor favor verifique a validade do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		}

		//Build the class that will handle the new driver, append it to the vector of drivers
		unsigned int unsigned_driver_id = driver_id;
		Driver driver(unsigned_driver_id, name, adress, NIF, regist_date, drivers_license);
		if ((taxi_idx = SearchForTaxiId(taxi_id)) == -1)
			throw ErrorParsingFile("Nao existe o taxi com o id " + to_string(taxi_id) + " lido do ficheiro de condutors na linha " + to_string(line_count + 1) + ".\nPor favor verifique a validade da informacao do ficheiro introduzido.\nO programa ira terminar.", drivers_fn);
		taxis[taxi_idx]->SetDriver(driver);

		//Initialize Taxis_queue
		if (!driver.GetName().empty())
			taxis_queue.push(taxis[taxi_idx]);

		if (unsigned_driver_id > Driver::GetCurrDriverId())
			Driver::SetCurrDriverId(unsigned_driver_id);

		//Clear the string stream to use in next iteration
		curr_driver_iss.clear();
	}

	if (num_of_drivers != line_count)
	{
		cout << "O numero de condutors apresentado no inicio do ficheiro é inconsistente com o numero de condutors exixtentes" << endl;
		cout << "O numero de condutors ira ser assumido como " << line_count << endl;
		num_of_drivers = line_count;
		drivers_changed = true;
	}

	this->num_of_drivers = num_of_drivers;

	if (num_of_drivers == 0)
	{
		cout << "O numero de condutors foi indicado como 0 (zero). O programa nao carregou quaisquer condutors do ficheiro.\nUtilize a opcao do Menu Principal para adicionar clientes a empresa." << endl;
		return;
	}
	cout << endl;
}

//---------------------------------------Class Customer---------------------------------------
bool EmpresaDeTaxis::IsParticularCustomer(Customer* customer) const
{
	ParticularCustomer *p = dynamic_cast<ParticularCustomer *> (customer);
	if (p != NULL)
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::AddCustomer()
{
	cout << "Se pretende adicionar um cliente particular, introduza 0.\nSe pretende adicionar um cliente empresarial, introduza 1.\n";
	string error_msg = "Ocorreu um erro ao ler a sua opcao de cliente que introduziu. Por favor, tente novamente, introduzindo uma opcao valida: ";
	int call_id = ReadUnsignedInt(error_msg);

	cout << "Introduza o nome do cliente que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler o nome de cliente que introduziu. Por favor, tente novamente, introduzindo um nome valido: ";
	string name = ReadString(error_msg);

	cout << "Introduza a morada do cliente que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler a morada de cliente que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string adress = ReadString(error_msg);

	cout << "Introduza o NIF do cliente que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler o NIF do cliente que introduziu. Por favor, tente novamente, introduzindo um NIF valido: ";
	int unused_idx;
	CustomerHash::iterator unused_it;
	unsigned int nif = ReadUnsignedInt(error_msg);
	while (true)
	{
		if (SearchForCustNIF(nif, unused_idx, unused_it))
			cout << "O nif introduzido ja esta associada a outro cliente. Verifique a validade do mesmo: ";
		else if (IsNifValid(nif) == false)
			cout << "O nif introduzido e invalido. Verifique a validade do mesmo: ";
		else
			break;

		nif = ReadUnsignedInt(error_msg);
	}

	Customer *new_customer;
	if (call_id == 0)
		new_customer = new ParticularCustomer(name, adress, nif);
	else
		new_customer = new BusinessCustomer(name, adress, nif);

	auto it = lower_bound(customers.begin(), customers.end(), new_customer, CompareCustomersNames);
	customers.insert(it, new_customer);

	if (call_id == 0)
	{
		customers_p_changed = true;
		num_of_p_customers++;
	}
	else
	{
		customers_b_changed = true;
		num_of_b_customers++;
	}

	cout << endl << "O cliente foi adicionado com sucesso." << endl << endl;
}
//------------------------------------------------------------------------------
//Reads a Customer id from user and calls the function that removes it
void EmpresaDeTaxis::RemoveCustomerById()
{
	cout << "Introduza o id do cliente que pretende remover: ";
	unsigned int idx;
	CustomerHash::iterator it;
	ReadCustomerId(idx, it);
	EraseCustomer(idx, it);
}
//------------------------------------------------------------------------------
//Reads a Customer name from user and calls the function that removes it
void EmpresaDeTaxis::RemoveCustomerByName()
{
	cout << "Introduza o nome do cliente que pretende remover: ";
	unsigned int lower_idx = 0, upper_idx = 0;
	vector<CustomerHash::iterator> cust_its;
	ReadCustomerName(lower_idx, upper_idx, cust_its);
	unsigned int cust_its_size = cust_its.size();

	if ((upper_idx - lower_idx + 1) + cust_its_size > 1)  //if the sum of the active customers and the inactive customers with the given name is higher than one, show the customers in those conditions and remove by id (that´s an unique identifier)
	{
		for (unsigned int i = lower_idx; i <= upper_idx; i++)
			cout << *(customers[lower_idx]) << endl;

		for (unsigned int i = 0; i < cust_its_size; i++)
			cout << *cust_its[i] << endl;

		RemoveCustomerById();
	}
	else
	{
		CustomerHash::iterator it;
		if (!cust_its.empty())
			it = cust_its[0];
		EraseCustomer(lower_idx, it);
	}
}
//------------------------------------------------------------------------------
//Receives a Customer id removes it; It also sets the flag that indicates if a particular customer or a business customer was changed
void EmpresaDeTaxis::EraseCustomer(int cust_idx, CustomerHash::iterator it)
{
	Customer *customer;
	BSTItrIn<Invoice> iterator(invoices);
	if (cust_idx != -1)
	{
		customer = customers[cust_idx];
		customers.erase(customers.begin() + cust_idx);
	}
	else
	{
		customer = (*it);
		inactive_customers.erase(*it);
	}

	//Eliminate the invoices of the erased customer
	Invoice invoice(customer, 0);
	unsigned int services_size = customer->GetServicesSize();
	for (unsigned int i = 0; i < services_size; i++)
	{
		invoice.SetServiceIdx(i);
		invoices.remove(invoice);
	}

	if (IsParticularCustomer(customer))
	{
		customers_p_changed = true;
		num_of_p_customers--;
	}
	else
	{
		customers_p_changed = true;
		num_of_b_customers--;
	}
	services_changed = true;

	//Delete the alocated memory for the customer that was erased
	delete customer;

	cout << endl << "O cliente foi removido com sucesso." << endl << endl;
}
//------------------------------------------------------------------------------
//Reads a Customer id whose adress will be changed
void EmpresaDeTaxis::ChangeCustomerAdressById()
{
	cout << "Introduza o id do cliente cuja morada pretende alterar: ";
	unsigned int idx;
	CustomerHash::iterator it;
	ReadCustomerId(idx, it);
	ChangeCustomerAdress(idx, it);
}
//------------------------------------------------------------------------------
//Reads a Customer name whose adress will be changed
void EmpresaDeTaxis::ChangeCustomerAdressByName()
{
	cout << "Introduza o nome do cliente cuja morada pretende alterar: ";
	string error_msg = "Ocorreu um erro ao ler o nome do cliente que introduziu. Por favor, tente novamente, introduzindo um nome valido: ";
	unsigned int lower_idx = 0, upper_idx = 0;
	vector<CustomerHash::iterator> cust_its;
	ReadCustomerName(lower_idx, upper_idx, cust_its);
	unsigned int cust_its_size = cust_its.size();

	if ((upper_idx - lower_idx + 1) + cust_its_size > 1)  //if the sum of the active customers and the inactive customers with the given name is higher than one, show the customers in those conditions and remove by id (that´s an unique identifier)
	{
		for (unsigned int i = lower_idx; i <= upper_idx; i++)
			cout << *(customers[lower_idx]) << endl;

		for (unsigned int i = 0; i < cust_its_size; i++)
			cout << *cust_its[i] << endl;

		ChangeCustomerAdressById();
	}
	else
	{
		CustomerHash::iterator it;
		if (!cust_its.empty())
			it = cust_its[0];

		ChangeCustomerAdress(lower_idx, it);
	}
}
//------------------------------------------------------------------------------
//Changes a customer adress
void EmpresaDeTaxis::ChangeCustomerAdress(int cust_idx, CustomerHash::iterator it)
{
	cout << "Introduza a nova morada do cliente: ";
	string error_msg = "Ocorreu um erro ao ler a morada do cliente que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string new_adress = ReadString(error_msg);
	Customer *cust;

	if (cust_idx != -1)
	{
		cust = customers[cust_idx];
		customers[cust_idx]->SetAdress(new_adress);
	}
	else
	{
		cust = *it;
		(*it)->SetAdress(new_adress);
	}

	if (IsParticularCustomer(cust))
		customers_p_changed = true;
	else
		customers_b_changed = true;

	cout << endl << "A morada do cliente foi alterada com sucesso." << endl << endl;
}
//----------------------------------------------Class Service--------------------------------
void EmpresaDeTaxis::AddRequestToRegisteredCustomer()
{
	if (taxis_queue.empty())
	{
		cout << "Nao existem taxis na empresa. Pode adicionar taxis usando a opçao do menu." << endl;
		return;
	}

	cout << "Introduza o id do cliente: ";
	unsigned int customer_idx;
	CustomerHash::iterator it;
	ReadCustomerId(customer_idx, it);
	Customer *customer;

	if (customer_idx == -1)
	{
		customer = *it;
		customer_idx = MoveCustomerToVector(customer);
	}

	AddRequest(customer_idx);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::AddRequest(unsigned int customer_idx)
{
	if (taxis_queue.empty())
	{
		cout << "Nao existem taxis na empresa. Pode adicionar taxis usando a opçao do menu." << endl;
		return;
	}

	Taxi *taxi = taxis_queue.top().GetTaxi();
	time_t time_when_available = taxi->GetTimeWhenAvailable();
	time_t curr_time = time(NULL);
	if (curr_time == -1)
		throw ErrorGettingLocalTime();
	time_t time_to_be_available = time_when_available - curr_time;
	if (time_to_be_available > 0)
	{
		requests_queue.push(customers[customer_idx]);
		string neat_time_stamp = MakeNeatTimeStampFromSeconds(time_to_be_available);
		cout << "O taxi " << taxi->GetId() << " estara disponivel em " << neat_time_stamp << "." << endl;
	}
	else
		AddService(customers[customer_idx], taxi);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ProcessAllWaitingRequests()
{
	if (requests_queue.empty())
	{
		cout << "Todos os pedidos ja foram atendidos" << endl;
		return;
	}
	if (taxis_queue.empty())
	{
		cout << "Nao existem taxis na empresa. Pode adicionar taxis usando a opçao do menu." << endl;
		return;
	}

	Customer *customer;
	Taxi *taxi;
	time_t time_when_available;
	time_t curr_time;
	while (!requests_queue.empty())
	{
		taxi = taxis_queue.top().GetTaxi();
		time_when_available = taxi->GetTimeWhenAvailable();
		curr_time = time(NULL);
		if (curr_time == -1)
			throw ErrorGettingLocalTime();
		time_t time_to_be_available = time_when_available - curr_time;
		if (time_to_be_available > 0)
		{
			cout << "Ainda existem " << requests_queue.size() << " pedidos por processar." << endl;
			string neat_time_stamp = MakeNeatTimeStampFromSeconds(time_to_be_available);
			cout << "No entanto, so existe um taxi disponivel em " << neat_time_stamp << endl << endl;
			return;
		}

		ClearScreen();
		customer = requests_queue.front();

		string name_to_present;
		if (customer->GetName().empty())
			name_to_present = " ocasional";
		else
			name_to_present = customer->GetName();

		cout << "Pedido do cliente " << name_to_present << " :" << endl;
		AddService(customer, taxi);
		requests_queue.pop();
	}

	cout << endl << "Todos os pedidos ja foram atendidos" << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::AddService(Customer *customer, Taxi *taxi)
{
	taxis_queue.pop();

	if (customer->GetId() != 0)
		if (customer->VerifyUnpaidAmount() == false) //if the registered customer has trips to pay from past months, he needs to pay them before being able to make a trip
			return;

	cout << "Introduza a morada de inicio da viagem: ";
	string error_msg = "Ocorreu um erro ao ler a morada de inicio da viagem que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string start = ReadString(error_msg);

	cout << "Introduza a morada de destino da viagem: ";
	error_msg = "Ocorreu um erro ao ler a morada do destino que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string finish = ReadString(error_msg);

	cout << "Introduza a distancia percorrida durante o dia na viagem: ";
	error_msg = "Ocorreu um erro ao ler distancia percorrida de dia que introduziu. Por favor, tente novamente, introduzindo uma distancia valida: ";
	unsigned int day_distance = ReadUnsignedInt(error_msg);

	cout << "Introduza a distancia percorrida durante a noite na viagem: ";
	error_msg = "Ocorreu um erro ao ler distancia percorrida de noite que introduziu. Por favor, tente novamente, introduzindo uma distancia valida: ";
	unsigned int night_distance = ReadUnsignedInt(error_msg);

	cout << "Introduza o tempo de duracao da viagem: ";
	error_msg = "Ocorreu um erro ao ler o tempo de duracao da viagem que introduziu. Por favor, tente novamente, introduzindo um tempo valida: ";
	time_t trip_duration = ReadUnsignedInt(error_msg) * 60;

	Service service(start, finish, day_distance, night_distance, trip_duration, taxi);

	taxi->IncrementKm(service.GetDistance());

	taxi->UpdateTimeWhenAvailable(service.GetDuration());
	taxis_queue.push(taxi);

	customer->AppendService(service);
	float price = customer->MakePayment();

	if (price != 0)
	{
		SelectPaymentMethod(customer, price);
	}
	AddInvoice(customer, customer->GetServicesSize() - 1);

	num_of_services++;
	services_changed = true;
	if (IsParticularCustomer(customer))
		customers_p_changed = true;
	else
		customers_b_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SelectPaymentMethod(Customer *customer, float price)
{
	cout << "1 - Pagamento em numerario." << endl;
	cout << "2 - Pagamento com cartao multibanco." << endl;
	if (customer->GetId() != 0) // if customer_idx = 0 it's an unregistered customer, else is a registered customer
	{
		cout << "3 - Pagamento com cartao de credito." << endl;
		cout << "4 - Pagamento no final do mes." << endl;
	}
	cout << "Escreva o numero da opcao pretendida: ";

	int option;
	bool error;
	do
	{
		error = false;
		string error_msg = "Ocorreu um erro ao ler a opcao que introduziu. Por favor, tente novamente, introduzindo uma opcao valida: ";
		option = ReadUnsignedInt(error_msg);
		switch (option)
		{
		case 1:
			PayInCash(price);
			break;
		case 2:
			PayWithATM(price);
			break;
		case 3:
			if (customer->GetId() == 0)
			{
				error = true;
				cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
			}
			else
			{
				PayWithCreditCard(price);
			}
			break;
		case 4:
			if (customer->GetId() == 0)
			{
				error = true;
				cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
			}
			else
			{
				PostponePayment(customer, price);
			}
			break;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::PayInCash(float price)
{
	cout << "O valor a pagar pelo servico e: " << price << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::PayWithATM(float price)
{
	cout << "O valor a pagar pelo servico e: " << price << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::PayWithCreditCard(float price)
{
	price = roundf(price * 1.05 * 100) / 100;
	cout << "O valor a pagar pelo servico e: " << price << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::PostponePayment(Customer *customer, float price)
{
	customer->SubPoints(price);
	price = roundf(price * 1.02 * 100) / 100;
	cout << "O valor a pagar pelo servico e: " << price << endl;
	cout << "Deve pagar este servico e os restantes ate ao final do mes na nossa empresa" << endl << endl;
	customer->PostPoneLastServicePayment(price);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::LiquidateCustAmount()
{
	cout << "Introduza o id do cliente que pretende liquidar o valor em divida: ";
	unsigned int cust_idx;
	CustomerHash::iterator it;
	ReadCustomerId(cust_idx, it);

	float amount_to_pay;
	if (cust_idx != -1)
		amount_to_pay = customers[cust_idx]->GetUnPaidAmount();
	else
		amount_to_pay = (*it)->GetUnPaidAmount();

	if (amount_to_pay == 0)
	{
		cout << endl << endl << "O cliente tem todos os servicos liquidados." << endl;
		return;
	}

	cout << "O valor a pagar e: " << amount_to_pay << endl;
	if (cust_idx != -1)
		customers[cust_idx]->SetAllServicesAsPaid();
	else
		(*it)->SetAllServicesAsPaid();
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::AddInvoice(const Customer *customer, unsigned int service_idx)
{
	Invoice new_invoice(customer, service_idx);
	invoices.insert(new_invoice);
}

//-----------------------------------Class Taxi-------------------------------------------
void EmpresaDeTaxis::AddTaxi()
{
	cout << "Introduza o numero de lugares do taxi: ";
	string error_msg = "Ocorreu um erro ao ler o numero de lugares que introduziu. Por favor, tente novamente, introduzindo um numero valido: ";
	unsigned int num_of_seats = ReadUnsignedInt(error_msg);

	LicensePlate plate;
	cout << "Introduza a matricula do taxi (no formato xx-xx-xx mm/aaaa): ";
	ReadLicensePlate(plate);
	while (SearchForTaxiLicensePlate(plate) != -1)
	{
		cout << "A matricula introduzida ja esta associada a outro taxi. Por favor, tente novamente introduzindo uma matricula valida: ";
		ReadLicensePlate(plate);
	}

	Taxi *taxi = new Taxi(plate, 0, num_of_seats);
	taxis.push_back(taxi);

	taxis_changed = true;

	cout << endl << "O taxi foi adicionado com sucesso." << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::RemoveTaxiByLicensePlate()
{
	cout << "Introduza a matricula do taxi que pretende remover: ";
	LicensePlate plate;
	unsigned int taxi_idx = ReadTaxiLicensePlate(plate);

	EraseTaxi(taxi_idx);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::RemoveTaxiById()
{
	cout << "Introduza o id do taxi que pretende remover: ";
	string error_msg = "Ocorreu um erro ao ler o id do taxi que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int taxi_idx = ReadTaxiId();

	EraseTaxi(taxi_idx);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::EraseTaxi(unsigned int taxi_idx)
{
	vector<Taxi*> temp;

	while (!taxis_queue.empty())
	{
		if (taxis_queue.top().GetTaxi()->GetId() == taxis[taxi_idx]->GetId())
		{
			taxis_queue.pop();
			break;
		}
		else
			temp.push_back(taxis_queue.top().GetTaxi());

		taxis_queue.pop();
	}

	for (unsigned int i = 0; i < temp.size(); i++)
		taxis_queue.push(temp[i]);

	//remove services of the taxi remove
	invoices.makeEmpty();
	vector<Service>  aux;
	for (unsigned int i = 0; i < customers.size(); i++)
	{
		Invoice temp(customers[i], 0);
		for (int j = 0; j < customers[i]->GetServicesSize(); j++)
		{
			if (!(customers[i]->GetServiceAtIdx(j).GetTaxi() == taxis[taxi_idx]))
				aux.push_back(customers[i]->GetServiceAtIdx(j));
			else
				num_of_services--;
		}
		customers[i]->SetServices(aux);
		aux.clear();
	}

	aux.clear();
	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		Invoice temp((*it), 0);
		for (int j = 0; j < (*it)->GetServicesSize(); j++)
		{
			if (!((*it)->GetServiceAtIdx(j).GetTaxi() == taxis[taxi_idx]))
				aux.push_back((*it)->GetServiceAtIdx(j));
			else
				num_of_services--;
		}
		(*it)->SetServices(aux);
		aux.clear();
	}

	unsigned int customers_size = customers.size();
	unsigned int services_size;
	//Sort all the services of each active customer and Add the respective invoices to the BST.
	for (unsigned int cust_idx = 0; cust_idx < customers_size; cust_idx++)
	{
		services_size = customers[cust_idx]->GetServicesSize();
		for (unsigned int serv_idx = 0; serv_idx < services_size; serv_idx++)
			AddInvoice(customers[cust_idx], serv_idx);
	}

	//Sort all the services of each inactive customer and Add the respective invoices to the BST.
	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		(*it)->SortServices();
		services_size = (*it)->GetServicesSize();
		for (unsigned int serv_idx = 0; serv_idx < services_size; serv_idx++)
			AddInvoice(*it, serv_idx);
	}

	delete taxis[taxi_idx];
	taxis.erase(taxis.begin() + taxi_idx);
	taxis_changed = true;
	num_of_drivers--;
	drivers_changed = true;
	services_changed = true;
	cout << endl << "O taxi foi removido com sucesso." << endl << endl;
}

//-----------------------------------Class Driver-------------------------------------------
void EmpresaDeTaxis::AddDriver()
{
	bool taxi_available = false;
	unsigned int taxis_size = taxis.size();
	vector<unsigned int> available_taxis_idx;
	ClearScreen();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		if (taxis[i]->GetDriver().GetName().empty())
		{
			available_taxis_idx.push_back(i);
			taxi_available = true;
		}
	}
	if (taxi_available == false)
	{
		cout << "Nao existe qualquer taxi disponivel para adicionar um condutor.\nUtilize a funcao do menu que permite adicionar taxis. " << endl;
		return;
	}

	cout << "Os seguintes Taxis estao disponiveis: " << endl << endl;
	cout << setw(4) << "Id" << setw(19) << "Id Condutor" << setw(15) << "Km" << setw(25) << "Numero de Lugares" << setw(25) << "Matricula" << setw(24) << "Data de Registo" << endl;
	unsigned int available_taxis_size = available_taxis_idx.size();
	for (unsigned int i = 0; i < available_taxis_size; i++)
		cout << *taxis[available_taxis_idx[i]] << endl;
	cout << endl << endl;

	cout << "Introduza o id do taxi ao qual pretende adicionar o condutor: ";
	string error_msg = "Ocorreu um erro ao ler o id do taxi que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int taxi_id = ReadUnsignedInt(error_msg);
	int taxi_idx;
	taxi_idx = SearchForTaxiId(taxi_id);
	while (find(available_taxis_idx.begin(), available_taxis_idx.end(), taxi_idx) == available_taxis_idx.end())
	{
		cout << "O Id introduzido nao pertence a nenhum taxi valido. Por favor, tente novamente, introduzindo um id valido: ";
		taxi_id = ReadUnsignedInt(error_msg);
		taxi_idx = SearchForTaxiId(taxi_id);
	}

	cout << "Introduza o nome do condutor que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler o nome do condutor que introduziu. Por favor, tente novamente, introduzindo um nome valido: ";
	string name = ReadString(error_msg);

	cout << "Introduza a morada do condutor que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler a morada de condutor que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string adress = ReadString(error_msg);

	cout << "Introduza o NIF do condutor que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler o NIF do cliente que introduziu. Por favor, tente novamente, introduzindo um NIF valido: ";
	unsigned int nif = ReadUnsignedInt(error_msg);
	while (true)
	{
		if (SearchForDriverNIF(nif) != -1)
			cout << "O NIF introduzido ja esta associada a outro condutor. Por favor, tente novamente, introduzindo um NIF valido: ";
		else if (IsNifValid(nif) == false)
			cout << "O NIF introduzido e invalido. Verifique a validade do mesmo: ";
		else
			break;

		nif = ReadUnsignedInt(error_msg);
	}

	cout << "Introduza o numero da carta de conducao do condutor que pretende adicionar: ";
	error_msg = "Ocorreu um erro ao ler o numero da carta de conducao que introduziu. Por favor, tente novamente, introduzindo um numero da carta de conducao valido: ";
	unsigned int driver_license = ReadUnsignedInt(error_msg);
	while (true)
	{
		if (SearchForDriverLicense(driver_license) != -1)
			cout << "O numero da carta de conducao introduzido ja esta associada a outro condutor. Por favor, tente novamente, introduzindo um numero de carta de conducao valido: ";
		else
			if (to_string(driver_license).length() != 9)
				cout << "O numero da carta de conducao deve conter 9 algarismos. Por favor, tente novamente, introduzindo um numero de carta de conducao valido: ";
			else
				break;

		driver_license = ReadUnsignedInt(error_msg);
	}

	Driver new_driver(name, adress, nif, driver_license);
	taxis[taxi_idx]->SetDriver(new_driver);

	//New taxi is available to do services, so we add it to the priority queue taxis_queue
	taxis_queue.push(taxis[taxi_idx]);

	num_of_drivers++;
	drivers_changed = true;

	cout << endl << "O condutor foi adicionado com sucesso." << endl << endl;

}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ChangeDriverAdressById()
{
	cout << "Introduza o id do condutor que pretende alterar: ";
	unsigned int taxi_idx = ReadDriverId();//it reads a driver id but returns an index for a taxi, because a driver must have a taxi 
	ChangeDriverAdress(taxi_idx);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ChangeDriverAdressByName()
{
	cout << "Introduza o nome do condutor que pretende alterar: ";
	vector<unsigned int> drivers_indexes;
	ReadDriverName(drivers_indexes);

	if (drivers_indexes.size() > 1)
	{
		unsigned int drivers_indexes_size = drivers_indexes.size();
		for (int i = 0; i <= drivers_indexes_size; i++)
		{
			cout << *(taxis[i]) << endl;
		}

		ChangeDriverAdressById();
	}

	ChangeDriverAdress(drivers_indexes[0]);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ChangeDriverAdress(unsigned int taxi_idx)
{
	cout << "Introduza a nova morada do condutor que pretende alterar: ";
	string error_msg = "Ocorreu um erro ao ler a morada de condutor que introduziu. Por favor, tente novamente, introduzindo uma morada valida: ";
	string new_adress = ReadString(error_msg);

	Driver driver = taxis[taxi_idx]->GetDriver();
	driver.SetAdress(new_adress);
	taxis[taxi_idx]->SetDriver(driver);

	drivers_changed = true;

	cout << "A morada do condutor foi alterada com sucesso" << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::RemoveDriverById()
{
	cout << "Introduza o id do condutor que pretende alterar: ";
	unsigned int taxi_idx = ReadDriverId();//it reads a driver name but returns an index for a taxi, because a driver must have a taxi 
	EraseDriver(taxi_idx);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::RemoveDriverByName()
{
	cout << "Introduza o nome do condutor que pretende alterar: ";
	vector<unsigned int> drivers_indexes;
	ReadDriverName(drivers_indexes);

	if (drivers_indexes.size() > 1)
	{
		unsigned int drivers_indexes_size = drivers_indexes.size();
		for (int i = 0; i <= drivers_indexes_size; i++)
		{
			cout << *(taxis[i]) << endl;
		}

		ChangeDriverAdressById();
	}
	else
		EraseDriver(drivers_indexes[0]);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::EraseDriver(unsigned int taxi_idx)
{
	Driver driver;
	taxis[taxi_idx]->SetDriver(driver);
	num_of_drivers--;
	drivers_changed = true;
	cout << "O condutor foi removido com sucesso" << endl;
}

//---------------------------------------Display Functions---------------------------------------
void EmpresaDeTaxis::DisplayAllCustomers() const
{
	unsigned int customers_size = customers.size();
	if (customers_size == 1 && inactive_customers.empty())
	{
		cout << "Nao existem clientes na empresa. Utilize a opcao do menu para adicionar clientes." << endl;
		return;
	}

	if (customers_size != 1)
	{
		cout << "Active Customers:" << endl << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl << endl;
		for (unsigned int i = 1; i < customers_size; i++)
			cout << *customers[i] << endl << endl;
	}


	if (!inactive_customers.empty())
	{
		vector<Customer*> inactive_custs_sorted;
		inactive_custs_sorted.insert(inactive_custs_sorted.end(), inactive_customers.begin(), inactive_customers.end());
		sort(inactive_custs_sorted.begin(), inactive_custs_sorted.end(), CompareCustomersNames);

		cout << "Inactive Customers:" << endl << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl << endl;
		unsigned int inactive_custs_vec_size = inactive_custs_sorted.size();
		for (unsigned int i = 0; i < inactive_custs_vec_size; i++)
			cout << *inactive_custs_sorted[i] << endl << endl;
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayAllCustomersSortedByRegistDate() const
{
	DisplayAllCustomersInSpecificOrder(CompareCustomersRegistDates);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayAllCustomersSortedByPoints() const
{
	DisplayAllCustomersInSpecificOrder(CompareCustomersPoints);
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayBottomCustomersSortedByUnpaidAmount() const
{
	unsigned int num_of_bottom_custs = 10;
	vector<Customer*> customers_sorted = customers;
	customers_sorted.erase(customers_sorted.begin());  //erase the unregistered customer because it is not intended to be shown
	unsigned int customers_size = customers.size();
	if (customers_size == 1 && inactive_customers.empty())
	{
		cout << "Nao existem clientes na empresa. Utilize a opcao do menu para adicionar clientes." << endl;
		return;
	}
	customers_sorted.insert(customers_sorted.end(), inactive_customers.begin(), inactive_customers.end());
	sort(customers_sorted.begin(), customers_sorted.end(), CompareCustomersUnPaidAmounts);

	unsigned int customers_sorted_size = customers_sorted.size();
	if (num_of_bottom_custs > customers_sorted.size())
		num_of_bottom_custs = customers_sorted.size();
	unsigned int last_vec_idx = customers_sorted_size - num_of_bottom_custs;

	unsigned int count = 0;
	for (int i = customers_sorted_size - 1; i >= last_vec_idx; i--)
	{
		if (customers_sorted[i]->GetUnPaidAmount() == 0)
		{
			num_of_bottom_custs = count;
			break;
		}
		count++;
	}

	if (num_of_bottom_custs == 0)
	{
		cout << "Todos os clientes tem as despesas saldadas." << endl;
		return;
	}

	last_vec_idx = customers_sorted_size - num_of_bottom_custs;
	cout << "Estes sao os " << num_of_bottom_custs << " clientes mais devedores da empresa: " << endl << endl;
	cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl << endl;
	for (int i = customers_sorted_size - 1; i >= last_vec_idx; i--)
		cout << *customers_sorted[i] << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayCustomerById() const
{
	unsigned int customers_size = customers.size();
	if (customers_size == 1)
	{
		cout << "Nao existem clientes na empresa. Utilize a opcao do menu para adicionar clientes." << endl;
		return;
	}

	cout << "Introduza o id do cliente a mostrar: ";
	unsigned int idx;
	CustomerHash::iterator it;
	ReadCustomerId(idx, it);
	Customer *cust;
	Date windows_date;
	CustomerDiscount discount;
	unsigned int current_month;
	if (idx != -1)
	{
		cust = customers[idx];
		cust->UpdateDiscount();
		cust->GetCustomerDiscount(discount);
		GetDateFromWindows(windows_date);
		current_month = windows_date.GetMonth();
	}
	else
		cust = *it;
	ClearScreen();
	cout << "Id: " << cust->GetId() << endl;
	cout << "Nome: " << cust->GetName() << endl;
	cout << "Morada: " << cust->GetAdress() << endl;
	cout << "NIF: " << cust->GetNif() << endl;
	cout << "Data de Registo: " << cust->GetRegistDate() << endl;
	cout << "Pontos: " << cust->GetPoints() << endl;
	cout << "Despesa nao saldada: " << fixed << setprecision(2) << cust->GetUnPaidAmount() << endl;

	cout << "Ativo: ";
	if (idx != -1)
		cout << "Sim" << endl;
	else
		cout << "Nao" << endl;

	if (idx == -1) //if the customer is inactive, it means he has no discounts
		return;

	if (IsParticularCustomer(customers[idx]))
	{
		if (ParticularCustomer::IsMinPaidDiscount())
		{
			cout << "Voucher: ";
			if (discount.GetVoucher() == 0)
				cout << "Nao";
			else
			{
				cout << "Sim, no valor de " << discount.GetVoucher() << " euros, ";
				if (current_month == discount.GetFreeTripValidMonth())
					cout << "no mes atual";
				else
					cout << "no mes seguinte";
			}
			cout << endl;
			cout << "Montante pago no mes atual: " << fixed << setprecision(2) << discount.GetAmountPaid() << endl;
		}

		if (ParticularCustomer::IsMinTripsDiscount())
		{
			cout << "Viagem gratuita: ";
			if (!discount.IsFreeTrip())
				cout << "Nao";
			else
			{
				cout << "Sim, ";
				if (current_month == discount.GetFreeTripValidMonth())
					cout << "no mes atual";
				else
					cout << "no mes seguinte";
			}
			cout << endl;
			cout << "Numero de viagens no mes atual: " << discount.GetNumTrips() << endl;
		}
	}
	else
	{
		if (BusinessCustomer::IsMinPaidDiscount())
		{
			cout << "Voucher: ";
			if (discount.GetVoucher() == 0)
				cout << "Nao";
			else
			{
				cout << "Sim, no valor de " << discount.GetVoucher() << " euros, ";
				if (current_month == discount.GetFreeTripValidMonth())
					cout << "no mes atual";
				else
					cout << "no mes seguinte";
			}
			cout << endl;
			cout << "Montante pago no mes atual: " << fixed << setprecision(2) << discount.GetAmountPaid() << endl;
		}

		if (BusinessCustomer::IsMinTripsDiscount())
		{
			cout << "Viagem gratuita: ";
			if (!discount.IsFreeTrip())
				cout << "Nao";
			else
			{
				cout << "Sim, ";
				if (current_month == discount.GetFreeTripValidMonth())
					cout << "no mes atual";
				else
					cout << "no mes seguinte";
			}
			cout << endl;
			cout << "Numero de viagens no mes atual: " << discount.GetNumTrips() << endl;
		}
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayCustomerByName() const
{
	unsigned int customers_size = customers.size();
	if (customers_size == 1)
	{
		cout << "Nao existem clientes na empresa. Utilize a opcao do menu para adicionar clientes." << endl;
		return;
	}

	cout << "Introduza o nome do(s) cliente(s) que pretende mostrar: ";
	unsigned int lower_idx = 0, upper_idx = 0;
	vector<CustomerHash::iterator> cust_its;
	ReadCustomerName(lower_idx, upper_idx, cust_its);

	ClearScreen();

	if (customers_size > 1)
	{
		cout << "Active Customers: " << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl << endl;
	}
	for (unsigned int i = lower_idx; i <= upper_idx; i++)
		cout << *customers[i] << endl << endl;

	unsigned int cust_its_size = cust_its.size();
	if (cust_its_size > 1)
	{
		cout << "Inactive Customers: " << endl;
		cout << setw(4) << "Id" << setw(18) << "Nome" << setw(18) << "Morada" << setw(16) << "NIF" << setw(18) << "Data de Registo" << setw(12) << "Pontos" << setw(19) << "Montante a Pagar" << endl << endl;
	}
	for (unsigned int i = 0; i < cust_its_size; i++)
		cout << *(*cust_its[i]) << endl << endl;

	cout << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayAllServices() const
{
	if (num_of_services == 0)
	{
		cout << "Nao existem servicos feitos pela empresa para mostrar. Pode adicionar servicos usando a opcao do menu." << endl;
		return;
	}

	cout << setw(12) << "Id Servico" << setw(12) << "Id Taxi" << setw(14) << "Distancia" << setw(12) << "Duracao" << setw(16) << "Data Inicio" << setw(21) << "Montante a Pagar" << setw(18) << "Servico Pago" << endl << endl;
	BSTItrIn<Invoice> invoices_it(invoices);
	unsigned int service_idx;
	Service curr_service;
	while (!invoices_it.isAtEnd())
	{
		service_idx = invoices_it.retrieve().GetServiceIdx();
		curr_service = invoices_it.retrieve().GetCustomer()->GetServiceAtIdx(service_idx);
		cout << curr_service << endl << endl;

		invoices_it.advance();
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayServiceById() const
{
	if (num_of_services == 0)
	{
		cout << "Nao existem servicos feitos pela empresa para mostrar. Pode adicionar servicos usando a opcao do menu." << endl;
		return;
	}

	unsigned int services_size;
	vector<Service> services;
	int customer_idx = 0;
	unsigned int service_idx = 0;
	CustomerHash::iterator cust_it;
	cout << "Introduza o id do(s) servico(s) que pretende mostrar: ";
	ReadServiceId(customer_idx, cust_it, service_idx);
	ClearScreen();
	const Service *service;
	Customer *customer;
	if (customer_idx != -1)
	{
		customer = customers[customer_idx];
		service = &customers[customer_idx]->GetServiceAtIdx(service_idx);
	}
	else
	{
		customer = (*cust_it);
		service = &(*cust_it)->GetServiceAtIdx(service_idx);
	}
	cout << "Id Servico: " << service->GetId() << endl;
	cout << "Id Taxi: " << service->GetTaxi()->GetId() << endl;
	cout << "Id Cliente: " << customer->GetId() << endl;
	cout << "Origem: " << service->GetStart() << endl;
	cout << "Destino: " << service->GetFinish() << endl;
	cout << "Distancia durante o dia: " << service->GetDayDistance() << endl;
	cout << "Distancia durante a noite: " << service->GetNightDistance() << endl;
	cout << "Distancia total: " << service->GetDistance() << endl;
	cout << "Duracao: " << service->GetDuration() << endl;
	cout << "Tempo de inicio: " << service->GetDate() << endl;
	cout << "Tempo de fim: " << service->GetFinalDate() << endl;
	cout << "Preco antes do desconto: " << service->GetPrePrice() << endl;
	cout << "Preco final: " << service->GetFinalPrice() << endl;
	cout << "Servico pago: ";
	if (service->IsPaid())
		cout << "Sim" << endl;
	else
		cout << "Nao" << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayServicesByName() const
{
	if (num_of_services == 0)
	{
		cout << "Nao existem servicos feitos pela empresa para mostrar. Pode adicionar servicos usando a opcao do menu." << endl;
		return;
	}

	unsigned int customer_size = customers.size();
	unsigned int services_size;
	unsigned lower_idx = 0, upper_idx = 0;
	vector<CustomerHash::iterator> cust_its;
	vector<Service> services;
	cout << "Introduza o nome do(s) cliente(s), cujo(s) servico(s) pretende mostrar: ";
	ReadCustomerName(lower_idx, upper_idx, cust_its);
	ClearScreen();
	cout << setw(12) << "Id Servico" << setw(12) << "Id Taxi" << setw(14) << "Distancia" << setw(12) << "Duracao" << setw(16) << "Data Inicio" << setw(21) << "Montante a Pagar" << setw(18) << "Servico Pago" << endl << endl;

	string name;
	if (lower_idx == -1)
		name = (*(cust_its[0]))->GetName();
	else
		name = customers[lower_idx]->GetName();

	BSTItrIn<Invoice> invoices_it(invoices);
	unsigned int service_idx;
	Service curr_service;
	while (!invoices_it.isAtEnd())
	{
		if (invoices_it.retrieve().GetCustomer()->GetName() == name)
		{
			service_idx = invoices_it.retrieve().GetServiceIdx();
			curr_service = invoices_it.retrieve().GetCustomer()->GetServiceAtIdx(service_idx);
			cout << curr_service << endl << endl;
		}
		invoices_it.advance();
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayServicesByDate() const
{
	if (num_of_services == 0)
	{
		cout << "Nao existem servicos feitos pela empresa para mostrar. Pode adicionar servicos usando a opcao do menu." << endl;
		return;
	}

	Date date;
	vector<Service> services;
	cout << "Introduza a data do(s) servico(s) predende mostrar: ";
	ReadDate(date);
	SearchForServiceDate(date, services);
	unsigned int services_size = services.size();
	ClearScreen();
	if (services_size == 0)
		cout << "Nao foram encontrados servicos realizados na data introduzida." << endl << endl;
	else
	{
		cout << setw(12) << "Id Servico" << setw(12) << "Id Taxi" << setw(14) << "Distancia" << setw(12) << "Duracao" << setw(16) << "Data Inicio" << setw(21) << "Montante a Pagar" << setw(18) << "Servico Pago" << endl << endl;
		for (unsigned int i = 0; i < services_size; i++)
			cout << services[i] << endl;
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayServicesBetweenDates() const
{
	if (num_of_services == 0)
	{
		cout << "Nao existem servicos feitos pela empresa para mostrar. Pode adicionar servicos usando a opcao do menu." << endl;
		return;
	}

	Date date1, date2;
	vector<Service> services;
	cout << "Introduza a primeira data: ";
	ReadDate(date1);
	cout << endl << "Introduza a segunda data: ";
	ReadDate(date2);
	SearchForServicesBetweenDates(date1, date2, services);
	ClearScreen();
	unsigned int services_size = services.size();
	if (services_size == 0)
		cout << "Nao foram encontrados servicos entre as datas introduzidas." << endl << endl;
	else
		cout << setw(12) << "Id Servico" << setw(12) << "Id Taxi" << setw(14) << "Distancia" << setw(12) << "Duracao" << setw(16) << "Data Inicio" << setw(21) << "Montante a Pagar" << setw(18) << "Servico Pago" << endl << endl;
	for (unsigned int i = 0; i < services_size; i++)
	{
		cout << services[i] << endl;
	}

}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayAllTaxis() const
{
	unsigned int taxis_size = taxis.size();
	if (taxis_size == 0)
	{
		cout << "Nao existem taxis na empresa. Utilize a opcao do menu para adicionar taxis." << endl;
		return;
	}

	cout << setw(4) << "Id" << setw(19) << "Id Condutor" << setw(15) << "Km" << setw(25) << "Numero de Lugares" << setw(25) << "Matricula" << setw(24) << "Data de Registo" << endl << endl;
	for (unsigned int i = 0; i < taxis_size; i++)
		cout << *taxis[i] << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayTaxiById() const
{
	if (taxis.size() == 0)
	{
		cout << "Nao existem taxis na empresa. Utilize a opcao do menu para adicionar taxis." << endl;
		return;
	}

	cout << "Introduza o id do taxi a mostrar: ";
	unsigned int pos = ReadTaxiId();
	ClearScreen();
	cout << setw(4) << "Id" << setw(19) << "Id Condutor" << setw(15) << "Km" << setw(25) << "Numero de Lugares" << setw(25) << "Matricula" << setw(24) << "Data de Registo" << endl << endl;
	cout << *taxis[pos] << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayTaxiByLicensePlate() const
{
	if (taxis.size() == 0)
	{
		cout << "Nao existem taxis na empresa. Utilize a opcao do menu para adicionar taxis." << endl;
		return;
	}
	cout << "Introduza a matricula do taxi a mostrar (na forma xx-xx-xx mm/aaaa): ";
	LicensePlate plate;
	unsigned int pos = ReadTaxiLicensePlate(plate);
	ClearScreen();
	cout << setw(4) << "Id" << setw(19) << "Id Condutor" << setw(15) << "Km" << setw(25) << "Numero de Lugares" << setw(25) << "Matricula" << setw(24) << "Data de Registo" << endl << endl;
	cout << *taxis[pos] << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayAllDrivers() const
{
	if (num_of_drivers == 0)
	{
		cout << "Nao existem condutores na empresa para mostrar. Pode adicionar clientes usando a opcao do menu." << endl;
		return;
	}

	unsigned int taxis_size = taxis.size();
	cout << setw(4) << "Id" << setw(18) << "Nome Condutor" << setw(37) << "Morada" << setw(16) << "NIF" << setw(20) << "Data de Registo" << setw(24) << "Carta de Conducao" << endl << endl;
	for (unsigned int i = 0; i < taxis_size; i++)
		if (!taxis[i]->GetDriver().GetName().empty())
			cout << taxis[i]->GetDriver() << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayDriverById() const
{
	if (num_of_drivers == 0)
	{
		cout << "Nao existem condutores na empresa para mostrar. Pode adicionar clientes usando a opcao do menu." << endl;
		return;
	}

	cout << "Introduza o id do condutor a mostrar:";
	unsigned int pos = ReadDriverId();
	ClearScreen();
	cout << setw(4) << "Id" << setw(18) << "Nome Condutor" << setw(37) << "Morada" << setw(16) << "NIF" << setw(20) << "Data de Registo" << setw(24) << "Carta de Conducao" << endl << endl;
	cout << taxis[pos]->GetDriver() << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::DisplayDriverByName() const
{
	if (num_of_drivers == 0)
	{
		cout << "Nao existem condutores na empresa para mostrar. Pode adicionar clientes usando a opcao do menu." << endl;
		return;
	}

	cout << "Introduza o nome do(s) condutor(es) a mostrar: ";
	vector<unsigned int> drivers_with_name;
	ReadDriverName(drivers_with_name);
	unsigned int drivers_with_name_size = drivers_with_name.size();
	Driver driver;
	ClearScreen();
	cout << setw(4) << "Id" << setw(18) << "Nome Condutor" << setw(37) << "Morada" << setw(16) << "NIF" << setw(20) << "Data de Registo" << setw(24) << "Carta de Conducao" << endl << endl;
	for (unsigned int i = 0; i < drivers_with_name_size; i++)
	{
		driver = taxis[i]->GetDriver();
		cout << driver;
	}

	cout << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::UpdateAllCustsState()
{
	time_t curr_system_time = time(NULL);
	if (curr_system_time == -1)
		throw ErrorGettingLocalTime();
	time_t last_trip_time;
	time_t inactive_time;
	time_t min_time_to_inactive;
	for (unsigned int i = 1; i < customers.size(); i++)
	{
		last_trip_time = customers[i]->GetLastTripTime();
		inactive_time = curr_system_time - last_trip_time;
		if (IsParticularCustomer(customers[i]))
			min_time_to_inactive = ParticularCustomer::GetMinTimeToInactive();
		else
			min_time_to_inactive = BusinessCustomer::GetMinTimeToInactive();

		if (inactive_time >= min_time_to_inactive && last_trip_time != 0)
		{
			MoveCustomerToHash(i);
			i--;
		}
	}

	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		last_trip_time = (*it)->GetLastTripTime();
		inactive_time = curr_system_time - last_trip_time;
		if (IsParticularCustomer(*it))
			min_time_to_inactive = ParticularCustomer::GetMinTimeToInactive();
		else
			min_time_to_inactive = BusinessCustomer::GetMinTimeToInactive();

		if (inactive_time < min_time_to_inactive)
		{
			MoveCustomerToVector(*it);
			it = inactive_customers.begin();
		}
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::MoveCustomerToHash(unsigned int cust_idx)
{
	inactive_customers.insert(customers[cust_idx]);
	customers.erase(customers.begin() + cust_idx);
}
//------------------------------------------------------------------------------
unsigned int EmpresaDeTaxis::MoveCustomerToVector(Customer *customer)
{
	vector<Customer*>::iterator it = lower_bound(customers.begin(), customers.end(), customer);
	it = customers.insert(it, customer);
	inactive_customers.erase(customer);
	unsigned int idx = it - customers.begin();
	return idx;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::AddCustomerToHash(Customer *customer)
{
	inactive_customers.insert(customer);
}
//------------------------------------------------------------------------------
//Updates all customers' discounts based on the current month. If the discount is out of date, invalidate it, by resetting it to zero
void EmpresaDeTaxis::UpdateAllCustsDiscounts()
{
	unsigned int customers_size = customers.size();
	for (unsigned int i = 1; i < customers_size; i++)
		customers[i]->UpdateDiscount();
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ResetAllCustsDiscounts()
{
	unsigned int customers_size = customers.size();
	for (unsigned int i = 1; i < customers_size; i++)
		customers[i]->ResetDisabledDiscounts();
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ToggleCustPMinPaidDiscount()
{
	if (ParticularCustomer::IsMinPaidDiscount())
	{
		ParticularCustomer::SetMinPaidDiscount(false);
		ResetAllCustsDiscounts();
		cout << "Desativou com sucesso os descontos para cliente particulares para minimos de totais pagos." << endl;
	}
	else
	{
		ParticularCustomer::SetMinPaidDiscount(true);
		cout << "Ativou com sucesso os descontos para clientes particulares por minimos de totais pagos.\nO minimo de total pago necessario para obtencao de voucher, sera o definido atualmente: " << ParticularCustomer::GetMinPaidForDiscount() << ".\Se pretender altera-lo, utilize a opcao do menu anterior" << endl;
	}

	customers_p_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ToggleCustPMinTripsDiscount()
{
	if (ParticularCustomer::IsMinTripsDiscount())
	{
		ParticularCustomer::SetMinTripsDiscount(false);
		ResetAllCustsDiscounts();
		cout << "Desativou com sucesso os descontos para cliente particulares para minimos de viagens realizadas." << endl;
	}
	else
	{
		ParticularCustomer::SetMinTripsDiscount(true);
		cout << "Ativou com sucesso os descontos para clientes particulares por minimos de viagens realizadas.\nO minimo de viagens realizadas necessario para obtencao de uma viagem gratuita, sera o definido atualmente: " << ParticularCustomer::GetMinTripsForDiscount() << ".\Se pretender altera-lo, utilize a opcao do menu anterior" << endl;
	}

	customers_p_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ToggleCustBMinPaidDiscount()
{
	if (BusinessCustomer::IsMinPaidDiscount())
	{
		BusinessCustomer::SetMinPaidDiscount(false);
		ResetAllCustsDiscounts();
		cout << "Desativou com sucesso os descontos para cliente empresariais para minimos de totais pagos." << endl;
	}
	else
	{
		BusinessCustomer::SetMinPaidDiscount(true);
		cout << "Ativou com sucesso os descontos para clientes empresariais por minimos de totais pagos.\nO minimo de total pago necessario para obtencao de voucher, sera o definido atualmente: " << BusinessCustomer::GetMinPaidForDiscount() << ".\Se pretender altera-lo, utilize a opcao do menu anterior" << endl;
	}

	customers_b_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ToggleCustBMinTripsDiscount()
{
	if (BusinessCustomer::IsMinTripsDiscount())
	{
		BusinessCustomer::SetMinTripsDiscount(false);
		ResetAllCustsDiscounts();
		cout << "Desativou com sucesso os descontos para cliente empresariais para minimos de viagens realizadas." << endl;
	}
	else
	{
		BusinessCustomer::SetMinTripsDiscount(true);
		cout << "Ativou com sucesso os descontos para clientes empresariais por minimos de viagens realizadas.\nO minimo de viagens realizadas necessario para obtencao de uma viagem gratuita, sera o definido atualmente: " << BusinessCustomer::GetMinTripsForDiscount() << ".\Se pretender altera-lo, utilize a opcao do menu anterior" << endl;
	}

	customers_b_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustPMinPaidForDiscount()
{
	cout << "Introduza o valor minimo de totais pagos para obter um voucher de 5 euros, para clientes particulares: ";
	string error_msg = "Ocorreu um erro ao ler o valor de minimos pagos que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	unsigned int min_paid = ReadUnsignedInt(error_msg);
	ParticularCustomer::SetMinPaidForDiscount(min_paid);
	customers_p_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustPMinTripsForDiscount()
{
	cout << "Introduza o numero minimo de viagens realizadas para obter uma viagem gratuita, para clientes particulares: ";
	string error_msg = "Ocorreu um erro ao ler o numero de viagens realizadas que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	unsigned int min_trips = ReadUnsignedInt(error_msg);
	ParticularCustomer::SetMinTripsForDiscount(min_trips);
	customers_p_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustPMinTimeToInactive()
{
	cout << "Introduza o minimo de tempo desde a ultima viagem para o cliente particular ficar inativo (em dias): ";
	string error_msg = "Ocorreu um erro ao ler o numero minimo de tempo que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	time_t min_days_to_inactive = ReadUnsignedInt(error_msg);
	time_t min_seconds_to_inactive = min_days_to_inactive * 60 * 60 * 24;
	ParticularCustomer::SetMinTimeToInactive(min_seconds_to_inactive);
	customers_p_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustBMinPaidForDiscount()
{
	cout << "Introduza o valor minimo de totais pagos para obter um voucher de 5 euros, para clientes empresariais: ";
	string error_msg = "Ocorreu um erro ao ler o valor de minimos pagos que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	unsigned int min_paid = ReadUnsignedInt(error_msg);
	BusinessCustomer::SetMinPaidForDiscount(min_paid);
	customers_b_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustBMinTripsForDiscount()
{
	cout << "Introduza o numero minimo de viagens realizadas para obter  uma viagem gratuita, para clientes empresariais: ";
	string error_msg = "Ocorreu um erro ao ler o numero de viagens realizadas que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	unsigned int min_trips = ReadUnsignedInt(error_msg);
	BusinessCustomer::SetMinTripsForDiscount(min_trips);
	customers_b_changed = true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SetCustBMinTimeToInactive()
{
	cout << "Introduza o minimo de tempo desde a ultima viagem para o cliente empresarial ficar inativo (em dias): ";
	string error_msg = "Ocorreu um erro ao ler o numero minimo de tempo que introduziu. Por favor, tente novamente, introduzindo um valor valido: ";
	time_t min_days_to_inactive = ReadUnsignedInt(error_msg);
	time_t min_seconds_to_inactive = min_days_to_inactive * 60 * 60 * 24;
	BusinessCustomer::SetMinTimeToInactive(min_seconds_to_inactive);
	customers_b_changed = true;
}


//---------------------------------------Read User Input Functions---------------------------------------
//Reads a Customer id (unsigned int) and returns it; does not return while the user doesn't introduce an id that exists in the vector of customers
void EmpresaDeTaxis::ReadCustomerId(unsigned int &idx, CustomerHash::iterator &it) const
{
	string error_msg = "Ocorreu um erro ao ler o id de cliente que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int id = ReadUnsignedInt(error_msg);
	while (!SearchForCustId(id, (int&)idx, it) || idx == 0)
	{
		cout << endl << endl << "O id do cliente introduzido nao foi encontrado na lista de clientes. Por favor, tente novamente, introduzindo um id valido: ";
		id = ReadUnsignedInt(error_msg);
	}
}
//------------------------------------------------------------------------------
//Reads a Customer name (string) and returns it; does not return while the user doesn't introduce a name that exists in the map of customer names
void EmpresaDeTaxis::ReadCustomerName(unsigned int &lower_idx, unsigned int &upper_idx, vector<CustomerHash::iterator> &cust_its) const
{
	string error_msg = "Ocorreu um erro ao ler o nome de cliente que introduziu. Por favor, tente novamente, introduzindo um nome valido: ";
	string name = ReadString(error_msg);

	//does not return while the user does not introduce a name that is not in the vector of customers
	while (name.empty() || !SearchForCustName(name, (int&)lower_idx, (int&)upper_idx, cust_its))
	{
		cout << endl << endl << "O nome do cliente introduzido nao foi encontrado na lista de clientes. Por favor, tente novamente, introduzindo um nome valido: ";
		name = ReadString(error_msg);
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::ReadServiceId(int &customer_idx, CustomerHash::iterator &it, unsigned int &service_idx) const
{
	string error_msg = "Ocorreu um erro ao ler o id do servico que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int id = ReadUnsignedInt(error_msg);
	while (!SearchForServiceId(id, customer_idx, it, service_idx))
	{
		cout << endl << endl << "O id do servico introduzido nao foi encontrado na lista de servicos. Por favor, tente novamente, introduzindo um id valido: ";
		id = ReadUnsignedInt(error_msg);
	}
}
//------------------------------------------------------------------------------
BSTItrIn<Invoice> EmpresaDeTaxis::ReadInvoiceId() const
{
	string error_msg = "Ocorreu um erro ao ler o id da fatura que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int id = ReadUnsignedInt(error_msg);
	BSTItrIn<Invoice> iterator_to_invoice(invoices);
	while ((iterator_to_invoice = SearchForInvoiceId(id)).isAtEnd())
	{
		cout << endl << endl << "O id da fatura introduzido nao foi encontrado na lista de faturas. Por favor, tente novamente, introduzindo um id valido: ";
		id = ReadUnsignedInt(error_msg);
	}

	return iterator_to_invoice;
}
//------------------------------------------------------------------------------
unsigned int EmpresaDeTaxis::ReadTaxiId() const
{
	string error_msg = "Ocorreu um erro ao ler o id do taxi que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int id = ReadUnsignedInt(error_msg);
	int pos;
	while ((pos = SearchForTaxiId(id)) == -1)
	{
		cout << endl << endl << "O id do taxi introduzido nao foi encontrado na lista de taxis. Por favor, tente novamente, introduzindo um id valido: ";
		id = ReadUnsignedInt(error_msg);
	}

	return pos;
}
//------------------------------------------------------------------------------
//Reads a value of type LicensePlate from user
//Does not return anything while the user does not introduce the intended input
unsigned int EmpresaDeTaxis::ReadTaxiLicensePlate(LicensePlate &plate) const
{
	ReadLicensePlate(plate);
	int idx;
	while ((idx = SearchForTaxiLicensePlate(plate)) == -1)
	{
		cout << endl << endl << "A matricula do introduzida nao corresponde a nenhum taxi da empresa. Por favor, tente novamente, introduzindo uma matricula valida: ";
		ReadLicensePlate(plate);
	}
	return idx;
}
//------------------------------------------------------------------------------
//Reads a driver id but returns an index for a taxi, because a driver must have a taxi
unsigned int EmpresaDeTaxis::ReadDriverId() const
{
	string error_msg = "Ocorreu um erro ao ler o id do condutor que introduziu. Por favor, tente novamente, introduzindo um id valido: ";
	unsigned int id = ReadUnsignedInt(error_msg);
	int pos;
	while ((pos = SearchForDriverId(id)) == -1)
	{
		cout << endl << endl << "O id do condutor introduzido nao foi encontrado na lista de taxis. Por favor, tente novamente, introduzindo um id valido: ";
		id = ReadUnsignedInt(error_msg);
	}

	return pos;
}
//------------------------------------------------------------------------------
//Reads a driver name and returns a vector of indexes of taxis (because a driver must have a taxi)
void EmpresaDeTaxis::ReadDriverName(vector<unsigned int> &drivers_indexes) const
{
	string error_msg = "Ocorreu um erro ao ler o nome do condutor que introduziu. Por favor, tente novamente, introduzindo um nome valido: ";
	string name = ReadString(error_msg);
	SearchForDriverName(drivers_indexes, name);
	while (drivers_indexes.empty())
	{
		cout << endl << endl << "O nome do condutor introduzido nao foi encontrado na lista de taxis. Por favor, tente novamente, introduzindo um id valido: ";
		name = ReadString(error_msg);
		SearchForDriverName(drivers_indexes, name);
	}
}



//---------------------------------------Search for Information in the Company Functions---------------------------------------
bool EmpresaDeTaxis::SearchForCustId(unsigned int id, int &idx, CustomerHash::iterator &it) const
{
	idx = SearchForActiveCustId(id);

	if (idx != -1)
		return true;
	else
		it = SearchForInactiveCustId(id);

	if (it != inactive_customers.end())
		return true;
	else
		return false;

}
//------------------------------------------------------------------------------
//Searches for an id of a customer
//If the id is found, returns the index of the customer in the vector customers, if it's not found, returns -1
int EmpresaDeTaxis::SearchForActiveCustId(unsigned int id) const
{
	//This declaration is to make the for loop more efficient, so that it doesn't need to be calculating the size of the vector in each cycle
	unsigned int customers_size = customers.size();
	for (int i = 0; i < customers_size; i++)
		if (customers[i]->GetId() == id)
			return i;
	return -1;
}
//------------------------------------------------------------------------------
CustomerHash::iterator EmpresaDeTaxis::SearchForInactiveCustId(unsigned int id) const
{
	ParticularCustomer customer(id);
	return inactive_customers.find(&customer);
}
//------------------------------------------------------------------------------
bool EmpresaDeTaxis::SearchForCustName(string name, int &lower_idx, int &upper_idx, vector<CustomerHash::iterator> &cust_its) const
{
	bool find = false;
	if (SearchForActiveCustName(name, lower_idx, upper_idx))
		find = true;
	if (SearchForInactiveCustName(name, cust_its))
		find = true;

	return find;
}
//------------------------------------------------------------------------------
//Searches for a name of a customer
//If the name is found, returns the boundaries (lower and upper indexes) of the customers that have that name in the vector customers, if it's not found, returns -1
bool EmpresaDeTaxis::SearchForActiveCustName(string name, int &lower_idx, int &upper_idx) const
{
	lower_idx = -1;
	upper_idx = -1;
	vector<Customer *>::const_iterator it;
	ParticularCustomer aux_cust(name);
	it = lower_bound(customers.begin(), customers.end(), &aux_cust, CompareCustomersNames);
	if (it == customers.end())
		return false;
	else if ((*it)->GetName() != name)
		return false;
	else
	{
		unsigned int customers_size = customers.size();
		lower_idx = it - customers.begin();
		for (unsigned int i = lower_idx + 1; i < customers_size; i++)
			if (customers[i]->GetName() != name)
			{
				upper_idx = i - 1;
				break;
			}
	}

	return true;
}
//------------------------------------------------------------------------------
bool EmpresaDeTaxis::SearchForInactiveCustName(string name, vector<CustomerHash::iterator> &cust_its) const
{
	cust_its.clear();
	bool find = false;
	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		if ((*it)->GetName() == name)
		{
			find = true;
			cust_its.push_back(it);
		}
	}

	return find;
}
bool EmpresaDeTaxis::SearchForCustNIF(unsigned int nif, int &idx, CustomerHash::iterator &it) const
{
	bool find = false;
	if (SearchForActiveCustNIF(nif, idx))
		find = true;

	//if the custome with the nif specified as parameter was not found in the vector, searches in the hash table
	if (SearchForInactiveCustNIF(nif, it))
		find = true;

	return find;
}
//------------------------------------------------------------------------------
//Searches for a nif of a customer
//If the nif is found, returns the index of the customer in the vector customers, if it's not found, returns -1
bool EmpresaDeTaxis::SearchForActiveCustNIF(unsigned int nif, int &idx) const
{
	//This declaration is to make the for loop more efficient, so that it doesn't need to be calculating the size of the vector in each cycle
	unsigned int customers_size = customers.size();
	for (int i = 0; i < customers_size; i++)
		if (customers[i]->GetNif() == nif)
			return true;

	return false;
}
bool EmpresaDeTaxis::SearchForInactiveCustNIF(unsigned int nif, CustomerHash::iterator &it) const
{
	for (it = inactive_customers.begin(); it != inactive_customers.end(); it++)
		if ((*it)->GetNif() == nif)
			return true;

	return false;
}
//------------------------------------------------------------------------------
//Searches for an id of a service
//If the id is found, returns 0 and the index of the customer who has the service and the index of the service in the vector taxis, if it's not found, returns -1
bool EmpresaDeTaxis::SearchForServiceId(unsigned int service_id, int &customer_idx, CustomerHash::iterator &it, unsigned int &service_idx) const
{
	vector<Service> curr_services;
	unsigned int services_size;
	unsigned int customers_size = customers.size();
	//Search in the vector of active customers
	for (unsigned int curr_cust_idx = 0; curr_cust_idx < customers_size; curr_cust_idx++)
	{
		customers[curr_cust_idx]->GetServices(curr_services);
		services_size = curr_services.size();
		for (unsigned int curr_serv_idx = 0; curr_serv_idx < services_size; curr_serv_idx++)
		{
			if (curr_services[curr_serv_idx].GetId() == service_id)
			{
				customer_idx = curr_cust_idx;
				service_idx = curr_serv_idx;
				return true;
			}
		}
	}

	//If not found in the vector of active customers, set customer_idx to -1 (to flag that it was not found there) and search in the hash table of inactive customers
	customer_idx = -1;
	for (CustomerHash::iterator curr_cust_it = inactive_customers.begin(); curr_cust_it != inactive_customers.end(); curr_cust_it++)
	{
		(*curr_cust_it)->GetServices(curr_services);
		services_size = curr_services.size();
		for (unsigned int curr_serv_idx = 0; curr_serv_idx < services_size; curr_serv_idx++)
		{
			if (curr_services[curr_serv_idx].GetId() == service_id)
			{
				it = curr_cust_it;
				service_idx = curr_serv_idx;
				return true;
			}
		}
	}

	//If not found in any of the data structures of customers, return false
	it = inactive_customers.end();
	return false;
}
//------------------------------------------------------------------------------
bool EmpresaDeTaxis::SearchForServiceDate(const Date &date, vector<Service> &desired_services) const
{
	Date service_date;

	vector<Service>::const_iterator lower_it, curr_it;

	Service aux_serv(date);
	vector<Service> curr_services;
	unsigned int services_size;

	//Search in the vector of active customers
	unsigned int customers_size = customers.size();
	for (unsigned int i = 0; i < customers_size; i++)
	{
		customers[i]->GetServices(curr_services);
		lower_it = lower_bound(curr_services.begin(), curr_services.end(), aux_serv);
		if (lower_it == curr_services.end())
			continue;
		else
			if (lower_it->GetDate() != date)
				continue;
			else
			{
				services_size = curr_services.size();
				for (curr_it = lower_it; curr_it < curr_services.end(); curr_it++)
					if (curr_it->GetDate() != date)
						break;
				desired_services.insert(desired_services.end(), lower_it, curr_it);
			}
	}


	//If not found in the vector of active customers, search in the hash table of inactive customers
	for (CustomerHash::iterator curr_cust_it = inactive_customers.begin(); curr_cust_it != inactive_customers.end(); curr_cust_it++)
	{
		(*curr_cust_it)->GetServices(curr_services);
		services_size = curr_services.size();
		for (unsigned int curr_serv_idx = 0; curr_serv_idx < services_size; curr_serv_idx++)
		{
			(*curr_cust_it)->GetServices(curr_services);
			lower_it = lower_bound(curr_services.begin(), curr_services.end(), aux_serv);
			if (lower_it == curr_services.end())
				continue;
			else
				if (lower_it->GetDate() != date)
					continue;
				else
				{
					services_size = curr_services.size();
					for (curr_it = lower_it; curr_it < curr_services.end(); curr_it++)
						if (curr_it->GetDate() != date)
							break;
					desired_services.insert(desired_services.end(), lower_it, curr_it);
				}
		}
	}
	if (desired_services.empty())
		return false;

	sort(desired_services.begin(), desired_services.end());
	return true;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SearchForServicesBetweenDates(const Date &date1, const Date &date2, vector<Service> &desired_services) const
{
	vector<Service>::const_iterator lower_it, curr_it;

	Service aux_serv(date1);
	vector<Service> services;
	unsigned int services_size;

	unsigned int customers_size = customers.size();
	for (unsigned int i = 0; i < customers_size; i++)
	{
		customers[i]->GetServices(services);
		lower_it = lower_bound(services.begin(), services.end(), aux_serv);
		if (lower_it == services.end())
			continue;
		else
		{
			services_size = services.size();
			for (curr_it = lower_it; curr_it < services.end(); curr_it++)
				if (curr_it->GetDate() > date2)
					break;
			desired_services.insert(desired_services.end(), lower_it, curr_it);
		}
	}

	sort(desired_services.begin(), desired_services.end());
}
BSTItrIn<Invoice> EmpresaDeTaxis::SearchForInvoiceId(unsigned int id) const
{
	BSTItrIn<Invoice> iterator(invoices);
	unsigned int service_idx;
	while (!iterator.isAtEnd())
	{
		service_idx = iterator.retrieve().GetServiceIdx();

		if (iterator.retrieve().GetCustomer()->GetServiceAtIdx(service_idx).GetId() == id)
			return iterator;
		iterator.advance();
	}

	return iterator;
}
//------------------------------------------------------------------------------
//Searches for an id of a taxi
//If the id is found, returns the index of the taxi in the vector taxis, if it's not found, returns -1
int EmpresaDeTaxis::SearchForTaxiId(unsigned int id) const
{
	Taxi aux_taxi(id);
	auto it = lower_bound(taxis.begin(), taxis.end(), &aux_taxi, CompareTaxisIds);
	if (it == taxis.end())
		return -1;
	else if ((*it)->GetId() != id)
		return -1;
	else
		return (it - taxis.begin());
}
//------------------------------------------------------------------------------
//Searches for a LicensePlate of a taxi
//If the licenseplate is found, returns the index of the taxi in the vector taxis, if it's not found, returns -1
int EmpresaDeTaxis::SearchForTaxiLicensePlate(const LicensePlate &plate) const
{
	unsigned int taxis_size = taxis.size();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		if (taxis[i]->GetLicensePlate() == plate)
			return i;
	}

	return -1;
}
//------------------------------------------------------------------------------
//Searches for a Driver Id of a taxi
//If the Driver Id is found, returns the index of the taxi in the vector taxis, if it's not found, returns -1
int EmpresaDeTaxis::SearchForDriverId(unsigned int driver_id) const
{
	unsigned int taxis_size = taxis.size();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		if (taxis[i]->GetDriver().GetId() == driver_id)
			if (!(taxis[i]->GetDriver().GetName().empty()))
				return i;
	}

	return -1;
}
//------------------------------------------------------------------------------
//Searches for a Driver name of a taxi
//If the Driver name is found, returns the index of the taxi in the vector taxis, if it's not found, returns -1
void EmpresaDeTaxis::SearchForDriverName(vector<unsigned int> &drivers_indexes, string driver_name) const
{
	drivers_indexes.clear();
	string curr_name;
	unsigned int taxis_size = taxis.size();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		curr_name = taxis[i]->GetDriver().GetName();
		if (curr_name == driver_name)
			if (!(curr_name.empty()))
				drivers_indexes.push_back(i);
	}
}
//------------------------------------------------------------------------------
int EmpresaDeTaxis::SearchForDriverNIF(unsigned int nif) const
{
	unsigned int taxis_size = taxis.size();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		if (taxis[i]->GetDriver().GetNif() == nif)
			if (!(taxis[i]->GetDriver().GetName().empty()))
				return i;
	}
	return -1;
}
//------------------------------------------------------------------------------
int EmpresaDeTaxis::SearchForDriverLicense(unsigned int driver_license) const
{
	unsigned int taxis_size = taxis.size();
	for (unsigned int i = 0; i < taxis_size; i++)
	{
		if (taxis[i]->GetDriver().GetDriversLicense() == driver_license)
			if (!(taxis[i]->GetDriver().GetName().empty()))
				return i;
	}

	return -1;
}


//------------------------------------------------------------------------------
void EmpresaDeTaxis::CallConstFunction(void(EmpresaDeTaxis::*Function)())
{
	(this->*Function)();
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SaveChanges() const
{
	if (customers_p_changed || customers_b_changed)
		SaveCustomers();

	if (services_changed)
		SaveServices();

	if (taxis_changed)
		SaveTaxis();

	if (drivers_changed)
		SaveDrivers();

	if (customers_p_changed || customers_b_changed || services_changed || taxis_changed || drivers_changed)
		cout << endl << "As suas alteracoes foram gravadas com sucesso.";
	else
		cout << endl << "Como a informacao nao foi alterada durante a execucao do programa, nao foi gravada qualquer alteracao aos ficheiros.";
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SaveCustomers() const
{
	ofstream customers_p_fs;
	ofstream customers_b_fs;
	unsigned int customers_size = customers.size();
	if (customers_p_changed)
	{
		customers_p_fs.open(customers_p_tmp_fn);
		customers_p_fs << "" << num_of_p_customers << " ; " << ParticularCustomer::IsMinTripsDiscount() << " is min trips discount active" << " ; " << ParticularCustomer::IsMinPaidDiscount() << " is min paid discount active" << " ; " << ParticularCustomer::GetMinTripsForDiscount() << " min trips for discount" << " ; " << ParticularCustomer::GetMinPaidForDiscount() << " min paid for discount" << " ; " << ParticularCustomer::GetMinTimeToInactive() << " min time to inactive (in seconds)" << endl;
	}
	if (customers_b_changed)
	{
		customers_b_fs.open(customers_b_tmp_fn);
		customers_b_fs << "" << num_of_b_customers << " ; " << BusinessCustomer::IsMinTripsDiscount() << " is min trips discount active" << " ; " << BusinessCustomer::IsMinPaidDiscount() << " is min paid discount active" << " ; " << BusinessCustomer::GetMinTripsForDiscount() << " min trips for discount" << " ; " << BusinessCustomer::GetMinPaidForDiscount() << " min paid for discount" << " ; " << BusinessCustomer::GetMinTimeToInactive() << " min time to inactive (in seconds)" << endl;
	}

	//the construction of decisions inside the loop ensures the dynamic cast attempt is performed only once, thus taking less time in runtime
	for (unsigned int i = 1; i < customers_size; i++)
	{
		if (IsParticularCustomer(customers[i]))
		{
			if (customers_p_changed)
				customers_p_fs << *customers[i] << endl;
		}
		else
		{
			if (customers_b_changed)
				customers_b_fs << *customers[i] << endl;
		}
	}

	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		if (IsParticularCustomer(*it))
		{
			if (customers_p_changed)
				customers_p_fs << *(*it) << endl;
		}
		else
		{
			if (customers_b_changed)
				customers_b_fs << *(*it) << endl;
		}
	}

	if (customers_p_changed)
		customers_p_fs.close();

	if (customers_b_changed)
		customers_b_fs.close();

	//If no error saving to the temp file, create the final file
	if (customers_p_changed)
	{
		if (remove(customers_p_fn.c_str()) != 0)
		{
			cerr << "Ocorreu um erro ao gravar para o ficheiro " << customers_p_fn << endl << endl;
			return;
		}
		if (rename(customers_p_tmp_fn.c_str(), customers_p_fn.c_str()) != 0)
		{
			cerr << "Ocorreu um erro ao gravar para o ficheiro " << customers_p_fn << endl << endl;
			return;
		}
		cout << "Ficheiro " << customers_p_fn << " guardado com sucesso!" << endl << endl;
	}
	if (customers_b_changed)
	{
		if (remove(customers_b_fn.c_str()) != 0)
		{
			cerr << "Ocorreu um erro ao gravar para o ficheiro " << customers_b_fn << endl << endl;
			return;
		}
		if (rename(customers_b_tmp_fn.c_str(), customers_b_fn.c_str()) != 0)
		{
			cerr << "Ocorreu um erro ao gravar para o ficheiro " << customers_b_fn << endl << endl;
			return;
		}
		cout << "Ficheiro " << customers_b_fn << " guardado com sucesso!" << endl << endl;
	}
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SaveServices() const
{
	ofstream services_fs(services_tmp_fn);
	unsigned int customers_size = customers.size();
	unsigned int services_size;
	unsigned int curr_cust_id;
	vector<Service> curr_services;

	services_fs << "" << num_of_services << " ; " << Service::GetBasePriceDay() << " base daytime price" << " ; " << Service::GetBasePriceNight() << " base nightime price" << " ; " << Service::GetAverageSpeedCity() << " average speed inside city" << " ; " << Service::GetAverageSpeedOffCity() << " average speed outside city" << " ; " << Service::GetPricePerMinute() << " price per minute" << " ; " << Service::GetPricePerKmDay() << " price per km day" << " ; " << Service::GetPricePerKmNight() << " price per km night" << endl;
	for (unsigned int curr_cust_idx = 0; curr_cust_idx < customers_size; curr_cust_idx++)
	{
		curr_cust_id = customers[curr_cust_idx]->GetId();
		customers[curr_cust_idx]->GetServices(curr_services);
		services_size = curr_services.size();
		for (unsigned int curr_serv_idx = 0; curr_serv_idx < services_size; curr_serv_idx++)
		{
			services_fs << "" << curr_services[curr_serv_idx].GetId() << " service id ; " << curr_cust_id << " customer id ; ";
			services_fs << curr_services[curr_serv_idx] << endl;
		}
	}

	for (CustomerHash::iterator it = inactive_customers.begin(); it != inactive_customers.end(); it++)
	{
		curr_cust_id = (*it)->GetId();
		(*it)->GetServices(curr_services);
		services_size = curr_services.size();
		for (unsigned int curr_serv_idx = 0; curr_serv_idx < services_size; curr_serv_idx++)
		{
			services_fs << "" << curr_services[curr_serv_idx].GetId() << " service id ; " << curr_cust_id << " customer id ; ";
			services_fs << curr_services[curr_serv_idx] << endl;
		}
	}
	services_fs.close();

	//If no error saving to the temp file, create the final file
	if (remove(services_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << services_fn << endl << endl;
		return;
	}
	if (rename(services_tmp_fn.c_str(), services_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << services_fn << endl << endl;
		return;
	}

	cout << "Ficheiro " << services_fn << " guardado com sucesso!" << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SaveTaxis() const
{
	ofstream taxis_fs(taxis_tmp_fn);

	unsigned int taxis_size = taxis.size();
	taxis_fs << "" << taxis_size << endl;
	for (unsigned int i = 0; i < taxis_size; i++)
		taxis_fs << *taxis[i] << endl;
	taxis_fs.close();

	//If no error saving to the temp file, create the final file
	if (remove(taxis_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << taxis_fn << endl << endl;
		return;
	}
	if (rename(taxis_tmp_fn.c_str(), taxis_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << taxis_fn << endl << endl;
		return;
	}

	cout << "Ficheiro " << taxis_fn << " guardado com sucesso!" << endl << endl;
}
//------------------------------------------------------------------------------
void EmpresaDeTaxis::SaveDrivers() const
{
	ofstream drivers_fs(drivers_tmp_fn);

	unsigned int taxis_size = taxis.size();
	drivers_fs << "" << num_of_drivers << endl;
	for (unsigned int i = 0; i < taxis_size; i++)
		if (!taxis[i]->GetDriver().GetName().empty())
		{
			drivers_fs << "" << taxis[i]->GetDriver().GetId() << " driver id" << " ; " << taxis[i]->GetId() << " taxi id" << " ; ";
			drivers_fs << taxis[i]->GetDriver() << endl;
		}
	drivers_fs.close();

	//If no error saving to the temp file, create the final file
	if (remove(drivers_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << drivers_fn << endl << endl;
		return;
	}
	if (rename(drivers_tmp_fn.c_str(), drivers_fn.c_str()) != 0)
	{
		cerr << "Ocorreu um erro ao gravar para o ficheiro " << drivers_fn << endl << endl;
		return;
	}

	cout << "Ficheiro " << drivers_fn << " guardado com sucesso!" << endl << endl;
}
//------------------------------------------------------------------------------
//---------------------------------------Operator Overloads---------------------------------------
ostream &operator<<(ostream &os, const EmpresaDeTaxis &company)
{
	os << "Estatisticas da " << company.company_name << ": " << endl << endl;
	os << setw(35) << "Numero de clientes particulares: " << setw(5) << company.num_of_p_customers << endl << endl;
	os << setw(35) << "Numero de clientes empresariais: " << setw(5) << company.num_of_b_customers << endl << endl;
	os << setw(35) << "Numero de servicos: " << setw(5) << company.num_of_services << endl << endl;
	os << setw(35) << "Numero de taxis: " << setw(5) << company.taxis.size() << endl << endl;
	os << setw(35) << "Numero de condutores: " << setw(5) << company.num_of_drivers << endl << endl;
	return os;
}
//------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const EmpresaDeTaxis::ErrorParsingFile &error)
{
	os << "Ocorreu um erro ao ler do ficheiro " << error.file_name << ":" << endl << error.error_msg;
	return os;
}