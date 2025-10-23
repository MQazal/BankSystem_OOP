#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

// Screen Number 22 - Update Currency's Exchange Rate

class clsUpdateExchangeRateScreen : protected clsScreen
{
private:
	static void _Print(clsCurrency Currency)
	{
		cout << "\n+-------------------------------+\n";
		cout << "|      CURRENCY INFORMATION     |\n";
		cout << "+-------------------------------+\n";
		cout << "| Country Name  : " << Currency.getCountryName() << endl;
		cout << "| Currency Code : " << Currency.getCurrencyCode() << endl;
		cout << "| Currency Name : " << Currency.getCurrencyName() << endl;
		cout << "| Rate/1$       : " << Currency.getExchangeRate() << endl;
		cout << "+-------------------------------+\n";
	}

	static void _UpdateResult(clsCurrency& Currency)
	{
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nAre you sure you want to update exchange rate? Y/N: "), 'Y', 'y'))
		{
			cout << "\n\nUpdate Currency Rate:\n-------------------\n";
			cout << "Enter new Exchnage Rate: ";
			Currency.UpdateExchangeRate(clsInputValidate::ReadDoubleNumber());
			cout << "\nCurrency Rate updated Successfully (-:\n";
			_Print(Currency);
		}
		else
			cout << "\nOperation is failed :-(\n";
	}

public:
	static void UpdateExchangeRate()
	{
		clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString("\nEnter Currency Code: "));
		while (Currency.IsEmpty())
		{
			Currency = clsCurrency::FindByCode(clsInputValidate::ReadString("\nCurrency not found!\nEnter another Currency Code: "));
		}
		_Print(Currency);
		_UpdateResult(Currency);
	}
};