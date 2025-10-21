#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

// Screen Number 19 - List Transfer Log Records

class clsTransferLogListScreen : protected clsScreen
{
private:
	static void _PrintTransferRecord(clsBankClient::stTransferLogRecord Record)
	{
        cout << setw(8) << left << "" << "| " << setw(23) << left << Record.DateTime;
        cout << "| " << setw(8) << left << Record.SourceClientAccountNumber;
        cout << "| " << setw(8) << left << Record.DestinationClientAccountNumber;
        cout << "| " << setw(8) << left << Record.TransferAmount;
        cout << "| " << setw(10) << left << Record.NewSourceClientAccountBalance;
        cout << "| " << setw(10) << left << Record.NewDestinationClientAccountBalance;
        cout << "| " << setw(8) << left << Record.Username;
	}

public:
	static void ListTransfersLog()
	{
		vector <clsBankClient::stTransferLogRecord> vTransfersRecords = clsBankClient::GetTransfersLogList();
        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t\t(" + to_string(vTransfersRecords.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        _BankSystemLogo();

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransfersRecords.empty())
            cout << "\t\t\t\tNo Transfers Available in the system!";
        else
        {
            for (clsBankClient::stTransferLogRecord& Record : vTransfersRecords)
            {
                _PrintTransferRecord(Record);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};