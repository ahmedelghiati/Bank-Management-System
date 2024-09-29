#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;
class clsWithdrawScreen:protected clsScreen
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
	static string _ReadAccountNumber()
	{
		string AccoutNumber;
		cout << "Enter AccountNumber : ";
		cin >> AccoutNumber;
		return AccoutNumber;
	}
public:
	static void ShowWhitdrawScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Deposit Screen ");
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount = 0;
		cout << "\nPlease enter withdraw amount? ";
		Amount = clsInputValidate::ReadDoubleNumber();

		cout << "\nAre you sure you want to perform this transaction? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			Client.Withdraw(Amount);
			cout << "\nAmount Withdraw Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

