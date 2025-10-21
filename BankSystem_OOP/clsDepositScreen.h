#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 8 - Deposit Money

class clsDepositScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient& Client)
	{
		cout << "\nCard Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name      : " << Client.FirstName;
		cout << "\nLast Name       : " << Client.LastName;
		cout << "\nFull Name       : " << Client.getFullName();
		cout << "\nEmail           : " << Client.Email;
		cout << "\nPhone Number    : " << Client.PhoneNumber;
		cout << "\nAccount Number  : " << Client.getAccountNumber();
		cout << "\nPinCode         : " << Client.PinCode;
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n-------------------------\n";
	}

public:
	static void UpdateAccountBalanceByDeposit()
	{
		_DrawScreenHeader("\tDeposit Screen");
		_BankSystemLogo();

		string AccountNumber = clsInputValidate::ReadString("\nEnter Account Number: ");
		clsBankClient Client = Client.Find(AccountNumber);
		while (Client.IsEmpty())
		{
			AccountNumber = clsInputValidate::ReadString("\nClient with [" + AccountNumber + "] dose not exist!\n\nEnter another Account Number: ");
			Client = Client.Find(AccountNumber);
		}
		_Print(Client);

		cout << "\nEnter deposit amount: ";
		double DepositAmount = clsInputValidate::ReadDoubleNumber();
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nAre you sure you want to perform this transaction? Y/N: "), 'Y', 'y'))
		{
			Client.Deposit(DepositAmount);
			cout << "\nDeposit is done (-:\n\nNew Balance is: ";
			cout << Client.AccountBalance << endl;
		}
		else
			cout << "\nBy choosing answer 'No', operation is failed.\n";
	}
};