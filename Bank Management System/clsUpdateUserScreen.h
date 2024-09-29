#pragma once
#include "clsInputValidate.h"
#include "clsScreen.h"
#include"clsUserlistScreen.h"
#include"clsAddUsersScreen.h"
#include"clsDeleteUserScreen.h"
#include <iostream>
using namespace std;
class clsUpdateUserScreen:protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter First Name :";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name :";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email    :";
		User.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone    :";
		User.PhoneNumber = clsInputValidate::ReadString();
		cout << "\nEnter PinCode  :";
		User.Password = clsInputValidate::ReadString();
		cout << "\nEnter Permissions :";
		User.Permissions = _ReadPermissions();
	}
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName       : " << User.FirstName;
		cout << "\nLastName        : " << User.LastName;
		cout << "\nFull Name       : " << User.getFullName();
		cout << "\nEmail           : " << User.Email;
		cout << "\nPhone           : " << User.PhoneNumber;
		cout << "\nPassword        : " << User.Password;
		cout << "\nPermissions     : " << User.Permissions;
		cout << "\n___________________\n";

	}
	static int _ReadPermissions()
	{
		int Permission = 0;
		char Res = 'n';
		cout << "Do you want to give full access? y/n? ";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			return (clsUser::enPermissions::eAll);
		}
		cout << "\nDo you want to give access to : \n ";
		cout << "\nShow Client Menue ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pListClients;
		}
		cout << "\nAdd New Client ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nDelete Client  ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pDeleteClient;
		}
		cout << "\nUpdate Client ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pUpdateClients;
		}
		cout << "\nFind Client ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pFindClient;
		}
		cout << "\n Transactions ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pTranactions;
		}
		cout << "\nManage Users ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pManageUsers;
		}
		cout << "\nLogin Register ?y/n?";
		cin >> Res;
		if (toupper(Res) == 'Y')
		{
			Permission += clsUser::enPermissions::pLogin;
		}
		return Permission;
	}

public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\tUpdate User Screen");

		string UserName = "";

		cout << "\nPlease Enter User UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nAccount number is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);
		cout << "\nAre you sure you want to update this User y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";
			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult;

			SaveResult = User.Save();

			switch (SaveResult)
			{
			case  clsUser::enSaveResults::svSuccessed:
			{
				cout << "\nUser Updated Successfully :-)\n";

				_PrintUser(User);
				break;
			}
			case clsUser::enSaveResults::svFaildEmpty:
			{
				cout << "\nError User was not saved because it's Empty";
				break;

			}

			}
		}
	}
};

