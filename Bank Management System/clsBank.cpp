#include "clsLoginScreen.h"
#include<iostream>
using namespace std;
int main()
{
	while(true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			 break;
		}
	}
	return 0;
}