#pragma once
#include<iostream>
#include<string>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include <iomanip>
using namespace std;
class clsFindClientScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.getFullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.PhoneNumber;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
	}
public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRight(clsUser::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("\t Find Client Screen ");
		string AccountNum = "";
		cout << "\nEnter Account Number :";
		AccountNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsExist(AccountNum))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNum = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNum);
		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client);


	}
};

