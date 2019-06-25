#include <iostream>
#include <iomanip>
#include <fstream>

#include "Customer.h"
#include "Menus.h"
#include "TimeStamp.h"
#include "Date.h"
#include "Service.h"
#include "utils.h"

#include "EmpresaDeTaxis.h"


using namespace std;


//---------------------------------------Reading From Files Functions---------------------------------------
//------------------------------------------------------------------------------
//Recieves a file stream that was not openned yet and reads the file name from user
//Returns the file name that it read from the user
//Does not return anything while it is not able to successfully read the file name introduced
//If it can read the filename but can't open it, exits with an error message
string ReadFile(ifstream &f_stream)
{
	string f_name;
	string error_msg = "Ocorreu um erro ao ler o nome de ficheiro que introduziu. Por favor, tente novamente, introduzindo um nome de ficheiro valido: ";
	f_name = ReadString(error_msg);
	f_stream.open(f_name);
	if (!(f_stream.is_open())) //Check if the file was openned successfully
	{
		cerr << endl << "Ocorreu um erro ao tentar abrir o ficheiro. O programa ira terminar." << endl;
		exit(1);
	}
	return f_name;
}
//------------------------------------------------------------------------------
//Reads all the filenames from user and opens the file streams (checking if the files exist)
void ReadFiles(ifstream &customers_p_fs, ifstream &customers_b_fs, ifstream &services_fs, ifstream &taxis_fs, ifstream &drivers_fs, string &company_name, string &customers_p_fn, string &customers_b_fn, string &services_fn, string &taxis_fn, string &drivers_fn)
{
	cout << "Introduza o nome da empresa: ";
	string error_msg = "Ocorreu um erro ao ler o nome da empresa que introduziu. Por favor, tente novamente, introduzindo um nome de empresa valido: ";
	company_name = ReadString(error_msg);
	cout << endl << "Introduza o nome do ficheiro que contem as informacoes dos clientes particulares: ";
	customers_p_fn = ReadFile(customers_p_fs);
	cout << endl << "Introduza o nome do ficheiro que contem as informacoes dos clientes empresariais: ";
	customers_b_fn = ReadFile(customers_b_fs);
	cout << endl << "Introduza o nome do ficheiro que contem os servicos realizados pela empresa: ";
	services_fn = ReadFile(services_fs);
	cout << endl << "Introduza o nome do ficheiro que contem as informacoes dos taxis da empresa: ";
	taxis_fn = ReadFile(taxis_fs);
	cout << endl << "Introduza o nome do ficheiro que contem as informacoes dos condutores da empresa: ";
	drivers_fn = ReadFile(drivers_fs);

	cout << endl;
}
//------------------------------------------------------------------------------
//Parses the contents of all the files to the vectors in the class VendeMaisMais
void ParseFileContents(EmpresaDeTaxis &Company, ifstream &customers_p_fs, ifstream &customers_b_fs, ifstream &services_fs, ifstream &taxis_fs, ifstream &drivers_fs)
{
	try
	{
		Company.ParseParticularCustomers(customers_p_fs);
		customers_p_fs.close();
		Company.ParseBusinessCustomers(customers_b_fs);
		customers_b_fs.close();
		Company.ParseTaxis(taxis_fs);
		taxis_fs.close();
		Company.ParseServices(services_fs);
		services_fs.close();
		Company.ParseDrivers(drivers_fs);
		drivers_fs.close();
	}
	catch (EmpresaDeTaxis::ErrorParsingFile &error)
	{
		cout << error;
		exit(1);
	}

	cout << "A informacao contida em todos os ficheiros foi lida com sucesso" << endl << endl;
	system("pause");
}

//---------------------------------------Main Function---------------------------------------
int main()
{
	string company_name, customers_p_fn, customers_b_fn, services_fn, taxis_fn, drivers_fn;
	ifstream customers_p_fs, customers_b_fs, services_fs, taxis_fs, drivers_fs;

	cout << "Bem-vindo. Este programa permite-lhe efetuar a gestao da sua empresa de Taxis." << endl << endl;

	ReadFiles(customers_p_fs, customers_b_fs, services_fs, taxis_fs, drivers_fs, company_name, customers_p_fn, customers_b_fn, services_fn, taxis_fn, drivers_fn);

	EmpresaDeTaxis Company(company_name, customers_p_fn, customers_b_fn, services_fn, taxis_fn, drivers_fn);

	Company.ComputeTmpFileNames();

	ParseFileContents(Company, customers_p_fs, customers_b_fs, services_fs, taxis_fs, drivers_fs);

	Company.UpdateAllCustsDiscounts();

	//This infinite loop garantees a way of coming back to the main menu without another function having to call the main menu function again, avoiding leaving processes in suspension
	while (true)
	{
		try
		{
			ShowMainMenu(Company);
			SelectMainMenuOption(Company);
			cout << endl << endl;
		}
		catch (EmpresaDeTaxis::ErrorGettingLocalTime)
		{
			cout << "Ocorreu um erro ao obter a data do sistema. O programa irá terminar, guardando a informaçao da ultima sessao" << endl << endl;
			Company.SaveChanges();
			exit(1);
		}
		catch (...)
		{
			cout << "Ocorreu um erro desconhecido. O programa ira terminar, tentando guardar a informaçao da ultima sessao" << endl << endl;
			Company.SaveChanges();
			exit(1);
		}
	}

	return 0;
}