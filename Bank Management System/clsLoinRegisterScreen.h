#pragma once
#include "clsScreen.h"
#include <iostream>
#include"clsDate.h"
using namespace std;
class clsLoinRegisterScreen:protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser::sLoginregister Record)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left
            << Record.DateTime;
        cout << "| " << setw(20) << left << Record.UserName;
        cout << "| " << setw(20) << left << Record.Password;
        cout << "| " << setw(10) << left << Record.Permissions;
    }
public:
	static void ShowLoginRegister()
    {
        if (!CheckAccessRight(clsUser::pLogin))
        {
            return;
        }
        vector <clsUser::sLoginregister> vLoginRegister = clsUser::GetRegisterLogInList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegister.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date&Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vLoginRegister.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {

            for (clsUser::sLoginregister Record : vLoginRegister)
            {

                _PrintUserRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

    }
};

