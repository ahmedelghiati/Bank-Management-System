#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include"Global.h"
class clsLoginScreen:protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFaild = false;
		string UserName, Password;
		short Trials = 3;
		do
		{
			if (LoginFaild)
			{
				cout << "\n Invlaid User Name/Password!\n";
				cout << "You have  " << --Trials << " Trials to login\n";

			}
			if (Trials == 0)
			{
				cout << "You are locked after 3  faild trials \n";
				return false;
			}
			cout << "\nEnter UserName :";
			cin >> UserName;
			cout << "\nEnter Password :";
			cin >> Password;
			GlobalUser = clsUser::Find(UserName, Password);
			LoginFaild = GlobalUser.IsEmpty();
		} while (LoginFaild);
		GlobalUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Login Screen ");
		return _Login();
	}
};

