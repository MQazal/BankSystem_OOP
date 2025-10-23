#pragma once
#include <iostream>
#include "GlobalUser.h"
using namespace std;

// Base UI Layer of all Project's Screens

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        if (CurrentUser.getPermissions() == -1)
        {
            cout << "\n\t\t\t\t\t\t\tUser: Admin";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tUser: " + CurrentUser.getUsername();
        }
        cout << "\n\n\t\t\t\t\t\t\tDate: " + clsDate::DateToString(clsDate());
    }

    static void _BankSystemLogo()
    {
        cout << R"(
      ____             _    
     |  _ \           | |   
     | |_) | __ _ _ __| | __
     |  _ < / _` | '__| |/ /
     | |_) | (_| | |  |   < 
     |____/ \__,_|_|  |_|\_\
)" << endl << endl;
    }

    static void _ClearScreen()
    {
        system("cls");
    }

    static bool _CheckAccessRights(clsUser::enMainMenuPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
            return true;
    }
};