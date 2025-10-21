#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _Print(clsBankClient Client)
	{
		cout << "\n------------------------------\n";
		cout << "Full Name  : " << Client.getFullName() << endl;
		cout << "Acc Number : " << Client.getAccountNumber() << endl;
		cout << "Balance    : " << Client.AccountBalance << endl;
		cout << "-----------------------------\n";
	}

	static clsBankClient _GetClient(string Message)
	{
		clsBankClient Client = Client.Find(clsInputValidate::ReadString(Message));
		while (Client.IsEmpty())
		{
			Client = Client.Find(clsInputValidate::ReadString("\nClient isn't exist!\nenter another account number: "));
		}
		return Client;
	}

	static float _ReadTransferAmount(clsBankClient Transferee)
	{
		cout << "\nEnter Transfer Amount: ";
		float TransferAmount = clsInputValidate::ReadDoubleNumber();
		while (clsUtil::IsNumber1GraterThanNumber2(TransferAmount, Transferee.getAccountBalance()))
		{
			cout << "\nOops, Amount exceeds the available balance, Enter another Amount: ";
			TransferAmount = clsInputValidate::ReadDoubleNumber();
		}
		return TransferAmount;
	}

public:
	static void TransferMoney()
	{
		_DrawScreenHeader("\tTransfer Screen");
		_BankSystemLogo();

		clsBankClient SourceClient = _GetClient("\nPlease enter Account Number to transfer from: ");
		_Print(SourceClient);

		clsBankClient DestinationClient = _GetClient("\nPlease enter Account Number to transfer to: ");
		_Print(DestinationClient);

		// Check Balance's Amount (UI Layer)
		float TransferAmount = _ReadTransferAmount(SourceClient);

		// Ask client to perform process
		// then check Balance's Amount in Backend Layer for data integrity (Defense Programming)
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nAre you sure you want to perform this transaction? Y/N: "), 'Y', 'y'))
		{
			if (SourceClient.Transfer(TransferAmount, DestinationClient))
			{
				cout << "\nTransfer Done Successfully (-:\n";
				_Print(SourceClient);
				_Print(DestinationClient);
			}
			else
				cout << "\nOops, Amount exceeds the available balance.\n";
		}
		else
			cout << "\nBy choosing 'No' operation is failed.\n";
	}
};