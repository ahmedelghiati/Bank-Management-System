#pragma once
#include<iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsUtil.h"
using namespace std;
class clsTotalBalancesScreen: protected clsScreen
{
private:
	static void PrintClientRecordBalancesLine(clsBankClient& Client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left 
			<< Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.getFullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}
public:
	static void ShowTotalBalancesScreen()
	{
        vector <clsBankClient> vClients = clsBankClient::GetClientList();
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        double totalBalances = clsBankClient::GetTotalBalances();
        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                PrintClientRecordBalancesLine(C);
                cout << "\n";
            }
        }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << "\t\t\t\tTotal Balances = " << totalBalances << "\n";
        cout << "\t\t(" << clsUtil::NumToTxt(totalBalances) << ")";
	}
};

