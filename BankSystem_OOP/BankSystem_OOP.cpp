#include <iostream>
#include "clsMainScreen.h"
using namespace std;

// The UI functions that display multiple records stay outside the class,
// while methods that work with individual objects stay inside the class.

int main()
{
// after Logout, current call stack will go back to here for starting a new call stack (new session from program)

    while (true) // infinity loop will keep using CPU resources indefinitely.
    {
        if (!clsLoginScreen::Login()) // after 3 failed login trials, this infinity loop will be killed
            break;
    }


    //int X = 3;
    //while (true)
    //{
    //    --X;
    //    if (X == 0)
    //        break;
    //}
    //cout << "\nX = " << X << endl;
    /*
    00011111
    00000100  &
    --------
    00000100 = 4
    */
    return 0;
}