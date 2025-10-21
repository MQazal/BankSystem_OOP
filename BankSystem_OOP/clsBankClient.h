#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "GlobalUser.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsString.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsUtil.h"
#include "E:\Programming_Path\Course#10\OOP_Notes\OOP_Notes\clsInputValidate.h"
using namespace std;

// Business Logic Layer 1
// No UI Related code inside object.
// Object's Mode and Account Number you don't be able to be edit them outside the class
// Empty Mode -> Empty Object
// Update Mode -> Full Object
// Static Method -> Database Level
// Object Method -> Database and Obj Level
// clsBankClient* this = &Client;

class clsBankClient : public clsPerson
{
private:
	struct stTransferLogRecord;

	enum _enClientMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	_enClientMode _Mode;

	string _AccountNumber; // Primary Key -> getter method

	string _PinCode;

	float _AccountBalance = 0.0;

	bool _MarkClientForDelete = false; // default delete sign

	short _MinIndex = 0;

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream File;
		File.open("BankClients_2025.txt", ios::in);

		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsBankClient CurrentClient = ConvertDataLineToObject(DataLine);
				vClients.push_back(CurrentClient);
			}
			File.close();
		}
		return vClients;
	}

	static string _ConvertObjectToDataLine(clsBankClient Object, string delimiter = "#//#")
	{
		string DataLine;
		DataLine += Object.FirstName + delimiter;
		DataLine += Object.LastName + delimiter;
		DataLine += Object.Email + delimiter;
		DataLine += Object.PhoneNumber + delimiter;
		DataLine += Object._AccountNumber + delimiter;
		DataLine += Object._PinCode + delimiter;
		DataLine += to_string(Object._AccountBalance);
		return DataLine;
	}

	static void _AddDataLineToFile(string FileName, string DataLine)
	{
		fstream File;
		File.open(FileName, ios::app);
		if (File.is_open())
		{
			File << DataLine << '\n';
			File.close();
		}
	}

	static void _SaveClientsDataToFile(vector <clsBankClient>& vClients)
	{
		fstream File;
		File.open("BankClients_2025.txt", ios::out);
		if (File.is_open())
		{
			string DataLine;
			for (short i = 0; i < vClients.size(); i++)
			{
				if (vClients[i]._MarkClientForDelete != true)
				{
					DataLine = _ConvertObjectToDataLine(vClients[i]);
					_AddDataLineToFile("BankClients_2025.txt", DataLine);
				}
			}
			File.close();
		}
	}

	void _AddNewClientToFile()
	{
		_AddDataLineToFile("BankClients_2025.txt", _ConvertObjectToDataLine(*this));
	}

	void _UpdateObject()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
		{
			if (Client.getAccountNumber() == this->getAccountNumber())
			{
				// Account Number of index == Account Number of current running object
				Client = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
	}

	static clsBankClient _MinObject(vector <clsBankClient>& vClients)
	{
		clsBankClient MinClient = vClients[0];
		for (short i = 0; i < vClients.size(); i++)
		{
			if (clsUtil::SumDigitsASCII(vClients[i].getAccountNumber()) < clsUtil::SumDigitsASCII(MinClient.getAccountNumber()))
			{
				MinClient = vClients[i];
				MinClient._MinIndex = i;
			}
		}
		return MinClient;
	}

	string _PrepareTransferLogDataLine(float TransferAmount, clsBankClient& DestinationClient, string Separator = "#//#")
	{
		string TransferDataLine = clsDate::GetSystemDateTimeString() + Separator;
		TransferDataLine += this->_AccountNumber + Separator;
		TransferDataLine += DestinationClient.getAccountNumber() + Separator;
		TransferDataLine += to_string(TransferAmount) + Separator;
		TransferDataLine += to_string(this->_AccountBalance) + Separator;
		TransferDataLine += to_string(DestinationClient.getAccountBalance()) + Separator;
		TransferDataLine += CurrentUser.getUsername();
		return TransferDataLine;
	}

	void _RegisterTransferLog(float TransferAmount, clsBankClient& DestinationClient)
	{
		_AddDataLineToFile("TransferLog.txt", _PrepareTransferLogDataLine(TransferAmount, DestinationClient));
	}

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string TransferDataLine)
	{
		stTransferLogRecord TransferRecord;
		vector <string> vTransfer = clsString::Split(TransferDataLine, "#//#");
		TransferRecord.DateTime = vTransfer[0];
		TransferRecord.SourceClientAccountNumber = vTransfer[1];
		TransferRecord.DestinationClientAccountNumber = vTransfer[2];
		TransferRecord.TransferAmount = vTransfer[3];
		TransferRecord.NewSourceClientAccountBalance = vTransfer[4];
		TransferRecord.NewDestinationClientAccountBalance = vTransfer[5];
		TransferRecord.Username = vTransfer[6];
		return TransferRecord;
	}

	static vector <stTransferLogRecord> _LoadTransfersLogRecordsFromFile()
	{
		vector <stTransferLogRecord> vTransfersRecords;
		fstream File;
		File.open("TransferLog.txt", ios::in);
		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				vTransfersRecords.push_back(_ConvertTransferLogLineToRecord(DataLine));
			}
			File.close();
		}
		return vTransfersRecords;
	}

public:
	static struct stTransferLogRecord
	{
		string DateTime;
		string SourceClientAccountNumber;
		string DestinationClientAccountNumber;
		string TransferAmount;
		string NewSourceClientAccountBalance;
		string NewDestinationClientAccountBalance;
		string Username;
	};

	clsBankClient(_enClientMode Mode, string FirstName, string LastName, string Email, string PhoneNumber,
		string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_AccountBalance = AccountBalance;
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}

	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string getPinCode()
	{
		return _PinCode;
	}

	_declspec(property(put = setPinCode, get = getPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(put = setAccountBalance, get = getAccountBalance)) float AccountBalance;

	bool IsEmpty()
	{
		return (_Mode == _enClientMode::EmptyMode);
	}

	bool MarkForDelete()
	{
		return this->_MarkClientForDelete;
	}

	static void ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
		Client.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
		Client.Email = clsInputValidate::ReadString("\nEnter Email: ");
		Client.PhoneNumber = clsInputValidate::ReadString("\nEnter Phone Number: ");
		Client.PinCode = clsInputValidate::ReadString("\nEnter PinCode: ");
		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadDoubleNumber();
	}

	enum enSaveResults
	{
		svFaildEmptyObject = 0, svFaildAccountNumberExists = 1, svSucceeded = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case _enClientMode::EmptyMode:
			if (IsEmpty())
			return enSaveResults::svFaildEmptyObject;
		case _enClientMode::UpdateMode:
			_UpdateObject();
			return enSaveResults::svSucceeded;
		case _enClientMode::AddNewMode:
			if (IsClientExist(getAccountNumber()))
				return enSaveResults::svFaildAccountNumberExists;
			else
			{
				_AddNewClientToFile();
				_Mode = _enClientMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient getEmptyObject()
	{
		return clsBankClient(_enClientMode::EmptyMode, "", "", "", "", "", "", 0.0);
	}

	// Add Algorithm
	static clsBankClient getNewObject(string AccountNumber)
	{
		return clsBankClient(_enClientMode::AddNewMode, "", "", "", "", AccountNumber, "", 0.0);
	}

	static void Add()
	{
		// Search about empty object
		string AccountNumber = clsInputValidate::ReadString("\nEnter account number: ");
		while (IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString("\nOops, client is exist!\nEnter another account number: ");
		}
		clsBankClient NewClient = getNewObject(AccountNumber);
		ReadClientInfo(NewClient);
		clsBankClient::enSaveResults Result = NewClient.Save();
		switch (Result)
		{
		case enSaveResults::svFaildEmptyObject:
			cout << "\nError, account was not saved because it is empty )-:\n";
			break;
		case enSaveResults::svFaildAccountNumberExists:
			cout << "\nError, account is already exist )-:\n";
			break;
		case enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully (-:\n";
			break;
		}
	}

	// Find Algorithm
	static clsBankClient ConvertDataLineToObject(string DataLine)
	{
		vector <string> vLine;
		vLine = clsString::Split(DataLine, "#//#");
		return clsBankClient(_enClientMode::UpdateMode, vLine[0], vLine[1], vLine[2], vLine[3]
			, vLine[4], vLine[5], stod(vLine[6]));
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;
		fstream File;
		File.open("BankClients_2025.txt", ios::in);

		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsBankClient Client = ConvertDataLineToObject(DataLine);
				if (Client.getAccountNumber() == AccountNumber)
				{
					File.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			File.close();
		}
		return getEmptyObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;
		fstream File;
		File.open("BankClients_2025.txt", ios::in);

		if (File.is_open())
		{
			string DataLine;
			while (getline(File, DataLine))
			{
				clsBankClient Client = ConvertDataLineToObject(DataLine);
				if (Client.getAccountNumber() == AccountNumber && Client.getPinCode() == PinCode)
				{
					File.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			File.close();
		}
		return getEmptyObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	// Update Algorithm

	static void Update()
	{
		// Search about Full Object
		clsBankClient ClientToUpdate = Find(clsInputValidate::ReadString("\nEnter Account Number: "));
		while (ClientToUpdate.IsEmpty())
		{
			ClientToUpdate = Find(clsInputValidate::ReadString("\nClient isn't exist!\nenter another account number: "));
		}
		ClientToUpdate.ReadClientInfo(ClientToUpdate);
		clsBankClient::enSaveResults Result = ClientToUpdate.Save();
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

	// Delete Algorithm

	bool DeleteObject()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& Client : vClients)
		{
			if (Client.getAccountNumber() == this->getAccountNumber())
				Client._MarkClientForDelete = true;
		}
		_SaveClientsDataToFile(vClients);
		return true;
	}

	static void Delete()
	{
		clsBankClient ClientToDelete = Find(clsInputValidate::ReadString("\nEnter Account Number: "));
		while (ClientToDelete.IsEmpty())
		{
			ClientToDelete = Find(clsInputValidate::ReadString("\nClient isn't exist!\nenter another account number: "));
		}
		if (clsUtil::CharToBoolean(clsUtil::AskToPerformOperation("\nDo you want to delete client? Y/N: "), 'Y', 'y'))
		{
			if (ClientToDelete.DeleteObject())
			{
				ClientToDelete = clsBankClient::getEmptyObject();
				cout << "\nAccount Deleted Successfully (-:\n";
			}
			else
				cout << "\nError, client was not deleted\n";
		}
		else
			cout << "\nBy choosing answer 'No', operation is failed.\n";
	}

	// Show Algorithm Code in UI Layer

	static vector <clsBankClient> getClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	// Total Balances

	static double getTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;
		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	// Sorting Database

	static void SortingDatabase()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		fstream File;
		File.open("BankClients_2025.txt", ios::out);
		if (File.is_open())
		{
			for (short i = 0; i < vClients.size(); i++)
			{
				clsBankClient MinFoundClient = _MinObject(vClients);
				_AddDataLineToFile("BankClients_2025.txt", _ConvertObjectToDataLine(MinFoundClient));
				vClients.erase(vClients.begin() + MinFoundClient._MinIndex); // 0 + index = index
				--i;
			}
			File.close();
		}
		cout << "\nSorting Done Successfully (-:\n";
	}

	// Transactions

	void Deposit(double DepositAmount)
	{
		this->_AccountBalance += DepositAmount;
		this->Save();
	}

	bool Withdraw(double WithdrawAmount)
	{
		if (WithdrawAmount > this->_AccountBalance)
			return false;
		else
		{
			Deposit(WithdrawAmount * -1);
			Save();
		}
	}

	bool Transfer(float TransferAmount, clsBankClient& DestinationClient)
	{
		// this pointer points to source client
		if (TransferAmount > this->_AccountBalance)
			return false;
		else
		{
			DestinationClient.Deposit(TransferAmount);
			this->Withdraw(TransferAmount);
			_RegisterTransferLog(TransferAmount, DestinationClient);
			return true;
		}
	}

	// List Transfer Log File

	static vector <stTransferLogRecord> GetTransfersLogList()
	{
		return _LoadTransfersLogRecordsFromFile();
	}
};