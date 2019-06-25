/**
*
* @file
* @brief Contains all functions declarations necessary to display the menus and read submenu selection from user
*
*/


#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "EmpresaDeTaxis.h"

using namespace std;

/**
*
* @brief Displays the Main Menu: clears the screen and couts the options available for the user to introduce to perform an action.
* @param Company The system class (the class that contains all the information of the company).
*
*/
void ShowMainMenu(EmpresaDeTaxis &Company);
/**
*
* @brief Reads the Main Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectMainMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Manage Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to manage customers, taxis and drivers.
*
*/
void ShowManageMenu();
/**
*
* @brief Reads the Manage Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectManageMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Manage Customers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to manage customers.
*
*/
void ShowManageCustomerMenu();
/**
*
* @brief Reads the Manage Customers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectManageCustomerMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Edit Customers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to edit customers.
*
*/
void ShowEditCustomerMenu();
/**
*
* @brief Reads the Edit Customers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectEditCustomerMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Remove Customers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to remove customers.
*
*/
void ShowRemoveCustomerMenu();
/**
*
* @brief Reads the Remove Customers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectRemoveCustomerMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Manage Taxis Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to manage taxis.
*
*/
void ShowManageTaxisMenu();
/**
*
* @brief Reads the Manage Taxis Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectManageTaxisMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Remove Taxis Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to remove taxis.
*
*/
void ShowRemoveTaxiMenu();
/**
*
* @brief Reads the Remove Taxis Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectRemoveTaxiOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Manage Drivers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to manage drivers.
*
*/
void ShowManageDriversMenu();
/**
*
* @brief Reads the Manage Drivers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectManageDriversMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Edit Drivers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to edit drivers.
*
*/
void ShowEditDriverMenu();
/**
*
* @brief Reads the Edit Drivers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectEditDriverMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Remove Drivers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to remove drivers.
*
*/
void ShowRemoveDriverMenu();
/**
*
* @brief Reads the Remove Drivers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectRemoveDriverMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Add request Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to make a request for services.
*
*/
void ShowAddRequestMenu();
/**
*
* @brief Reads the request Services Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectAddRequestMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all the information related to customers, taxis, drivers and services.
*
*/
void ShowDisplayMenu();
/**
*
* @brief Reads the Display Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Customers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all the information related to customers.
*
*/
void ShowDisplayCustomersMenu();
/**
*
* @brief Reads the Display Customers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayCustomersMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Services Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all the information related to services.
*
*/
void ShowDisplayServicesMenu();
/**
*
* @brief Reads the Display Services Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayServicesMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Invoices Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all invoices.
*
*/
void ShowDisplayInvoicesMenu();
/**
*
* @brief Reads the Display Service Invoices Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayInvoicesMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Taxis Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all the information related to taxis.
*
*/
void ShowDisplayTaxisMenu();
/**
*
* @brief Reads the Display Taxis Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayTaxisMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Display Drivers Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to display all the information related to drivers.
*
*/
void ShowDisplayDriversMenu();
/**
*
* @brief Reads the Display Drivers Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectDisplayDriversMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Customize Discount Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to customize the discount system.
*
*/
void ShowCustomizeMenu();
/**
*
* @brief Reads the Customize Discount Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectCustomizeMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Toggle Discount Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to enable or disable the discount system.
*
*/
void ShowToggleDiscountsMenu();
/**
*
* @brief Reads the Toggle Discount Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectToggleDiscountsMenuOption(EmpresaDeTaxis &Company);
/**
*
* @brief Displays the Edit Discount Conditions Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to edit the discount system's conditions.
* @param option_number_function A vector with pointers to functions to call based on user option of the menu.
*
*/
void ShowEditDiscountsConditionsMenu(vector<void(EmpresaDeTaxis::*)()> &option_number_function);
/**
*
* @brief Reads the Edit Discount Conditions Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
* @param option_number_function A vector with pointers to functions to call based on user option of the menu.
*
*/
void SelectEditDiscountsConditionsMenuOption(EmpresaDeTaxis &Company, vector<void(EmpresaDeTaxis::*)()> &option_number_function);
/**
*
* @brief Displays the Edit Inactivation Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to set the minimium time in days since last trip for a customer to become inactive.
*
*/
void ShowEditInactivationConditionsMenu();
/**
*
* @brief Reads the Edit inactivation Conditions Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectEditInactivationConditionsMenuOption(EmpresaDeTaxis & Company);
/**
*
* @brief Displays the Exit Menu: clears the screen and couts the options available for the user to introduce to perform an action. This sub menu allows the user to exit the program, with or without saving.
*
*/
void ShowExitMenu();
/**
*
* @brief Reads the Exit Menu option from the user (according to the function that displays it). Verifies if the option introduced by the user is valid. When the user introduces a valid option, clears the screen and calls the function according to the user's input (it can either be a Sub Menu or a the function that performs the intended action).
* @param Company The system class (the class that contains all the information of the company).
*
*/
void SelectExitMenuOption(EmpresaDeTaxis &Company);