#pragma once
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

    void _ClearInput()
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


string ReadString()
{
    string m = "";
	getline(cin, m);

	return m;
}
double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
{
    double Number;
	while (!(cin >> Number))
    {
	cin.clear();
	cout << ErrorMessage;
	}
	return Number;
}


static string EncryptText(string password, short key = 3)
{
    for(auto& i : password)
    {
        i = static_cast<char> (static_cast<int>(i) + key);
    }
    return password;
}

static string DecryptText(string password, short key = 3)
{
    for(auto& i : password)
    {
        i = static_cast<char> (static_cast<int>(i) - key);
    }
    return password;
}