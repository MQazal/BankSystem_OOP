#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogListScreen.h"
using namespace std;

// stubs: Draw Menu , Handle Menu's Input , Convert each option to its correct screen flow , test stubs

// Screen Number 7 - Sub Menu 1 - Transactions Menu

class clsTransactionsScreen : protected clsScreen
{
private:
	enum _enTransactionsMenuOptions
	{
		Deposit = 1, Withdraw = 2,
		TotalBalances = 3, Transfer = 4,
		TransferLogList = 5, BackToMainMenu = 6
	};

	static short _ReadTransactionsMenuOption()
	{
		short ChoiceNumber = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		ChoiceNumber = clsInputValidate::ReadIntegerNumberInRange(1, 6);
		return ChoiceNumber;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::UpdateAccountBalanceByDeposit();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::UpdateAccountBalanceByWithdraw();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		//cout << "\nTransfer Money will be here...\n";
		clsTransferScreen::TransferMoney();
	}

	static void _ShowTransferLogListScreen()
	{
		//cout << "\nTransfer Log List will be here...\n";
		clsTransferLogListScreen::ListTransfersLog();
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _PerformTransactionsMenu(_enTransactionsMenuOptions Option)
	{
		switch (Option)
		{
		case _enTransactionsMenuOptions::Deposit:
			_ClearScreen();
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		case _enTransactionsMenuOptions::Withdraw:
			_ClearScreen();
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		case _enTransactionsMenuOptions::TotalBalances:
			_ClearScreen();
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		case _enTransactionsMenuOptions::Transfer:
			_ClearScreen();
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		case _enTransactionsMenuOptions::TransferLogList:
			_ClearScreen();
			_ShowTransferLogListScreen();
			_GoBackToTransactionsMenu();
			break;
		case _enTransactionsMenuOptions::BackToMainMenu:
			// Main Menu will handle this option
			break;
		}
	}

public:
	static void ShowTransactionsMenu()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pAccessToTransactionsMenu))
		{
			return;
		}
		_ClearScreen();

		// Screen's Header
		_DrawScreenHeader("\tTransactions Screen");
		_BankSystemLogo();

		// Screen's Menu
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Show Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log List.\n";
		cout << setw(37) << left << "" << "\t[6] Back to Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		// Screen's Option
		_PerformTransactionsMenu(_enTransactionsMenuOptions(_ReadTransactionsMenuOption()));
	}
};