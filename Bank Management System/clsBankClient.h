#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include"clsPerson.h";
#include"clsString.h";
#include <iomanip>
using namespace std;
class clsBankClient : public clsPerson
{
private:
	enum enMode { Emptymode = 0, UpdateMode = 1,AddNewMode=2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _Balance;
	bool _MarkedForDelete = false;
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4], vClientData[5],
			stod(vClientData[6]));
	}
	static clsBankClient _GetEmptyClientobject()
	{
		return clsBankClient(enMode::Emptymode, "", "", "", "", "", "", 0);
	}
	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.PhoneNumber + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;

	}
	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}
	string _PrepareTransferLog(double Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferLog = "";
		TransferLog += clsDate::GetSystemDateTime() + Seperator;
		TransferLog += AccountNumber() + Seperator;
		TransferLog += DestinationClient.AccountNumber () + Seperator;
		TransferLog += to_string(Amount) + Seperator;
		TransferLog += to_string(AccountBalance) + Seperator;
		TransferLog += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLog += UserName;
		return TransferLog;
	}
	void _RegisterTrangerLog(double Amount ,clsBankClient DestinationClient,string UserName )
	{
		string DataLine = _PrepareTransferLog(Amount, DestinationClient, UserName);
		fstream MyFile;
		MyFile.open("transfarLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}
	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}

	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	void _AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	void _Update()
	{
		vector <clsBankClient>_vClient;
		_vClient = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClient);
	}
	struct sTransferLog;
	static sTransferLog _ConvertTransferLogToLineObject(string Line, string Seperator = "#//#")
	{
		vector<string> vTransferLog = clsString::Split(Line, Seperator);
		sTransferLog TransferLog;
		TransferLog.DateTime = vTransferLog[0];
		TransferLog.SourceAccountNumber = vTransferLog[1];
		TransferLog.DestinationAccountNumber = vTransferLog[2];
		TransferLog.Amount = stod(vTransferLog[3]);
		TransferLog.srcBalanceAfter = stod(vTransferLog[4]);
		TransferLog.destBalanceAfter = stod(vTransferLog[5]);
		TransferLog.UserName = vTransferLog[6];
		return TransferLog;
	}


public:
	struct sTransferLog
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};

	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = AccountBalance;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::Emptymode);
	}
	string AccountNumber()
	{
		return _AccountNumber;
	}
	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float Balance)
	{
		_Balance = Balance;
	}

	float GetAccountBalance()
	{
		return _Balance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	static clsBankClient Find(string AccountNum)
	{
		vector<clsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client._AccountNumber == AccountNum)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientobject();
	}
	static clsBankClient Find(string AccountNum, string PinCode)
	{
		vector<clsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client._AccountNumber == AccountNum && Client._PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientobject();
	}
	static bool IsExist(string AccountNum)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNum);
		return (!Client1.IsEmpty());
	}
	bool Delete()
	{
		vector< clsBankClient>_vClient ;
		_vClient = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClient);
		*this = _GetEmptyClientobject();
		return true;
	}
	enum enSaveResults { svFaildEmpty = 0, svSuccessed = 1, svFaildUsed = 2 };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::Emptymode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmpty;
			}

		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSuccessed;
			break;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsExist(_AccountNumber))
			{
				return enSaveResults::svFaildUsed;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSuccessed;
			}

			break;
		}
		}
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	static vector<clsBankClient>GetClientList()
	{
		return _LoadClientsDataFromFile();
	}
	static double GetTotalBalances()
	{
		double Total = 0;
		vector< clsBankClient>vClient = _LoadClientsDataFromFile();
		for (clsBankClient C : vClient)
		{
			Total += C.AccountBalance;
		}
		return Total;
	}
	void Deposit(double Amount)
	{
		_Balance += Amount;
		Save();
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _Balance)
		{
			return false;
		}
		else
		{
			_Balance -= Amount;
			Save();
		}
	}
	bool Transfer(double Amount, clsBankClient& Transfer,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		Withdraw(Amount);
		Transfer.Deposit(Amount);
		_RegisterTrangerLog(Amount, Transfer, UserName);
		return true;
	}
	static vector< sTransferLog> GetTransferLogList()
	{
		vector< sTransferLog>vRegisterList;
		fstream FileRegister;
		FileRegister.open("transfarLog.txt", ios::in);
		if (FileRegister.is_open())
		{
			string Line;
			sTransferLog TransferLog;

			while (getline(FileRegister, Line))
			{
				TransferLog = _ConvertTransferLogToLineObject(Line);
				vRegisterList.push_back(TransferLog);
			}
			FileRegister.close();
		}
		return vRegisterList;
	}
};

