#pragma once
#include <iostream>
#include <iomanip>
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
#include "clsScreen.h"
#include "clsListClientsScreen.h"
#include "clsAddClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
using namespace std;


// *** Welcome in UI Layer ***
// Stubs: it is testing UI content by temporary messages inside each option to see page's navigation by:
// * Draw Main Screen  * Handle User Input(Validation)  * Convert option to appropriate method

// Screen Number 1 - Mian Menu

class clsMainScreen : protected clsScreen
{
private:
	enum _enMainMenuOptions
	{
		AddNewClient = 1, FindClient = 2,
		UpdateClient = 3, DeleteClient = 4,
		ListSystemClients = 5, TransactionsMenu = 6,
		ManageUsersMenu = 7, LoginRegister = 8, Exit = 9
	};

	static short _ReadMainMenuOption()
	{
		short ChoiceNumber = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
		ChoiceNumber = clsInputValidate::ReadIntegerNumberInRange(1, 9);
		return ChoiceNumber;
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddClientScreen::AddNewClient();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::FindClient();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::UpdateClient();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::DeleteClient();
	}

	static void _ShowListClientsScreen()
	{
		clsListClientsScreen::ShowClientsList();
	}

	static void _ShowTransactionsMenu()
	{
		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu()
	{
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowLoginRegisterScreen()
	{
		//cout << "\nLogin File Info will be here...\n";
		clsLoginRegisterScreen::ShowLoginInfoList();
	}

	static void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...";
		system("pause>0");
		ShowMainMenu();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenuOption(_enMainMenuOptions Option)
	{
		switch (Option)
		{
		case _enMainMenuOptions::AddNewClient:
			_ClearScreen();
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::FindClient:
			_ClearScreen();
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::UpdateClient:
			_ClearScreen();
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::DeleteClient:
			_ClearScreen();
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::ListSystemClients:
			_ClearScreen();
			_ShowListClientsScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::TransactionsMenu:
			_ClearScreen();
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::ManageUsersMenu:
			_ClearScreen();
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::LoginRegister:
			_ClearScreen();
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		case _enMainMenuOptions::Exit:
			_ClearScreen();
			_Logout(); // after Logout, clsMainScreen::ShowMainMenu will be killed in call stack and call stack
					   // will go back to main() to start new session with clsLoginScreen::Login()
					   // because it is in loop
			break;
		}
	}

public:
	static void ShowMainMenu()
	{
		_ClearScreen();

		// Screen's Header
		_DrawScreenHeader("\t\tMain Screen");
		_BankSystemLogo();

		// Screen's Menu
		cout << "\033[96m";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << "\033[93m";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << "\033[96m";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << "\033[92m";
		cout << setw(37) << left << "" << "\t[1] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[2] Find Client.\n";
		cout << setw(37) << left << "" << "\t[3] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[4] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[5] Show Clients List.\n";
		cout << setw(37) << left << "" << "\t[6] Go to Transactions Menu.\n";
		cout << setw(37) << left << "" << "\t[7] Go to Manage Users Menu.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register List.\n";
		cout << "\033[91m";
		cout << setw(37) << left << "" << "\t[9] Logout.\n";
		cout << "\033[96m";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << "\033[0m";
		
		// Screen's Option
		_PerformMainMenuOption(_enMainMenuOptions(_ReadMainMenuOption()));
	}
};