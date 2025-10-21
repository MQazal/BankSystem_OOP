#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 18 - List Login File Records

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _Print(clsUser::stLoginRegisterRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Record.DateTime;
        cout << "| " << setw(20) << left << Record.Username;
        cout << "| " << setw(20) << left << Record.Password;
        cout << "| " << setw(10) << left << Record.Permissions;
    }

public:
	static void ShowLoginInfoList()
	{
        if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pListLoginRegister))
        {
            return;
        }
        vector <clsUser::stLoginRegisterRecord> vLoginInfo = clsUser::GetLoginInfoList();
        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginInfo.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        _BankSystemLogo();

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vLoginInfo.empty())
            cout << "\t\t\t\tNo Users Registered In the System!";

        else
        {
            for (clsUser::stLoginRegisterRecord& LoginRegisterRecord : vLoginInfo)
            {
                _Print(LoginRegisterRecord);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};