#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

// Screen Number 12 - Add New User

class clsAddUserScreen : protected clsScreen
{
private:
	static void _Print(clsUser& NewUser)
	{
		cout << "\nCard Info:\n";
		cout << "-------------------------";
		cout << "\nFirst Name  : " << NewUser.FirstName;
		cout << "\nLast Name   : " << NewUser.LastName;
		cout << "\nFull Name   : " << NewUser.getFullName();
		cout << "\nEmail       : " << NewUser.Email;
		cout << "\nPhone Number: " << NewUser.PhoneNumber;
		cout << "\nUsername    : " << NewUser.getUsername();
		cout << "\nPassword    : " << NewUser.Password;
		cout << "\nPermissions : " << NewUser.getPermissions();
		cout << "\n-------------------------\n";
	}

public:
	static void AddNewUser()
	{
		_DrawScreenHeader("\t  Add New User Screen");
		_BankSystemLogo();
		string Username = clsInputValidate::ReadString("\nEnter Username: ");
		clsUser User = User.Find(Username);
		while (!User.IsEmpty())
		{
			string Username = clsInputValidate::ReadString("\nUser is exist!\nEnter another username: ");
			User = User.Find(Username);
		}
		User = User.getNewObject(Username);
		clsUser::ReadUserInfo(User);
		clsUser::enSaveResults Result = User.Save();
		switch (Result)
		{
		case clsUser::enSaveResults::svFaildUserExists:
			cout << "\nFailed to save, client already exist!\n";
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser added successfully.\n";
			_Print(User);
		}
	}
};