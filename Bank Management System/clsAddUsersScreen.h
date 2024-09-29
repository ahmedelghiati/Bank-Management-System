#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include"clsPerson.h";
#include"clsString.h";
#include <iomanip>
using namespace std;
class clsAddUsersScreen:protected clsScreen
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
		cout << "\nEnter Permissions :\n";
		User.Permissions = _ReadPermissions();
	}
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName    : " << User.FirstName;
		cout << "\nLastName     : " << User.LastName;
		cout << "\nFull Name    : " << User.getFullName();
		cout << "\nEmail        : " << User.Email;
		cout << "\nPhone        : " << User.PhoneNumber;
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions  : " << User.Permissions;
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
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");

		string UserName = "";

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSuccessed:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmpty:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUsedUser:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}
};

