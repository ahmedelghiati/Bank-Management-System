#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include <iomanip>
using namespace std;
class clsClientListScreen:protected clsScreen
{
private:
	static void PrintClientRecord(clsBankClient& Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left 
            << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.getFullName();
        cout << "| " << setw(12) << left << Client.PhoneNumber;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }
public:
    static void ShowClientList()
    {
        if (!CheckAccessRight(clsUser::pListClients))
        {
            return;
        }
        vector<clsBankClient>vClients = clsBankClient::GetClientList();
        string Title = "\t\tClient List ";
        string SubTitle = "\t\t(" + to_string(vClients.size()) + ") Client (s) ";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                PrintClientRecord(C);
                cout << "\n";
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

