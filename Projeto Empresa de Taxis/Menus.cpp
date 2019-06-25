#include "Menus.h"


//-----------------------------------------Main Menu Functions------------------------------------------------
void ShowMainMenu(EmpresaDeTaxis &Company)
{
	ClearScreen();
	cout << Company.GetCompanyName() << endl << endl;
	cout << "1 - Gestao de informacao." << endl;
	cout << "2 - Adicionar pedido." << endl;
	cout << "3 - Processar pedidos em espera." << endl;
	cout << "4 - Liquidar despesas de um cliente." << endl;
	cout << "5 - Visualizacao de informacao." << endl;
	cout << "6 - Personalizacao." << endl;
	cout << "7 - Estatisticas da " << Company.GetCompanyName() << "." << endl;
	cout << "8 - Sair" << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectMainMenuOption(EmpresaDeTaxis &Company)
{
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
			ShowManageMenu();
			SelectManageMenuOption(Company);
			break;
		case 2:
			ClearScreen();
			ShowAddRequestMenu();
			SelectAddRequestMenuOption(Company);
			break;
		case 3:
			ClearScreen();
			Company.ProcessAllWaitingRequests();
			system("pause");
			break;
		case 4:
			ClearScreen();
			Company.LiquidateCustAmount();
			system("pause");
			break;
		case 5:
			ShowDisplayMenu();
			SelectDisplayMenuOption(Company);
			break;
		case 6:
			ShowCustomizeMenu();
			SelectCustomizeMenuOption(Company);
			break;
		case 7:
			ClearScreen();
			cout << Company;
			system("pause");
			break;
		case 8:
			ShowExitMenu();
			SelectExitMenuOption(Company);
			break;
		default:
			error = true;
			cout << endl << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//---------------------------------------Manage Menu Functions---------------------------------------
void ShowManageMenu()
{
	ClearScreen();
	cout << "1 - Gestao de clientes." << endl;
	cout << "2 - Gestao de Taxis." << endl;
	cout << "3 - Gestao de Condutores." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectManageMenuOption(EmpresaDeTaxis &Company)
{
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
			ShowManageCustomerMenu();
			SelectManageCustomerMenuOption(Company);
			break;
		case 2:
			ShowManageTaxisMenu();
			SelectManageTaxisMenuOption(Company);
			break;
		case 3:
			ShowManageDriversMenu();
			SelectManageDriversMenuOption(Company);
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowManageCustomerMenu()
{
	ClearScreen();
	cout << "1 - Adicionar um cliente." << endl;
	cout << "2 - Modificar morada de um cliente." << endl;
	cout << "3 - Remover um cliente." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectManageCustomerMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.AddCustomer();
			system("pause");
			break;
		case 2:
			ShowEditCustomerMenu();
			SelectEditCustomerMenuOption(Company);
			break;
		case 3:
			ShowRemoveCustomerMenu();
			SelectRemoveCustomerMenuOption(Company);
			break;		
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowEditCustomerMenu()
{
	ClearScreen();
	cout << "1 - Modificar por Id do cliente." << endl;
	cout << "2 - Modificar por nome do cliente." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectEditCustomerMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.ChangeCustomerAdressById();
			system("pause");
			break;
		case 2:
			Company.ChangeCustomerAdressByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowRemoveCustomerMenu()
{
	ClearScreen();
	cout << "1 - Remover por Id do cliente." << endl;
	cout << "2 - Remover por nome do cliente." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectRemoveCustomerMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.RemoveCustomerById();
			system("pause");
			break;
		case 2:
			Company.RemoveCustomerByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowManageTaxisMenu()
{
	ClearScreen();
	cout << "1 - Adicionar um taxi." << endl;
	cout << "2 - Remover um taxi." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectManageTaxisMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.AddTaxi();
			system("pause");
			break;
		case 2:
			ShowRemoveTaxiMenu();
			SelectRemoveTaxiOption(Company);
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowRemoveTaxiMenu()
{
	ClearScreen();
	cout << "1 - Remover por id do taxi." << endl;
	cout << "2 - Remover por matricula do taxi." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectRemoveTaxiOption(EmpresaDeTaxis &Company)
{
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
			Company.RemoveTaxiById();
			system("pause");
			break;
		case 2:
			Company.RemoveTaxiByLicensePlate();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowManageDriversMenu()
{
	ClearScreen();
	cout << "1 - Adicionar um condutor." << endl;
	cout << "2 - Modificar a morada de um condutor." << endl;
	cout << "3 - Remover um condutor." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectManageDriversMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.AddDriver();
			system("pause");
			break;
		case 2:
			ShowEditDriverMenu();
			SelectEditDriverMenuOption(Company);
			break;
		case 3:
			ShowRemoveDriverMenu();
			SelectRemoveDriverMenuOption(Company);
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowEditDriverMenu()
{
	ClearScreen();
	cout << "1 - Modificar por Id do condutor." << endl;
	cout << "2 - Modificar por nome do condutor." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectEditDriverMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.ChangeDriverAdressById();
			system("pause");
			break;
		case 2:
			Company.ChangeDriverAdressByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowRemoveDriverMenu()
{
	ClearScreen();
	cout << "1 - Remover por Id do condutor." << endl;
	cout << "2 - Remover por nome do condutor." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectRemoveDriverMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.RemoveDriverById();
			system("pause");
			break;
		case 2:
			Company.RemoveDriverByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowAddRequestMenu()
{
	ClearScreen();
	cout << "1 - Adicionar pedido para cliente registado." << endl;
	cout << "2 - Adicionar pedido para cliente nao registado." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectAddRequestMenuOption(EmpresaDeTaxis & Company)
{
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
			ClearScreen();
			Company.AddRequestToRegisteredCustomer();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.AddRequest(0); //Customer with id 0 is the customer used to regist the services done for non registered customers
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//---------------------------------------Display Menu Functions---------------------------------------
void ShowDisplayMenu()
{
	ClearScreen();
	cout << "1 - Visualizar clientes." << endl;
	cout << "2 - Visualizar servicos/faturas." << endl;
	cout << "3 - Visualizar taxis." << endl;
	cout << "4 - Visualizar condutores." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectDisplayMenuOption(EmpresaDeTaxis &Company)
{
	int option;
	bool error;
	do
	{
		error = false;
		string error_msg = "Ocorreu um erro ao ler a opcao que introduziu. Por favor, tente novamente, introduzindo uma opcao valida: ";
		option = ReadUnsignedInt(error_msg);
		Company.UpdateAllCustsState(); //To make sure that all cust are in the right state, i.e, active or unactive
		switch (option)
		{
		case 1:
			ShowDisplayCustomersMenu();
			SelectDisplayCustomersMenuOption(Company);
			break;
		case 2:
			ClearScreen();
			ShowDisplayServicesMenu();
			SelectDisplayServicesMenuOption(Company);
			break;
		case 3:
			ClearScreen();
			ShowDisplayTaxisMenu();
			SelectDisplayTaxisMenuOption(Company);
			break;
		case 4:
			ClearScreen();
			ShowDisplayDriversMenu();
			SelectDisplayDriversMenuOption(Company);
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowDisplayCustomersMenu()
{
	ClearScreen();
	cout << "1 - Visualizar todos os clientes por ordem alfabetica do seu nome." << endl;
	cout << "2 - Visualizar todos os clientes por ordem temporal da sua data de registo." << endl;
	cout << "3 - Visualizar todos os clientes por ordem numerica dos pontos que tem acumulados." << endl;
	cout << "4 - Visualizar os 10 clientes com maior valor de despesa por saldar." << endl;
	cout << "5 - Visualizar informacao para um cliente em especifico por Id." << endl;
	cout << "6 - Visualizar informacao para um cliente em especifico por nome." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectDisplayCustomersMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.DisplayAllCustomers();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.DisplayAllCustomersSortedByRegistDate();
			system("pause");
			break;
		case 3:
			ClearScreen();
			Company.DisplayAllCustomersSortedByPoints();
			system("pause");
			break;
		case 4:
			ClearScreen();
			Company.DisplayBottomCustomersSortedByUnpaidAmount();
			system("pause");
			break;
		case 5:
			ClearScreen();
			Company.DisplayCustomerById();
			system("pause");
			break;
		case 6:
			ClearScreen();
			Company.DisplayCustomerByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowDisplayServicesMenu()
{
	ClearScreen();
	cout << "1 - Visualizar todos os servicos/faturas." << endl;
	cout << "2 - Visualizar informacao para um servico/fatura em especifico por Id." << endl;
	cout << "3 - Visualizar informacao para um servicos/faturas em especifico por nome de cliente." << endl;
	cout << "4 - Visualizar informacao para um servicos/faturas em especifico por data." << endl;
	cout << "5 - Visualizar informacao para um servicos/faturas em especifico entre datas." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectDisplayServicesMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.DisplayAllServices();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.DisplayServiceById();
			system("pause");
			break;
		case 3:
			ClearScreen();
			Company.DisplayServicesByName();
			system("pause");
			break;
		case 4:
			ClearScreen();
			Company.DisplayServicesByDate();
			system("pause");
			break;
		case 5:
			ClearScreen();
			Company.DisplayServicesBetweenDates();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowDisplayTaxisMenu()
{
	ClearScreen();
	cout << "1 - Visualizar todos os taxis." << endl;
	cout << "2 - Visualizar informacao para um taxi em especifico por Id." << endl;
	cout << "3 - Visualiar informacao para um taxi em especifico por matricula." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectDisplayTaxisMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.DisplayAllTaxis();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.DisplayTaxiById();
			system("pause");
			break;
		case 3:
			ClearScreen();
			Company.DisplayTaxiByLicensePlate();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowDisplayDriversMenu()
{
	ClearScreen();
	cout << "1 - Visualizar todos os condutores." << endl;
	cout << "2 - Visualizar informacao para um condutor em especifico por Id." << endl;
	cout << "3 - Visualiar informacao para um condutor em especifico por nome." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectDisplayDriversMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.DisplayAllDrivers();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.DisplayDriverById();
			system("pause");
			break;
		case 3:
			ClearScreen();
			Company.DisplayDriverByName();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//----------------------------------------Costumizing Discount Menu Functions--------------------------------------
void ShowCustomizeMenu()
{
	ClearScreen();
	cout << "1 - Ativar ou desativar sistema de descontos." << endl;
	cout << "2 - Editar condicoes de desconto." << endl;
	cout << "3 - Editar tempo minimo para inativacao de um cliente." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectCustomizeMenuOption(EmpresaDeTaxis &Company)
{
	vector<void(EmpresaDeTaxis::*)()> option_number_function;
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
			ClearScreen();
			ShowToggleDiscountsMenu();
			SelectToggleDiscountsMenuOption(Company);
			break;
		case 2:
			ClearScreen();
			ShowEditDiscountsConditionsMenu(option_number_function);
			SelectEditDiscountsConditionsMenuOption(Company, option_number_function);
			break;
		case 3:
			ClearScreen();
			ShowEditInactivationConditionsMenu();
			SelectEditInactivationConditionsMenuOption(Company);
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowToggleDiscountsMenu()
{
	ClearScreen();
	if (ParticularCustomer::IsMinPaidDiscount())
		cout << "1 - Desativar sistema de descontos para minimos de totais pagos para os clientes particulares." << endl;
	else
		cout << "1 - Ativar sistema de descontos para minimos de totais pagos para os clientes particulares." << endl;
	
	if (ParticularCustomer::IsMinTripsDiscount())
		cout << "2 - Desativar sistema de descontos para minimos de viagens realizadas para clientes empresariais." << endl;
	else
		cout << "2 - Ativar sistema de descontos para minimos de viagens realizadas para clientes particulares." << endl;
	
	if (BusinessCustomer::IsMinPaidDiscount())
		cout << "3 - Desativar sistema de descontos para minimos de totais pagos para os clientes empresariais." << endl;
	else
		cout << "3 - Ativar sistema de descontos para minimos de totais pagos para os clientes empresariais." << endl;
	
	if (BusinessCustomer::IsMinTripsDiscount())
		cout << "4 - Desativar sistema de descontos para minimos de viagens realizadas para clientes empresariais." << endl;
	else
		cout << "4 - Ativar sistema de descontos para minimos de viagens realizadas para clientes empresariais." << endl;

	cout << "0 - Cancelar e voltar ao Menu Principal." << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectToggleDiscountsMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.ToggleCustPMinPaidDiscount();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.ToggleCustPMinTripsDiscount();
			system("pause");
			break;
		case 3:
			ClearScreen();
			Company.ToggleCustBMinPaidDiscount();
			system("pause");
			break;
		case 4:
			ClearScreen();
			Company.ToggleCustBMinTripsDiscount();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}
//------------------------------------------------------------------------------
void ShowEditDiscountsConditionsMenu(vector<void(EmpresaDeTaxis::*)()> &option_number_function)
{
	ClearScreen();
	unsigned int curr_opt = 1;
	if (ParticularCustomer::IsMinPaidDiscount())
	{
		cout << curr_opt << " - Definir o minimo de total pago para que os clientes particulares possam obter um voucher e definir o voucher." << endl;
		option_number_function.push_back(&EmpresaDeTaxis::SetCustPMinPaidForDiscount);
		curr_opt++;
	}
	if (ParticularCustomer::IsMinTripsDiscount())
	{
		cout << curr_opt << " - Definir o minimo de viagens realizadas para que clientes particulares possam obter uma viagem gratuita no mes seguinte." << endl;
		option_number_function.push_back(&EmpresaDeTaxis::SetCustPMinTripsForDiscount);
		curr_opt++;
	}
	if (BusinessCustomer::IsMinPaidDiscount())
	{
		cout << curr_opt << " - Definir o minimo de total pago para que os clientes empresariais possam obter um voucher e definir o voucher." << endl;
		option_number_function.push_back(&EmpresaDeTaxis::SetCustBMinPaidForDiscount);
		curr_opt++;
	}
	if (BusinessCustomer::IsMinTripsDiscount())
	{
		cout << curr_opt << " - Definir o minimo de viagens realizadas para que clientes empresariais possam obter uma viagem gratuita no mes seguinte." << endl;
		option_number_function.push_back(&EmpresaDeTaxis::SetCustBMinTripsForDiscount);
		curr_opt++;
	}

	if (curr_opt == 1)
	{
		cout << "Atualmente, nenhum dos dois sistemas de descontos suportados se encontra ativo para qualquer um dos dois tipos de clientes.\nNao e possivel editar condicoes de desconto de momento.\nPor favor ative pelo menos um dos sistemas para pelo menos um tipo de cliente e tente novamente." << endl << endl;
		return;
	}
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectEditDiscountsConditionsMenuOption(EmpresaDeTaxis &Company, vector<void(EmpresaDeTaxis::*)()> &option_number_function)
{
	if (option_number_function.empty())
		return;
	int option;
	bool error;
	string error_msg = "Ocorreu um erro ao ler a opcao que introduziu. Por favor, tente novamente, introduzindo uma opcao valida: ";
	do
	{
		error = false;
		option = ReadUnsignedInt(error_msg);
		if (option > option_number_function.size())
		{
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
		else if (option == 0)
			return;
	} while (error);

	option--; //adjust user notation to vector notation
	ClearScreen();
	Company.CallConstFunction(option_number_function[option]);
	system("pause");
}
//------------------------------------------------------------------------------
void ShowEditInactivationConditionsMenu()
{
	ClearScreen();
	cout << "1 - Editar tempo para inativacao para clientes particulares." << endl;
	cout << "2 - Editar tempo para inativacao para clientes empresariais." << endl;
	cout << "0 - Cancelar e voltar ao Menu Principal." << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectEditInactivationConditionsMenuOption(EmpresaDeTaxis &Company)
{
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
			ClearScreen();
			Company.SetCustPMinTimeToInactive();
			system("pause");
			break;
		case 2:
			ClearScreen();
			Company.SetCustBMinTimeToInactive();
			system("pause");
			break;
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}

//----------------------------------------Exit Menu Functions--------------------------------------
void ShowExitMenu()
{
	ClearScreen();
	cout << "1 - Sair e Guardar." << endl;
	cout << "2 - Sair sem Guardar." << endl;
	cout << "0 - Voltar ao Menu Principal." << endl;
	cout << "Escreva o numero da opcao pretendida: ";
}
//------------------------------------------------------------------------------
void SelectExitMenuOption(EmpresaDeTaxis &Company)
{
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
			Company.UpdateAllCustsState(); //To make sure that all cust are in the right state, i.e, active or unactive
			Company.UpdateAllCustsDiscounts();
			Company.SaveChanges();
			cout << endl << "Obrigado por utilizar o programa. Volte sempre e boa sorte com o seu grande negocio de Taxis." << endl;
			exit(0);
		case 2:
			cout << endl << "Obrigado por utilizar o programa. Volte sempre e boa sorte com o seu grande negocio de Taxis." << endl;
			exit(0);
		case 0:
			return;
		default:
			error = true;
			cout << "O numero que introduziu nao corresponde a nenhuma opcao. Por favor, tente novamente, introduzindo um numero valido: ";
		}
	} while (error);
}