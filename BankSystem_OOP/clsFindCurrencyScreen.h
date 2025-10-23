#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

// Screen Number 22 - Find Currency

class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum _enSearchAboutCurrency { SearchByCountry = 1, SearchByCode = 2 };

	static short _ReadSearchWayOption()
	{
		short ChoiceNumber = 0;
		cout << setw(37) << left << "" << "Choose: Find Currency By Country[1] , Find Currency By Code[2]: ";
		ChoiceNumber = clsInputValidate::ReadIntegerNumberInRange(1, 2);
		return ChoiceNumber;
	}

	static clsCurrency _Search(_enSearchAboutCurrency SearchWay)
	{
		switch (SearchWay)
		{
		case _enSearchAboutCurrency::SearchByCountry:
			return clsCurrency::FindByCountry(clsInputValidate::ReadString("\nEnter Country Name: "));
		case _enSearchAboutCurrency::SearchByCode:
			return clsCurrency::FindByCode(clsInputValidate::ReadString("\nEnter Currency Code: "));
		}
	}

	static void _PrintCurrencyInfo(clsCurrency Currency)
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

	static void _SearchResult(clsCurrency Currency)
	{
		if (Currency.IsEmpty())
			cout << "\nOops, currency not found )-:\n";
		else
		{
			cout << "\nCurrency found (-:\n";
			_PrintCurrencyInfo(Currency);
		}
	}

public:
	static void FindCurrency()
	{
		_DrawScreenHeader("\t Find Currency Screen");
		_BankSystemLogo();
		_SearchResult(_Search(_enSearchAboutCurrency(_ReadSearchWayOption())));
	}
};