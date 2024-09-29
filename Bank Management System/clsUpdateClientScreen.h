#pragma once
#include"clsScreen.h"
#include "clsInputValidate.h"
#include"clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include <iomanip>
using namespace std;
class clsUpdateClientScreen:protected clsScreen
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
		cout << "\nFull Name   : " << Client.getFullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.PhoneNumber;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRight(clsUser::pUpdateClients))
		{
			return;
		}
		_DrawScreenHeader("\t Update Client Screen ");
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
		cout << "\nAre you sure you want to update this client y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";


			_ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case  clsBankClient::enSaveResults::svSuccessed:
			{
				cout << "\nAccount Updated Successfully :-)\n";

				_PrintClient(Client);
				break;
			}
			case clsBankClient::enSaveResults::svFaildEmpty:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}

			}

		}


	}
};

