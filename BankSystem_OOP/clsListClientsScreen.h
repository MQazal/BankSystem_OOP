#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 6 - List Clients

class clsListClientsScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient& Client)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.getAccountNumber();
		cout << "| " << setw(20) << left << Client.getFullName();
		cout << "| " << setw(12) << left << Client.PhoneNumber;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowClientsList()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pShowClientsList))
		{
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::getClientsList();
		string Title = "\tList Clients Screen";
		string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";
		_DrawScreenHeader(Title, SubTitle);
		_BankSystemLogo();

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
		{
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordLine(Client);
				cout << endl;
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
    }
};