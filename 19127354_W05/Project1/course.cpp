#include"allroles.h"
#ifndef _COURSE_H_
#define _COURSE_H_

struct Semester {
	string name;
	string year;
	string className;
	string csvPath;
};

bool validateYear(string year) {
	if (year[4] != '-') {
		return false;
	}
	for (int i = 0; i < year.length(); i++) {
		if (i == 4) {
			continue;
		}
		if (year[i] > 57 || year[i] < 48) {
			return false;
		}
	}
	bool condition = year.length() == 9 && year[4] == '-' && year[0] != '0' && year[5] != '0';
	return condition;
}

void createYearSemester() {
	ClearPrintDelay();
	string year;
	string semester;
	int choose;
	cout << "Enter year(YYYY-YYYY): ";
	cin >> year;
	cout << "Choose semester: \n";
	cout << "1. Hoc ki 1" << endl;
	cout << "2. Hoc ki 2" << endl;
	cout << "3. Hoc ki 3" << endl;
	cout << "\nYour choice: ";
	cin >> choose;
	while (choose < 1 || choose > 3 || cin.fail() || !validateYear(year))
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		if (!validateYear(year)) {
			cout << "Enter year(YYYY-YYYY): ";
			cin >> year;
		}
		else {
			cout << "Enter year(YYYY-YYYY): " << year << endl;
		}
		cout << "Choose semester: \n";
		cout << "1. Hoc ki 1" << endl;
		cout << "2. Hoc ki 2" << endl;
		cout << "3. Hoc ki 3" << endl;
		cout << "\nYour choice: ";
		cin >> choose;
	}
	switch (choose)
	{
	case 1:
		semester = "HK1";
		break;
	case 2:
		semester = "HK2";
		break;
	case 3:
		semester = "HK3";
		break;
	}

	ifstream semFileIn("../../Semester.txt");
	if (semFileIn.is_open()) {
		int numberOfSem;
		ofstream semFileOut("../../Semester.txt", ios::app);
		semFileIn >> numberOfSem;
	}
	else {
		ofstream semFileOut("../../Semester.txt");
		semFileOut << "1\n";
		semFileOut << year + "\n";
		semFileOut << semester + "\n";
	}
 }

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
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Create academic year and semester" << endl;
		cout << "\tEnter  your choice: ";
		cin >> choose;
	}
	switch (choose)
	{
	case 0:
		break;
	case 1:
		createYearSemester();
		break;
	}
}
#endif 
