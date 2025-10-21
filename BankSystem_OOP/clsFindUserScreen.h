#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include <cmath>
using namespace std;

// Screen Number 13 - Find User

class clsFindUserScreen : protected clsScreen
{
private:
    static string _PrintPermissions(clsUser& CurrentUser)
    {
        string PermissionsList = "";
        short PermissionsValue = CurrentUser.getPermissions();
        if (PermissionsValue == clsUser::enMainMenuPermissions::HaveAllPermissions)
        {
            return clsUtil::GetFullString("\t- Add New Client\n", "\t- Find Client\n", "\t- Update Client\n",
                "\t- Delete Client\n", "\t- List Clients\n", "\t- Transactions Menu\n", "\t- Manage Users\n");
        }

        short i = 1, Power = 0;
        while (i <= PermissionsValue)
        {
            switch (i)
            {
            case clsUser::enMainMenuPermissions::pAddNewClient:
                PermissionsList += "\t- Add New Client\n";
                break;

            case clsUser::enMainMenuPermissions::pFindClient:
                PermissionsList += "\t- Find Client\n";
                break;

            case clsUser::enMainMenuPermissions::pUpdateClientInfo:
                PermissionsList += "\t- Update Client\n";
                break;

            case clsUser::enMainMenuPermissions::pDeleteClient:
                PermissionsList += "\t- Delete Client\n";
                break;

            case clsUser::enMainMenuPermissions::pShowClientsList:
                PermissionsList += "\t- List Clients\n";
                break;

            case clsUser::enMainMenuPermissions::pAccessToTransactionsMenu:
                PermissionsList += "\t- Transactions Menu\n";
                break;

            case clsUser::enMainMenuPermissions::pAccessToManageUsersMenu:
                PermissionsList += "\t- Manage Users\n";
                break;
            }
            Power += 1;
            i = pow(2, Power);
        }
        return PermissionsList;
    }

    static void _Print(clsUser& CurrentUser)
    {
        cout << "\n+-------------------------------+\n";
        cout << "|       USER INFORMATION        |\n";
        cout << "+-------------------------------+\n";
        cout << "| First Name   : " << CurrentUser.FirstName << "\n";
        cout << "| Last Name    : " << CurrentUser.LastName << "\n";
        cout << "| Full Name    : " << CurrentUser.getFullName() << "\n";
        cout << "| Email        : " << CurrentUser.Email << "\n";
        cout << "| Phone Number : " << CurrentUser.PhoneNumber << "\n";
        cout << "| Username     : " << CurrentUser.getUsername() << "\n";
        cout << "| Password     : " << CurrentUser.Password << "\n";
        cout << "| Permissions  : " << CurrentUser.getPermissions() << "\n" + _PrintPermissions(CurrentUser);
        cout << "+-------------------------------+\n";
    }

public:
    static void FindUser()
    {
        _DrawScreenHeader("\t\tFind User Screen");
        _BankSystemLogo();
        clsUser FoundUser = clsUser::Find(clsInputValidate::ReadString("\nEnter Username: "));
        while (FoundUser.IsEmpty())
        {
            FoundUser = clsUser::Find(clsInputValidate::ReadString("\nUser is not exist!\nEnter another username: "));
        }
        cout << "\nUser Found (-:\n\n";
        _Print(FoundUser);
    }
};
