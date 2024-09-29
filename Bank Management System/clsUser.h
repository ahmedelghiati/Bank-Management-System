#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include"clsPerson.h";
#include"clsString.h";
#include"clsDate.h";
#include"clsUtil.h";
#include <iomanip>
using namespace std;
class clsUser:public clsPerson
{
private:
	enum _enMode { enEmptyMode = 0, enUpdateMode = 1, enAddMode = 2 };
	_enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDeleted = false;
    string _PrepareLogin(string Seperator = "#//#")
    {
        string Login = "";
        Login += clsDate::GetSystemDateTime() + Seperator;
        Login += UserName + Seperator;
        Login += clsUtil::EncryptText(Password)+Seperator;
        Login += to_string(Permissions);
        return Login;
    }
    string _TransferLog(string Seperator = "#//#")
    {
        string Login = "";
        Login += clsDate::GetSystemDateTime() + Seperator;
        Login += UserName + Seperator;
        Login += Password + Seperator;
        Login += to_string(Permissions);
        return Login;
    }
    struct sLoginregister;
    static sLoginregister _ConvertLinetoRegisterObject(string Line, string Seperator = "#//#")
    {
        vector<string> vLoginregister = clsString::Split(Line, Seperator);
        sLoginregister LoginregisterLine;
        LoginregisterLine.DateTime = vLoginregister[0];
        LoginregisterLine.UserName = vLoginregister[1];
        LoginregisterLine.Password = clsUtil::DecryptText(vLoginregister[2]);
        LoginregisterLine.Permissions = stoi(vLoginregister[3]);
        return LoginregisterLine;
    }
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        return clsUser(_enMode::enUpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }
    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.PhoneNumber + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord +=clsUtil:: EncryptText(User.Password)+ Seperator;
        UserRecord += to_string(User.Permissions);
        return UserRecord;
    }
    static  vector <clsUser> _LoadUsersDataFromFile()
    {
        vector <clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);

        string DataLine;

        if (MyFile.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(_enMode::enEmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32,pLogin=64, pManageUsers = 128
    };
    struct sLoginregister
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };
    clsUser(_enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }
    bool IsEmpty()
    {
        return (_Mode == _enMode::enEmptyMode);
    }
    bool MarkedForDeleted()
    {
        return _MarkedForDeleted;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName))string UserName;
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;
    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
enum enSaveResults { svFaildEmpty = 0, svSuccessed = 1, svFaildUsedUser = 2 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enEmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmpty;
			}

		}

		case enUpdateMode:
		{
			_Update();
			return enSaveResults::svSuccessed;
			break;
		}

		case enAddMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUsedUser;
			}
			else
			{
				_AddNew();
				_Mode = enUpdateMode;
				return enSaveResults::svSuccessed;
			}

			break;
		}
		}

	}
    static bool IsUserExist(string UserName)
    {
        clsUser User = Find(UserName);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDeleted = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(_enMode::enAddMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }
    bool CheckAccessPermissions(enPermissions Permissions)
    {
        if (this->Permissions == enPermissions::eAll)
        {
            return true;
        }
        if ((this->Permissions & Permissions) == Permissions)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void RegisterLogIn()
    {
        string DateLine = _PrepareLogin();

        fstream FileRegister;
        FileRegister.open("LoginRegister.txt", ios::out | ios::app);
        if (FileRegister.is_open())
        {
            FileRegister << DateLine<< endl;
            FileRegister.close();
        }
    }
    static vector< sLoginregister> GetRegisterLogInList()
    {
        vector< sLoginregister>vRegisterList;
        fstream FileRegister;
        FileRegister.open("LoginRegister.txt", ios::in);
        if (FileRegister.is_open())
        {
            string Line;
            sLoginregister LoginList;
            
            while (getline(FileRegister,Line))
            {
                LoginList = _ConvertLinetoRegisterObject(Line);

                vRegisterList.push_back(LoginList);
            }
            FileRegister.close();
        }
        return vRegisterList;
    }
};

