#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 5 - Delete Client

class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient& DeletedClient)
	{
		cout << "\nCard Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name      : " << DeletedClient.FirstName;
		cout << "\nLast Name       : " << DeletedClient.LastName;
		cout << "\nFull Name       : " << DeletedClient.getFullName();
		cout << "\nEmail           : " << DeletedClient.Email;
		cout << "\nPhone Number    : " << DeletedClient.PhoneNumber;
		cout << "\nAccount Number  : " << DeletedClient.getAccountNumber();
		cout << "\nPinCode         : " << DeletedClient.PinCode;
		cout << "\nAccount Balance : " << DeletedClient.AccountBalance;
		cout << "\n-------------------------\n";
	}

public:
	static void DeleteClient()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("\tDelete Client Screen");
		_BankSystemLogo();
		clsBankClient ClientToDelete = clsBankClient::Find(clsInputValidate::ReadString("\nEnter Account Number: "));
		while (ClientToDelete.IsEmpty())
		{
			ClientToDelete = clsBankClient::Find(clsInputValidate::ReadString("\nClient isn't exist!\nenter another account number: "));
		}
		_Print(ClientToDelete);
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to delete client? Y/N: "), 'Y', 'y'))
		{
			if (ClientToDelete.DeleteObject())
			{
				ClientToDelete = clsBankClient::getEmptyObject();
				cout << "\nAccount Deleted Successfully (-:\n";
				_Print(ClientToDelete);
			}
			else
				cout << "\nError, client was not deleted\n";
		}
		else
			cout << "\nBy answering 'N' or 'n', operation is failed.\n";
	}
};