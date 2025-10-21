#pragma once
#include "clsLoginScreen.h"

bool clsLoginScreen::Login()
{
	_DrawScreenHeader("\t\tLogin Screen");
	_BankSystemLogo();
	bool LoginFailed;
	string Username, Password;
	short LoginTrials = 3;
	do
	{
		Username = clsInputValidate::ReadString("\n\t\tEnter username: ");
		Password = clsInputValidate::ReadString("\n\t\tEnter password: ");
		CurrentUser = clsUser::Find(Username, Password);
		LoginFailed = (CurrentUser.IsEmpty());
		if (LoginFailed)
		{
			--LoginTrials;
			cout << "\nInvalid Username/Password!\n";
			cout << "\nYou have " << LoginTrials << " trial(s) to login.\n";
		}
		if (LoginTrials == 0)
		{
			cout << "\n\nYou are locked after 3 failed trials.\n";
			return false;
		}
	} while (LoginFailed);

	// After Valid Login, save user in log file here
	CurrentUser.AddLoginInfoToFile();
	clsMainScreen::ShowMainMenu();
	return true;
}