#pragma once
#include <iostream>
#include <string>
using namespace std;

class InterfaceCommunication
{
	// this interface has pure virtual functions that are implemented in class inherits it
public:
	virtual void SendEmail(string Title, string Body) = 0;
	virtual void SendSMS(string Title, string Body) = 0;
	virtual void SendFax(string Title, string Body) = 0;
};