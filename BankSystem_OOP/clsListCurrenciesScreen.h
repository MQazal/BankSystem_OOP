#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

// Screen Number 21 - List Currencies

class clsListCurrenciesScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.getCountryName();
		cout << "| " << setw(8) << left << Currency.getCurrencyCode();
		cout << "| " << setw(45) << left << Currency.getCurrencyName();
		cout << "| " << setw(10) << left << Currency.getExchangeRate();
	}

public:
	static void ListCurrencies()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\tList Currencies Screen";
		string SubTitle = "\t   (" + to_string(vCurrencies.size()) + ") Currency(s).";
		_DrawScreenHeader(Title, SubTitle);
		_BankSystemLogo();

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
			cout << "\t\t\t\tNo Currencies Available In the System!";
		else
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyRecord(Currency);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};