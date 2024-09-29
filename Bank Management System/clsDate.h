#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<vector>
#include<string>
#include "clsString.h"
using namespace std;
class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string conDate)
	{
		vector<string>vDate;
		vDate = clsString::Split(conDate, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	static short Days_Number_Month(short month, short year)
	{
		if (month < 1 || month>12) return  0;
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (month == 2) ? (isLeapYear(year) ? 29 : 28) :
			days[month - 1];
	}

	short Days_Number_Month()
	{
		return Days_Number_Month(_Month, _Year);
	}
	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}
	static clsDate dateFromday(short dateOrderyear, short year)
	{
		clsDate Date;
		short Days = dateOrderyear;
		short monthDays = 0;
		Date._Month = 1;
		Date._Year = year;
		while (true)
		{
			monthDays = Days_Number_Month(Date._Month, year);
			if (Days > monthDays)
			{
				Days -= monthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = Days;
				break;
			}
		}
		return Date;
	}
	clsDate(short dateOrderyear, short year)
	{
		clsDate Date1 = dateFromday(dateOrderyear, year);
		_Day = Date1._Day;
		_Month = Date1._Month;
		_Year = Date1._Year;

	}
	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;
	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;
	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" +
			to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}
	void Print()
	{
		cout << DateToString();
	}
	static short Days_Number_Year(short year)
	{
		return isLeapYear(year) ? 365 : 364;
	}
	short Days_Number_Year()
	{
		return Days_Number_Year(_Year);
	}
	static short Hours_Number_Year(short year)
	{
		return Days_Number_Year(year) * 24;
	}
	short Hours_Number_Year()
	{
		return Hours_Number_Year(_Year);
	}
	static short Minutes_Number_Year(short year)
	{
		return Hours_Number_Year(year) * 60;
	}
	short Minutes_Number_Year()
	{
		return Minutes_Number_Year(_Year);
	}
	static int Second_Number_Year(short year)
	{
		return Minutes_Number_Year(year) * 60;
	}
	int Second_Number_Year()
	{
		return Second_Number_Year(_Year);
	}
	static bool isValid_Date(clsDate Date)
	{
		if (Date.Day < 1 || Date.Day>31)
			return false;
		if (Date.Month < 1 || Date.Month>12)
			return false;
		if (Date.Month == 2)
		{
			if (isLeapYear(Date.Year))
			{
				if (Date.Day > 29 || Date.Day > 28)
					return false;
			}
		}
		short daysInmonth = Days_Number_Month(Date.Month, Date.Year);
		if (Date.Day > daysInmonth)
			return false;

		return true;
	}
	bool isValid()
	{
		return isValid_Date(*this);
	}
	static short DayInWeek(short day, short month, short year)
	{
		short d, m, y;
		d = (14 - month) / 12;
		m = month + (d * 12) - 2;
		y = year - d;
		return (day + y + (y / 4) - (y / 100)
			+ (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayInWeek()
	{
		return DayInWeek(_Day, _Month, _Year);
	}
	static string Day_Name(short DayInWeek)
	{
		string arrDayNames[] =
		{ "Sat","Sun","Mon","Tue","Wed","Thu","Fri" };
		return arrDayNames[DayInWeek];
	}
	string Day_Name()
	{
		string arrDayNames[] =
		{ "Sat","Sun","Mon","Tue","Wed","Thu","Fri" };
		return arrDayNames[DayInWeek(_Year, _Month, _Day)];
	}
	static string MonthName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
						   "Apr", "May", "Jun",
						   "Jul", "Aug", "Sep",
						   "Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);

	}
	string MonthName()
	{
		return MonthName(_Month);
	}
	static void Month_Calendar(short Month, short Year)
	{
		int NumberOfDays;
		int current = DayInWeek(1, Month, Year);

		NumberOfDays = Days_Number_Month(Month, Year);
		printf("\n  _______________%s_______________\n\n",
			MonthName(Month).c_str());

		printf("  Sat Sun  Mon  Tue  Wed  Thu   Fri \n");
		int i;

		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");

	}

	void Month_Calendar()
	{
		Month_Calendar(_Month, _Year);
	}
	static void Year_Calendar(short year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			Month_Calendar(i, year);
		}
		return;
	}
	void Year_Calendar()
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", _Year);
		printf("  _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			Month_Calendar(i, _Year);
		}
		return;
	}
	static string GetSystemDateTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		short Hour, Minute, Second;
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;
		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " +
			to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second) + ":");
	}
};


