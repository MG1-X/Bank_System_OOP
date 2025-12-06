#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "Main.h"


class clsUpdateClientScreen :protected clsScreen

{
private:
    
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";

    }

    static void ReadClientInfo(clsBankClient& Client)
    {
        cout << "Enter First Name: \n";
        Client.SetFirstName(ReadString());

        cout << "Enter Last Name: \n";
        Client.SetLastName(ReadString());

        cout << "Enter Email: \n";
        Client.SetEmail(ReadString());

        cout << "Enter Phone: \n";
        Client.SetPhone(ReadString());

        cout << "Enter Pincode: \n";
        Client.SetPinCode(ReadString());

        cout << "Enter Account Balance: \n";
        Client.SetAccountBalance(ReadDblNumber());
    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    
        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        _ClearInput();

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            ReadClientInfo(Client1);

            clsBankClient::enSaveResult SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
              
                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResult::svFailedEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;

            }

            }

        }

    }
};

