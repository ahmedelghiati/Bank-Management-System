#pragma once
#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;
class clsFindUserScreen:protected clsScreen
{
private:
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
public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t Find User Screen ");
		string UserName = "";
		cout << "\n Enter UserName :";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}
		_PrintUser(User);
	}
};

