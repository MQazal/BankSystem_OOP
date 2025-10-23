#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateExchangeRateScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

// Screen Number 20 - Sub Menu 3 - Currency Exchange Menu

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum _enCurrencyExchangeMenuOptions
	{
		FindCurrency = 1, UpdateExchangeRate = 2,
		ListCurrencies = 3, CurrencyCalculator = 4,
		BackToMainMenu = 5
	};

	static short _ReadCurrencyExchangeMenuOption()
	{
		short ChoiceNumber = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		ChoiceNumber = clsInputValidate::ReadIntegerNumberInRange(1, 5);
		return ChoiceNumber;
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::FindCurrency();
	}

	static void _ShowUpdateExchangeRateScreen()
	{
		clsUpdateExchangeRateScreen::UpdateExchangeRate();
	}

	static void _ShowListCurrenciesScreen()
	{
		clsListCurrenciesScreen::ListCurrencies();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculator::ShowCurrencyCalculator();
	}

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menu...";
		system("pause>0");
		ShowCurrencyExchangeMenu();
	}

	static void _PerformCurrencyExchangeMenu(_enCurrencyExchangeMenuOptions Option)
	{
		switch (Option)
		{
		case _enCurrencyExchangeMenuOptions::FindCurrency:
			_ClearScreen();
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case _enCurrencyExchangeMenuOptions::UpdateExchangeRate:
			_ClearScreen();
			_ShowUpdateExchangeRateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case _enCurrencyExchangeMenuOptions::ListCurrencies:
			_ClearScreen();
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case _enCurrencyExchangeMenuOptions::CurrencyCalculator:
			_ClearScreen();
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case _enCurrencyExchangeMenuOptions::BackToMainMenu:
			break;
		}
	}

public:
	static void ShowCurrencyExchangeMenu()
	{
		_ClearScreen();

		// Screen's Header
		_DrawScreenHeader("\tCurrency Exchange Screen");
		_BankSystemLogo();

		// Screen's Menu
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[2] Update Exchange Rate.\n";
		cout << setw(37) << left << "" << "\t[3] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Back to Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		// Screen's Option
		_PerformCurrencyExchangeMenu(_enCurrencyExchangeMenuOptions(_ReadCurrencyExchangeMenuOption()));
	}
};