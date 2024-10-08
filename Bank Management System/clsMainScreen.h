#pragma once
#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include"clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionScreen.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsManageUsersScreen.h"
#include"Global.h"
#include"clsLoinRegisterScreen.h"
#include <iomanip>
using namespace std;
class clsMainScreen: protected clsScreen
{
private:
	enum enMainMenueOptions{
        enListClients = 1, enAddNewClient = 2, enDeleteClient = 3,
        enUpdateClient = 4, enFindClient = 5, enShowTransactionsMenue = 6,
        enManageUsers = 7, enLogin=8 ,enExit = 9
    };
    static short _ReadMainoption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short Choice = clsInputValidate::ReadIntNumBetween(1, 9, "Enter Number between 1 to 9? ");
        return Choice;
    }
    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientList();
    }
    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::AddClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionScreen::ShowTransactionsMenue();
    }
    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }
    static void _ShowLoginRegister()
    {
        clsLoinRegisterScreen::ShowLoginRegister();
    }
    static void _Logout()
    {
        GlobalUser = clsUser::Find("", "");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions Option)
    {
        switch (Option)
        {
        case enListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enAddNewClient:
        {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enShowTransactionsMenue:
        {
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        }
        case enManageUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        }
        case enLogin:
        {
            system("cls");
            _ShowLoginRegister();
            _GoBackToMainMenue();
            break;
        }
        case enExit:
        {
            system("cls");
            _Logout();
            break;
        }
        }
    }
public:
    static void ShowMainMenue()
    {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainoption());
    }
};