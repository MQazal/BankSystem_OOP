#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 2 - Add New Client

class clsAddClientScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient& NewClient)
	{
		cout << "\nCard Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name      : " << NewClient.FirstName;
		cout << "\nLast Name       : " << NewClient.LastName;
		cout << "\nFull Name       : " << NewClient.getFullName();
		cout << "\nEmail           : " << NewClient.Email;
		cout << "\nPhone Number    : " << NewClient.PhoneNumber;
		cout << "\nAccount Number  : " << NewClient.getAccountNumber();
		cout << "\nPinCode         : " << NewClient.PinCode;
		cout << "\nAccount Balance : " << NewClient.AccountBalance;
		cout << "\n-------------------------\n";
	}

public:
	static void AddNewClient()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pAddNewClient))
		{
			return;
		}
		_DrawScreenHeader("\tAdd Client Screen");
		_BankSystemLogo();
		string AccountNumber = clsInputValidate::ReadString("\nEnter account number: ");
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString("\nOops, client is exist!\nEnter another account number: ");
		}
		clsBankClient NewClient = clsBankClient::getNewObject(AccountNumber);
		clsBankClient::ReadClientInfo(NewClient);
		clsBankClient::enSaveResults Result = NewClient.Save();
		switch (Result)
		{
		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\nError, account was not saved because it is empty )-:\n";
			break;
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
			cout << "\nError, account is already exist )-:\n";
			break;
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully (-:\n";
			_Print(NewClient);
			break;
		}
	}
};