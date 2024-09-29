#pragma once
#include <iostream>
using namespace std;
class clsPerson
{
private:
    string _PhoneNumber;
    string _FirstName;
    string _LastName;
    string _Email;

public:
    clsPerson(string fName, string  lName, string email, string pNumber)
    {
        _FirstName = fName;
        _LastName = lName;
        _PhoneNumber = pNumber;
        _Email = email;
    }
    void setfirstName(string fName)
    {
        _FirstName = fName;
    }
    string getfirstName()
    {
        return _FirstName;
    }
    __declspec(property(get = getfirstName, put = setfirstName))string FirstName;
    void setLastName(string  lName)
    {
        _LastName = lName;
    }
    string getlastName()
    {
        return _LastName;
    }
    __declspec(property(get = getlastName, put = setLastName)) string LastName
        ;
    void setphoneNumber(string pNumber)
    {
        _PhoneNumber = pNumber;
    }
    string getphoneNumber()
    {
        return _PhoneNumber;
    }
    __declspec(property(get = getphoneNumber, put = setphoneNumber))string PhoneNumber;
    void setEmail(string email)
    {
        _Email = email;
    }
    string getEmail()
    {
        return _Email;
    }
    __declspec(property(get = getEmail, put = setEmail))string Email;
    string getFullName()
    {
        return (_FirstName + " " + _LastName);
    }
};