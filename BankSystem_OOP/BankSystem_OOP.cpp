#include <iostream>
#include "clsMainScreen.h"
using namespace std;

int main()
{
    // after Logout, current call stack will go back to here for starting a new call stack
    // (new session from program)

    while (true)
    {
        if (!clsLoginScreen::Login())
            break;
    }
    return 0;
}