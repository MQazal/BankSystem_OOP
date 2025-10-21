#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
#include "clsAddUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsListUsersScreen.h"
using namespace std;

// Screen Number 11 - Sub Menu 2 - Manage Users Menu

class clsManageUsersScreen : protected clsScreen
{
private:
	enum _enManageUsersMenuOptions
	{
		AddUser = 1, FindUser = 2, UpdateUser = 3, DeleteUser = 4, ListSystemUsers = 5, BackToMainMenu = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		short ChoiceNumber = 0;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		ChoiceNumber = clsInputValidate::ReadIntegerNumberInRange(1, 6);
		return ChoiceNumber;
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddUserScreen::AddNewUser();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::FindUser();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::UpdateUser();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::DeleteUser();
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUsersMenu();
	}

	static void _PerformManageUsersMenu(_enManageUsersMenuOptions Option)
	{
		switch (Option)
		{
		case _enManageUsersMenuOptions::AddUser:
			_ClearScreen();
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersMenuOptions::FindUser:
			_ClearScreen();
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersMenuOptions::UpdateUser:
			_ClearScreen();
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersMenuOptions::DeleteUser:
			_ClearScreen();
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersMenuOptions::ListSystemUsers:
			_ClearScreen();
			_ShowListUsersScreen();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersMenuOptions::BackToMainMenu:
			break;
		}
	}

public:
	static void ShowManageUsersMenu()
	{
		if (!_CheckAccessRights(clsUser::enMainMenuPermissions::pAccessToManageUsersMenu))
		{
			return;
		}
		_ClearScreen();

		// Screen's Header
		_DrawScreenHeader("\tManage Users Screen");
		_BankSystemLogo();

		// Screen's Menu
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Add New User.\n";
		cout << setw(37) << left << "" << "\t[2] Find User.\n";
		cout << setw(37) << left << "" << "\t[3] Update User Info.\n";
		cout << setw(37) << left << "" << "\t[4] Delete User.\n";
		cout << setw(37) << left << "" << "\t[5] List Users.\n";
		cout << setw(37) << left << "" << "\t[6] Back to Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		// Screen's Option
		_PerformManageUsersMenu(_enManageUsersMenuOptions(_ReadManageUsersMenuOption()));
	}
};