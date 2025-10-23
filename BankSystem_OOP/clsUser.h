#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsString.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsUtil.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsDate.h"
using namespace std;

// Business Logic Layer 2

// The method that is represent a point to access to all system (Full Global User Object) you will
// use decryption concept with it.

// The method that is responsible about saving password to database you will use encryption concept with it.

// if there is a data from outside class in data line -> use structure to
// group data variables, download data from DB in structure vector, print each record on monitor


class clsUser : public clsPerson
{
private:
	struct stLoginRegisterRecord; // Declaration

	enum _enUserMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };

	_enUserMode _Mode;

	string _Username; // Primary Key

	string _Password;

	short _Permissions = 0;

	bool _MarkForDelete = false;

	static clsUser _getEmptyObject()
	{
		return clsUser(_enUserMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static short _ReadPermissionsToSet()
	{
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to give this user all system's permissions? Y/N: "), 'Y'))
			return -1;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to block this user from all system's permissions? Y/N: "), 'Y'))
			return 0;

		short PermissionsValue = 0;
		cout << "\n\nDo you want to give user access to:\n";
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nAdd New Client? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pAddNewClient;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nSearch about Client? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pFindClient;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nUpdate Client Information? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pUpdateClientInfo;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDelete Client? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pDeleteClient;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nShow Clients List? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pShowClientsList;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nTransactions Menu? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pAccessToTransactionsMenu;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nManage Users Menu? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pAccessToManageUsersMenu;

		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nLogin Register? Y/N: "), 'Y'))
			PermissionsValue += enMainMenuPermissions::pListLoginRegister;
		return PermissionsValue;
	}

	string _ConvertObjectToDataLine(clsUser& User, string Separator = "#//#")
	{
		string Line = User.FirstName + Separator;
		Line += User.LastName + Separator;
		Line += User.Email + Separator;
		Line += User.PhoneNumber + Separator;
		Line += User._Username + Separator;
		Line += clsUtil::EncryptText(User.Password, 10) + Separator;
		Line += to_string(User._Permissions);
		return Line;
	}

	void _AddDataLineToFile(string FileName, string DataLine)
	{
		fstream File;
		File.open(FileName, ios::app);
		if (File.is_open())
		{
			File << DataLine << endl;
			File.close();
		}
	}

	void _AddObject()
	{
		_AddDataLineToFile("BankUsers_2025.txt", _ConvertObjectToDataLine(*this));
	}

	static clsUser _ConvertDataLineToObject(string DataLine)
	{
		// each password comes from database, it will be decrypted.
		vector <string> vUser = clsString::Split(DataLine, "#//#");
		return clsUser(_enUserMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptText(vUser[5], 10), stoi(vUser[6]));
	}

	static vector <clsUser> _LoadUsersDateFromFile()
	{
		vector <clsUser> vUsers;
		fstream File;
		File.open("BankUsers_2025.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				vUsers.push_back(_ConvertDataLineToObject(DataLine));
			}
			File.close();
		}
		return vUsers;
	}

	void _SaveUsersDataToFile(vector <clsUser>& vUsers)
	{
		fstream File;
		File.open("BankUsers_2025.txt", ios::out);
		if (File.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if (User._MarkForDelete != true)
				_AddDataLineToFile("BankUsers_2025.txt", _ConvertObjectToDataLine(User));
			}
			File.close();
		}
	}

	void _UpdateObject()
	{
		vector <clsUser> vUsers = _LoadUsersDateFromFile();
		for (clsUser& User : vUsers)
		{
			if (User._Username == this->_Username)
			{
				User = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	string _PrepareLoginRecord(string delimiter = "#//#")
	{
		string LoginRecord = clsDate::GetSystemDateTimeString();
		LoginRecord += delimiter + this->_Username;
		LoginRecord += delimiter + clsUtil::EncryptText(this->_Password, 10);
		LoginRecord += delimiter + to_string(this->_Permissions);
		return LoginRecord;
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string DataLine)
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(DataLine, "#//#");
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.Username = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], 10);
		LoginRegisterRecord.Permissions = LoginRegisterDataLine[3];
		return LoginRegisterRecord;
	}

public:
	static struct stLoginRegisterRecord
	{
		string DateTime;
		string Username;
		string Password;
		string Permissions;
	};
	
	enum enMainMenuPermissions
	{
		HaveAllPermissions = -1, pAddNewClient = 1,
		pFindClient = 2, pUpdateClientInfo = 4,
		pDeleteClient = 8, pShowClientsList = 16,
		pAccessToTransactionsMenu = 32, pAccessToManageUsersMenu = 64,
		pListLoginRegister = 128
	};

	clsUser(_enUserMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string Username,
		string Password, short Permissions) : clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	string getUsername()
	{
		return _Username;
	}

	void setPassword(string Password)
	{
		_Password = Password;
	}

	string getPassword()
	{
		return _Password;
	}

	__declspec(property(put = setPassword, get = getPassword)) string Password;

	short getPermissions()
	{
		return _Permissions;
	}

	bool IsEmpty()
	{
		return this->_Mode == _enUserMode::EmptyMode;
	}

	bool IsMarkedForDelete()
	{
		return this->_MarkForDelete;
	}

	bool CheckAccessPermission(enMainMenuPermissions BinaryPermission)
	{
		if (this->_Permissions == enMainMenuPermissions::HaveAllPermissions)
			return true;
		if ((BinaryPermission & this->_Permissions) == BinaryPermission) // Binary N & Odd N
			return true;
		else
			return false;
	}

	enum enSaveResults {svFaildEmptyObject = 1, svFaildUserExists = 2, svSucceeded = 3};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case _enUserMode::EmptyMode:
			if (IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		case _enUserMode::UpdateMode:
			_UpdateObject();
			return enSaveResults::svSucceeded;
		case _enUserMode::AddMode:
			if (IsUserExist(this->_Username))
				return enSaveResults::svFaildUserExists;
			else
			{
				_AddObject();
				_Mode = _enUserMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	// Add new User Algorithm == Sign up
	
	static clsUser getNewObject(string Username)
	{
		return clsUser(_enUserMode::AddMode, "", "", "", "", Username, "", 0);
	}

	static void ReadUserInfo(clsUser& User)
	{
		User.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
		User.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
		User.Email = clsInputValidate::ReadString("\nEnter Email: ");
		User.PhoneNumber = clsInputValidate::ReadString("\nEnter Phone Number: ");
		User.Password = clsInputValidate::ReadString("\nEnter Password: ");
		User._Permissions = _ReadPermissionsToSet();
	}

	static void Add()
	{
		string Username = clsInputValidate::ReadString("\nEnter Username: ");
		clsUser User = Find(Username);
		while (!User.IsEmpty())
		{
			string Username = clsInputValidate::ReadString("\nUser is exist!\nEnter another username: ");
			User = Find(Username);
		}
		User = getNewObject(Username);
		ReadUserInfo(User);
		clsUser::enSaveResults Result = User.Save();
		switch (Result)
		{
		case enSaveResults::svFaildUserExists:
			cout << "\nFailed to save, client already exist!\n";
		case enSaveResults::svSucceeded:
			cout << "\nUser is added successfully.\n";
		}
	}

	// Find User Algorithm

	static clsUser Find(string Username)
	{
		fstream File;
		File.open("BankUsers_2025.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsUser User = _ConvertDataLineToObject(DataLine);
				if (User._Username == Username)
				{
					File.close();
					return User;
				}
			}
			File.close();
		}
		return _getEmptyObject();
	}

	static clsUser Find(string Username, string Password)
	{
		fstream File;
		File.open("BankUsers_2025.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsUser User = _ConvertDataLineToObject(DataLine); // Password is Encrypted
				if (User._Username == Username && User.Password == Password)
				{
					File.close();
					return User;
				}
			}
			File.close();
		}
		return _getEmptyObject();
	}

	static bool IsUserExist(string Username)
	{
		clsUser User = Find(Username);
		return !(User.IsEmpty());
	}

	// Update User Algorithm

	static void Update()
	{
		clsUser UserToUpdate = UserToUpdate.Find(clsInputValidate::ReadString("\nEnter Username: "));
		while (UserToUpdate.IsEmpty())
		{
			UserToUpdate = UserToUpdate.Find(clsInputValidate::ReadString("\nUser isn't exist!\nEnter another username: "));
		}
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to update user? Y/N: "), 'Y', 'y'))
		{
			ReadUserInfo(UserToUpdate);
			clsUser::enSaveResults Result = UserToUpdate.Save();
			switch (Result)
			{
			case enSaveResults::svFaildEmptyObject:
				cout << "\nError, account was not saved because it is empty )-:\n";
				break;
			case enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully (-:\n";
				break;
			}
		}
		else
			cout << "\nBy choosing answer 'N', operation is failed.\n";
	}

	// Delete User Algorithm

	bool DeleteObject()
	{
		vector <clsUser> vUsers = _LoadUsersDateFromFile();
		for (clsUser& User : vUsers)
		{
			if (User._Username == this->_Username)
			{
				User._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _getEmptyObject();
		return true;
	}

	static void Delete()
	{
		clsUser UserToDelete = UserToDelete.Find(clsInputValidate::ReadString("\nEnter Username: "));
		while (UserToDelete.IsEmpty())
		{
			UserToDelete = UserToDelete.Find(clsInputValidate::ReadString("\nUser isn't exist!\nEnter another username: "));
		}
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to delete user? Y/N: "), 'Y', 'y'))
		{
			if (UserToDelete.DeleteObject())
				cout << "\nAccount Deleted Successfully (-:\n";
			else
				cout << "\nError, client was not deleted\n";
		}
		else
			cout << "\nBy choosing answer 'N', operation is failed.\n";
	}

	// List Users
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDateFromFile();
	}

	// Log File Algorithm
	void AddLoginInfoToFile()
	{
		_AddDataLineToFile("LoginFile.txt", _PrepareLoginRecord());
	}

	// List Login Info File
	static vector <stLoginRegisterRecord> GetLoginInfoList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecords;
		fstream File;
		File.open("LoginFile.txt", ios::in);
		if (File.is_open())
		{
			string LoginRegisterDataLine;
			while (getline(File, LoginRegisterDataLine))
			{
				vLoginRegisterRecords.push_back(_ConvertLoginRegisterLineToRecord(LoginRegisterDataLine));
			}
			File.close();
		}
		return vLoginRegisterRecords;
	}
};