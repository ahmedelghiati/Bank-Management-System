#pragma once
#include<iostream>
#include<string>
using namespace std;
class clsUtil
{
public:
	enum enCharType
	{
		enSmallLetter=1,enCapitalLetter=2,enDigit=3,
		enMixChars=4,enSpecialChar=5
	};
	static void Srand()
	{
		srand(time(0));
	}
	static int RandomNumber(int From, int To)
	{
		int RandomNum = rand() % (To - From + 1) + From;
		return RandomNum;
	}
	static char RandomChar(enCharType CharType)
	{
		if (CharType == enMixChars)
		{
			CharType == (enCharType)RandomNumber(1, 3);
		}
		switch (CharType)
		{
		case enSmallLetter:
		{
			return RandomNumber(97, 122);
			break;
		}
		case enCapitalLetter:
		{
			return RandomNumber(97, 122);
			break;
		}
		case enDigit:
		{
			return RandomNumber(48, 57);
			break;
		}
		case enSpecialChar:
		{
			return RandomNumber(33, 47);
			break;
		}
		default:
		{
			return RandomNumber(65, 90);
			break;
		}
		}
	}
	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word;
		for (int i = 0; i <= Length; i++)
		{
			Word += RandomChar(CharType);
		}
		return Word;
	}
	static string GenerateKey(enCharType CharType = enCapitalLetter)
	{
		string Key = "";
		Key += GenerateWord(CharType, 4) + "_";
		Key += GenerateWord(CharType, 4) + "_";
		Key += GenerateWord(CharType, 4) + "_";
		Key += GenerateWord(CharType, 4);
		return Key;
	}
	static void GenerateKeys(short Keys , enCharType CharType)
	{
		for (int i = 1; i <= Keys; i++)
		{
			cout << "Key [" << i << "] :";
			cout << GenerateKey(CharType) << endl;
		}
	}
	static void RandomArrayNums(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i <= arrLength; i++)
		{
			arr[i] = RandomNumber(From, To);
		}
	}
	static void RandomArrayWord(string arr[100], int arrLength, int WordLength, enCharType CharType)
	{
		for (int i = 0; i <= arrLength; i++)
		{
			arr[i] = GenerateWord(CharType, WordLength);
		}
	}
	static void RandomArrayKeys(string arr[100], int arrLength,  enCharType CharType)
	{
		for (int i = 0; i <= arrLength; i++)
		{
			arr[i] = GenerateKey(CharType);
		}
	}
	static void Swap(int& A, int& B)
	{
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B)
	{
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(bool& A, bool& B)
	{
		bool Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(char& A, char& B)
	{
		char Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string & A, string& B)
	{
		string Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static  void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}
	static  void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}
	static string  Tabs(short NumberOfTabs)
	{
		string Tab = "";
		for (int i = 0; i < NumberOfTabs; i++)
		{
			Tab += "\t";
			cout << Tab ;
		}
		return Tab;
	}
	static string  EncryptText(string Text, short EncryptionKey=2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}
	static string  DecryptText(string Text, short EncryptionKey=2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}
	static string NumToTxt(int Number)
	{
		if (Number == 0)
		{
			return "";
		}
		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "","One","Two","Three","Four","Five"
				,"Six","Seven", "Eight","Nine","Ten","Eleven","Twelve",
				"Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen",
				"Eighteen","Nineteen" };
			return arr[Number] + " ";
		}
		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty",
				"Sixty","Seventy","Eighty","Ninety" };
			return arr[Number / 10] + " " + NumToTxt(Number % 10);
		}
		if (Number >= 100 && Number <= 999)
		{
			return NumToTxt(Number / 100) + " Hundreds "
				+ NumToTxt(Number % 100);
		}
		if (Number >= 1000 && Number <= 999999)
		{
			return NumToTxt(Number / 1000) + " Thousands "
				+ NumToTxt(Number % 1000);
		}
		if (Number >= 1000000 && Number <= 999999999)
		{
			return NumToTxt(Number / 1000000) + " Millions "
				+ NumToTxt(Number % 1000000);
		}
		else
		{
			return NumToTxt(Number / 1000000) + " Billions "
				+ NumToTxt(Number % 1000000);
		}
	}
};

