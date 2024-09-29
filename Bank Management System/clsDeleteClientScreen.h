#pragma once
#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include"clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include <iomanip>
using namespace std;
class clsDeleteClientScreen:protected clsScreen
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
		cout << "\n___________________\n";
	}
public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRight(clsUser::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("\tDelete Client Screen");
		string AccountNum = "";
		cout << "\nEnter Account Number :";
		AccountNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsExist(AccountNum))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNum = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNum);
		_PrintClient(Client);
		cout << "Are you sure you wanted to delete this client ?";
		char Answer = 'n';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}
};

