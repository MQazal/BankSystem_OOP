#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 3 - Find Client

class clsFindClientScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient& CurrentClient)
	{
		cout << "\n+------------------------------+\n";
		cout << "|       Client INFORMATION     |\n";
		cout << "+------------------------------+\n";
		cout << "| First Name   : " << CurrentClient.FirstName << "\n";
		cout << "| Last Name    : " << CurrentClient.LastName << "\n";
		cout << "| Full Name    : " << CurrentClient.getFullName() << "\n";
		cout << "| Email        : " << CurrentClient.Email << "\n";
		cout << "| Phone Number : " << CurrentClient.PhoneNumber << "\n";
		cout << "| Acc Number   : " << CurrentClient.getAccountNumber() << "\n";
		cout << "| PinCode      : " << CurrentClient.PinCode << "\n";
		cout << "| Acc Balance  : " << CurrentClient.AccountBalance << "\n";
		cout << "+-----------------------------+\n";
	}

public:
	static void FindClient()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("\tFind Client Screen");
		_BankSystemLogo();
		clsBankClient FoundClient = clsBankClient::Find(clsInputValidate::ReadString("\nEnter Account Number: "));
		while (FoundClient.IsEmpty())
		{
			FoundClient = clsBankClient::Find(clsInputValidate::ReadString("\nClient is not exist!\nEnter another account number: "));
		}
		cout << "\nClient Found (-:\n\n";
		_Print(FoundClient);
	}
};