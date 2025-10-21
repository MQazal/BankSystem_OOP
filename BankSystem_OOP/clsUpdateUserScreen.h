#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 14 - Update User

class clsUpdateUserScreen : protected clsScreen
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
	static void UpdateUser()
	{
		_DrawScreenHeader("\tUpdate User Screen");
		_BankSystemLogo();
		clsUser UserToUpdate = UserToUpdate.Find(clsInputValidate::ReadString("\nEnter Username: "));
		while (UserToUpdate.IsEmpty())
		{
			UserToUpdate = UserToUpdate.Find(clsInputValidate::ReadString("\nUser isn't exist!\nEnter another username: "));
		}
		_Print(UserToUpdate);
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to update user? Y/N: "), 'Y', 'y'))
		{
			clsUser::ReadUserInfo(UserToUpdate);
			clsUser::enSaveResults Result = UserToUpdate.Save();
			switch (Result)
			{
			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError, account was not saved because it is empty )-:\n";
				break;
			case clsUser::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully (-:\n";
				_Print(UserToUpdate);
				break;
			}
		}
		else
			cout << "\nBy choosing answer 'N', operation is failed.\n";
	}
};