#include"allroles.h"
#ifndef _COURSE_H_
#define _COURSE_H_

void courseMenu()
{
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Create academic year and semester" << endl;
	cout << "\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 1 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("Your choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Create academic year and semester" << endl;
		cout << "\tEnter  your choice: ";
		cin >> choose;
	}
	ClearPrintDelay();
	switch (choose)
	{
	case 0:
		break;
	case 1:

		break;
	}
}
#endif 
