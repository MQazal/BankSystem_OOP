#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 16 - List Users

class clsListUsersScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser& User)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << User.getUsername();
        cout << "| " << setw(25) << left << User.getFullName();
        cout << "| " << setw(12) << left << User.PhoneNumber;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.getPermissions();
    }

public:
    static void ShowUsersList()
    {
        vector <clsUser> vUsers = clsUser::GetUsersList();
        string Title = "\tList Users Screen";
        string SubTitle = "\t   (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);
        _BankSystemLogo();

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        
        if (vUsers.empty())
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {
            for (clsUser& User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};