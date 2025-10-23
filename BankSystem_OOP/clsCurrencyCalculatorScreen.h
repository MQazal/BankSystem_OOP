#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

// Screen Number 23 - Currency Calculator

// 1- Convert Currency to USD -> ExchangeAmount / Exchange Rate of Currency
// 2- Convert from Currency1 to Currency2:
// - Convert Currency1 to USD.
// - Convert USD to Currency2.
// (ExchangeAmount / Exchange Rate of Currency1) * Exchange Rate of Currency2

class clsCurrencyCalculator : protected clsScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency, string Title)
	{
		cout << "\n" + Title + "\n";
		cout << "-------------------------------\n";
		cout << "Country Name  : " << Currency.getCountryName() << endl;
		cout << "Currency Code : " << Currency.getCurrencyCode() << endl;
		cout << "Currency Name : " << Currency.getCurrencyName() << endl;
		cout << "Rate/1$       : " << Currency.getExchangeRate() << endl;
		cout << "--------------------------------\n";
	}

	static clsCurrency _GetCurrency(string Message)
	{
		clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString(Message));
		while (Currency.IsEmpty())
		{
			Currency = clsCurrency::FindByCode(clsInputValidate::ReadString("\nCurrency not found!\nEnter another Currency Code: "));
		}
		return Currency;
	}

	static float _ReadAmountOfExchangeRate()
	{
		cout << "\nEnter amount to exchange: ";
		return (float)clsInputValidate::ReadDoubleNumber();
	}

	static void _PrintConvertingResult(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrencyInfo(Currency1, "Convert From");

		cout << Amount << " " << Currency1.getCurrencyCode() << " = "
			<< Currency1.ConvertCurrencyToUSD(Amount) << " " + Currency2.getCurrencyCode() << endl;

		if (Currency2.getCurrencyCode() == "USD")
			return;

		else
		{
			_PrintCurrencyInfo(Currency2, "Convert To");
			cout << Amount << " " << Currency1.getCurrencyCode() << " = "
				<< Currency1.ConvertToOtherCurrency(Amount, Currency2.getExchangeRate())
				<< " " + Currency2.getCurrencyCode() << endl;
		}
	}

public:
	static void ShowCurrencyCalculator()
	{
		bool PerformCalculation;
		do
		{
			_ClearScreen();
			_DrawScreenHeader("\tCurrency Calculator Screen");
			_BankSystemLogo();
			clsCurrency CurrencyFrom = _GetCurrency("\nEnter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nEnter Currency2 Code: ");
			float Amount = _ReadAmountOfExchangeRate();
			_PrintConvertingResult(Amount, CurrencyFrom, CurrencyTo);
			PerformCalculation = (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\n\n\nDo you want to perform another calculation? Y/N: "), 'Y', 'y'));
		} while (PerformCalculation);
	}
};