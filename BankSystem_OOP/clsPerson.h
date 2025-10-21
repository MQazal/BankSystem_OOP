#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"
using namespace std;

// you must implement interface class pure methods by overriding concept
class clsPerson : public InterfaceCommunication
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _PhoneNumber;

public:
	clsPerson(string FirstName, string LastName, string Email, string PhoneNumber)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_PhoneNumber = PhoneNumber;
	}

	void setFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string getFirstName()
	{
		return _FirstName;
	}

	__declspec(property(put = setFirstName, get = getFirstName)) string FirstName;

	void setLastName(string LastName)
	{
		_LastName = LastName;
	}

	string getLastName()
	{
		return _LastName;
	}

	__declspec(property(put = setLastName, get = getLastName)) string LastName;

	string getFullName()
	{
		return _FirstName + " " + _LastName;
	}

	void setEmail(string Email)
	{
		_Email = Email;
	}

	string getEmail()
	{
		return _Email;
	}

	__declspec(property(put = setEmail, get = getEmail)) string Email;

	void setPhoneNumber(string PhoneNumber)
	{
		_PhoneNumber = PhoneNumber;
	}

	string getPhoneNumber()
	{
		return _PhoneNumber;
	}

	__declspec(property(put = setPhoneNumber, get = getPhoneNumber)) string PhoneNumber;

	// interface

	void SendEmail(string Title, string Body)
	{

	}

	void SendSMS(string Title, string Body)
	{

	}

	void SendFax(string Title, string Body)
	{

	}
};