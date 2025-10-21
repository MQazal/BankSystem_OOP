#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 15 - Delete User

class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _Print(clsUser& User)
	{
		cout << "\nUser Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.getFullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone Number: " << User.PhoneNumber;
		cout << "\nUsername    : " << User.getUsername();
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.getPermissions();
		cout << "\n-------------------------\n";
	}

public:
	static void DeleteUser()
	{
		_DrawScreenHeader("\t Delete User Screen");
		_BankSystemLogo();
		clsUser UserToDelete = UserToDelete.Find(clsInputValidate::ReadString("\nEnter Username: "));
		while (UserToDelete.IsEmpty())
		{
			UserToDelete = UserToDelete.Find(clsInputValidate::ReadString("\nUser isn't exist!\nEnter another username: "));
		}
		_Print(UserToDelete);
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to delete user? Y/N: "), 'Y', 'y'))
		{
			if (UserToDelete.DeleteObject())
			{
				cout << "\nAccount Deleted Successfully (-:\n";
				_Print(UserToDelete);
			}
			else
				cout << "\nError, client was not deleted\n";
		}
		else
			cout << "\nBy choosing answer 'N', operation is failed.\n";
	}
};