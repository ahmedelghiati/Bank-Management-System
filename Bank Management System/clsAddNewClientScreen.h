#pragma once
#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include"clsClientListScreen.h"
#include <iomanip>
using namespace std;
class clsAddNewClientScreen:protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name :";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name :";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email    :";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone    :";
		Client.PhoneNumber = clsInputValidate::ReadString();
		cout << "\nEnter PinCode  :";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter Balance :";
		Client.AccountBalance = clsInputValidate::ReadDoubleNumber();
	}
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " <<Client.getFullName();
		cout << "\nEmail       : " <<Client.Email;
		cout << "\nPhone       : " <<Client.PhoneNumber;
		cout << "\nAcc. Number : " <<Client.AccountNumber();
		cout << "\nPassword    : " <<Client.PinCode;
		cout << "\nBalance     : " <<Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void AddClient()
	{
		if (!CheckAccessRight(clsUser::pAddNewClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("\t Add New Client Screen ");
		string AccountNum = "";
		cout << "\nEnter Account Number :";
		AccountNum = clsInputValidate::ReadString();
		while (clsBankClient::IsExist(AccountNum))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNum = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNum);
		_ReadClientInfo(Client);
		clsBankClient::enSaveResults SaveResults = Client.Save();
		switch (SaveResults)
		{
		case clsBankClient::svSuccessed:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(Client);
			break;
		}
		case clsBankClient::svFaildEmpty:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankClient::svFaildUsed:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
		}
	}
};

