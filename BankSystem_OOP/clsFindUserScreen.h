#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 13 - Find User

class clsFindUserScreen : protected clsScreen
{
private:
    static bool _CheckAccessPermission(clsUser::enMainMenuPermissions BinaryPermission, short UserPermissions)
    {
        return (BinaryPermission & UserPermissions) == BinaryPermission;
    }

    static string _ListPermissions(clsUser& CurrentUser)
    {
        vector <string> vPermissions = { "\t- Add New Client\n", "\t- Find Client\n",
        "\t- Update Client\n", "\t- Delete Client\n",
        "\t- List Clients\n", "\t- Access to Transactions Menu\n",
        "\t- Access to Manage Users Menu\n", "\t- List Login Register\n" };

        short PermissionsValue = CurrentUser.getPermissions();
        string List = "";

        // Case1: Blocked User
        if (PermissionsValue == 0)
            return "\t\n  This user doesn't have permissions.\n";
        
        // Case2: Admin User
        if (PermissionsValue == -1)
        {
            return clsUtil::GetFullString(vPermissions[0], vPermissions[1]
                , vPermissions[2], vPermissions[3], vPermissions[4], vPermissions[5],
                vPermissions[6], vPermissions[7]);
        }

        // Case3: Mix Permissions
        short Index = 0;
        for (short i = 1; i <= 128; i *= 2) // 1 Byte
        {
            if (_CheckAccessPermission(clsUser::enMainMenuPermissions(i), PermissionsValue))
            {
                List += vPermissions[Index];
            }
            ++Index;
        }
        return List;
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
        cout << "| Permissions  : " << CurrentUser.getPermissions() << "\n" + _ListPermissions(CurrentUser);
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
