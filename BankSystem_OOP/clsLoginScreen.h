#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
using namespace std;

// Screen Number 17 - Login to the System
// each new login process, there is a new global user uses this system from #include "GlobalUser.h"

class clsLoginScreen : protected clsScreen
{
public:
	static bool Login();
};