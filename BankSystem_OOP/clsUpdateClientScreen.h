#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 4 - Update Client

class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient& UpdatedClient)
	{
		cout << "\nCard Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name      : " << UpdatedClient.FirstName;
		cout << "\nLast Name       : " << UpdatedClient.LastName;
		cout << "\nFull Name       : " << UpdatedClient.getFullName();
		cout << "\nEmail           : " << UpdatedClient.Email;
		cout << "\nPhone Number    : " << UpdatedClient.PhoneNumber;
		cout << "\nAccount Number  : " << UpdatedClient.getAccountNumber();
		cout << "\nPinCode         : " << UpdatedClient.PinCode;
		cout << "\nAccount Balance : " << UpdatedClient.AccountBalance;
		cout << "\n-------------------------\n";
	}

public:
	static void UpdateClient()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pUpdateClientInfo))
		{
			return;
		}
		_DrawScreenHeader("\tUpdate Client Screen");
		_BankSystemLogo();
		clsBankClient ClientToUpdate = ClientToUpdate.Find(clsInputValidate::ReadString("\nEnter Account Number: "));
		while (ClientToUpdate.IsEmpty())
		{
			ClientToUpdate = ClientToUpdate.Find(clsInputValidate::ReadString("\nClient isn't exist!\nenter another account number: "));
		}
		_Print(ClientToUpdate);
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nAre you sure you want to update client? Y/N: "), 'Y', 'y'))
		{
			cout << "\n____________________\n";
			clsBankClient::ReadClientInfo(ClientToUpdate);
			clsBankClient::enSaveResults Result = ClientToUpdate.Save();
			switch (Result)
			{
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError, account was not saved because it is empty )-:\n";
				break;
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully (-:\n";
				_Print(ClientToUpdate);
				break;
			}
		}
		else
			cout << "\nBy answering 'N' or 'n', operation is failed.\n";
	}
};