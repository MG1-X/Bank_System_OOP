#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private :

  static  bool _Login()
    {
        bool LoginFaild = false;
        short Trials = 3;

        string Username, Password;
        do
        {
     
            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";
                Trials--;
                cout << "You have " << Trials << " Trials to login\n\n";
            }

            if (Trials == 0)
            {
                cout << "You're Locked after 3 failed Trials\n";
                return false;
            }



            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

