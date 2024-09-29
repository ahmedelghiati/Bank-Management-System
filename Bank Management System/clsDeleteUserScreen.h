#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include"clsPerson.h"
#include"clsScreen.h"
#include"clsString.h"
#include"clsUser.h"
#include <iomanip>
using namespace std;
class clsDeleteUserScreen:protected clsScreen
{
private:
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
public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");
		string UserName = "";
		cout << "\nEnter UserName :";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		cout << "\nAre you sure you wanted to delete this User ?";
		char Answer = 'n';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError user Was not Deleted\n";
			}
		}
	}
};

