#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

class clsBankClient : public clsPerson
{
public:

    struct stTrnsferLogRecord;

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 3};
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool MarkForDelete = false;

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line , Seperator);

        return clsBankClient(enMode::UpdateMode,
                         vClientData[0], 
                         vClientData[1],  
                         vClientData[2],  
                         vClientData[3], 
                         vClientData[4],  
                         vClientData[5], 
                         stod(vClientData[6]));
    }
    
    static string _ConvertClientObjectToLine(clsBankClient Client, string Seprator = "#//#")
    {
        string Line = "";
        Line += Client.GetFirstName() + Seprator;
        Line += Client.GetLastName() + Seprator;
        Line += Client.GetEmail() + Seprator;
        Line += Client.GetPhone() + Seprator;
        Line += Client.AccountNumber() + Seprator;
        Line += Client.GetPinCode() + Seprator;
        Line += to_string(Client.GetAccountBalance());

        return Line;
    }
    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;

        fstream My_File;

        My_File.open("Data.txt", ios::in);

        while (My_File.is_open())
        {
            string Line = "";

            while (getline(My_File, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }

            My_File.close();
        }  
        return vClients;
    }
    static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream My_File;

        My_File.open("Data.txt", ios::out);

        while (My_File.is_open())
        {
            string Line = "";
            
        for(auto& C : vClients)
        {
            if(C.MarkForDelete == false)
            {
                Line = _ConvertClientObjectToLine(C);
                My_File << Line << endl;
            }
        }
            My_File.close();
        }  
    }
    
    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for(auto& C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string Line)
    {
        fstream MyFile;
        MyFile.open("Data.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << Line << endl;

            MyFile.close();
        }
    }

    string _GetTime()
    {
    time_t t = time(0);
    char* dt = ctime(&t);

    string s(dt);

    if (!s.empty() && s.back() == '\n')
    {
        s.pop_back();
    }

    return s;
    }

    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);

        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }

    string _PrepareTransferLogRecord(float Amount,clsBankClient DestinationClient,
                                     string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += _GetTime() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord( Amount,  DestinationClient,  UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

public:

    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double srcBalanceAfter;
        double destBalanceAfter;
        string UserName;

    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        double AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    void SetAccountBalance(double AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    double GetAccountBalance()
    {
        return _AccountBalance;
    }

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFirstName();
        cout << "\nLastName    : " << GetLastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Data.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }                
            }
                MyFile.close();
        }
            return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Data.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }                
            }
                MyFile.close();
        }
            return _GetEmptyClientObject();
    }


    enum enSaveResult {svFailedEmptyObject = 1, svSucceeded = 2, svFaildAccountNumberExists = 3};

   enSaveResult Save()
{
    switch (_Mode)
    {
    case enMode::EmptyMode:
        return enSaveResult::svFailedEmptyObject;

    case enMode::UpdateMode:
        _Update();
        return enSaveResult::svSucceeded;

    case enMode::AddNewMode:    
        _AddNew();
        _Mode = enMode::UpdateMode;
        return enSaveResult::svSucceeded; 
    }

    return enSaveResult::svFailedEmptyObject;
}



    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClient(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }


    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for(auto& C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C.MarkForDelete = true;
                break;
                
            }
        }

        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();

        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalance()
    {
        double total = 0;

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        for(auto& C : vClients)
        {
            total += C.GetAccountBalance();
        }
        return total;

    }


    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
       if (Amount > _AccountBalance)
       {
            return false;
       }
       else
       {
            _AccountBalance -= Amount;
            Save();
            return true;
       }
    }

    bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
    {
        if (Amount > _AccountBalance)
        {   
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;
    }

    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }


};

