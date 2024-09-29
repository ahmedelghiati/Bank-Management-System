#pragma once
#include<iostream>
#include<string>
using namespace std;
class clsInputValidate
{
public:
	static bool IsNumberBetween(int Num, int From, int To)
	{
		if (Num >= From && Num <= To)
		{
			return true;
		}
		else
		   return false;
	}
	static bool IsNumberBetween(short Num, short From, short To)
	{
		if (Num >= From && Num <= To)
		{
			return true;
		}
		else
			return false;
	}
	static bool IsNumberBetween(double Num, double From, double To)
	{
		if (Num >= From && Num <= To)
		{
			return true;
		}
		else
			return false;
	}
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static int ReadIntNumBetween(int From, int To, string ErrorMessage
		= "Number is not within range, Enter again:\n")
	{
		int Num = ReadIntNumber();
		if (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage;
			Num = ReadIntNumber();
		}
		return Num;
	}

	static double ReadDoubleNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDoubleNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDoubleNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDoubleNumber();
		}
		return Number;
	}
	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

};

