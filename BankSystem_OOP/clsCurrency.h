#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsString.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsUtil.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
using namespace std;

// Business Logic Layer 3

class clsCurrency
{
private:
	enum _enCurrencyMode { EmptyMode = 0, UpdateMode = 1 };
	_enCurrencyMode _Mode;

	string _CountryName;

	string _CurrencyCode;

	string _CurrencyName;

	float _ExchangeRate = 0.0;

	static clsCurrency _ConvertDataLineToObject(string DataLine)
	{
		vector <string> vCurrencyData = clsString::Split(DataLine, "#//#");
		return clsCurrency(_enCurrencyMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static clsCurrency _GetEmptyObject()
	{
		return clsCurrency(_enCurrencyMode::EmptyMode, "", "", "", 0.0);
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				vCurrencies.push_back(_ConvertDataLineToObject(DataLine));
			}
			File.close();
		}
		return vCurrencies;
	}

	static void _AddDataLineToFile(string FileName, string DataLine)
	{
		fstream File;
		File.open(FileName, ios::app);
		if (File.is_open())
		{
			File << DataLine << endl;
			File.close();
		}
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency>& vCurrencies)
	{
		fstream File;
		File.open("Currencies.txt", ios::out);
		if (File.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_AddDataLineToFile("Currencies.txt", _ConvertObjectToDataLine(Currency, "#//#"));
			}
			File.close();
		}
	}

	void _UpdateObject()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency._CurrencyCode == this->_CurrencyCode)
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrenciesDataToFile(vCurrencies);
	}

	static string _ConvertObjectToDataLine(clsCurrency& Currency, string Separator = "#//#")
	{
		string DataLine = Currency._CountryName + Separator;
		DataLine += Currency._CurrencyCode + Separator;
		DataLine += Currency._CurrencyName + Separator;
		DataLine += to_string(Currency._ExchangeRate);
		return DataLine;
	}

public:
	clsCurrency(_enCurrencyMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float ExchangeRate)
	{
		this->_Mode = Mode;
		this->_CountryName = CountryName;
		this->_CurrencyCode = CurrencyCode;
		this->_CurrencyName = CurrencyName;
		this->_ExchangeRate = ExchangeRate;
	}

	string getCountryName()
	{
		return this->_CountryName;
	}

	string getCurrencyCode()
	{
		return this->_CurrencyCode;
	}

	string getCurrencyName()
	{
		return this->_CurrencyName;
	}

	void UpdateExchangeRate(float NewExchangeRate)
	{
		// set new Exchange Rate must be converted to Data Layer not object level only
		this->_ExchangeRate = NewExchangeRate;
		_UpdateObject();
	}

	float getExchangeRate()
	{
		return this->_ExchangeRate;
	}

	bool IsEmpty()
	{
		return _Mode == _enCurrencyMode::EmptyMode;
	}

	// Find Currency Algorithm

	static clsCurrency FindByCountry(string CountryName)
	{
		CountryName = clsString::UpperAllString(CountryName);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsCurrency Currency = _ConvertDataLineToObject(DataLine);
				if (clsString::UpperAllString(Currency._CountryName) == CountryName)
					return Currency;
			}
			File.close();
		}
		return _GetEmptyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsCurrency Currency = _ConvertDataLineToObject(DataLine);
				if (Currency._CurrencyCode == CurrencyCode)
					return Currency;
			}
			File.close();
		}
		return _GetEmptyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return !(Currency.IsEmpty());
	}

	// List Currencies

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	// Currency Calculator

	float ConvertCurrencyToUSD(float Amount)
	{
		return float(Amount / this->_ExchangeRate);
	}

	float ConvertToOtherCurrency(float Amount, float Currency2Rate)
	{
		return float(ConvertCurrencyToUSD(Amount) * Currency2Rate);
	}
};