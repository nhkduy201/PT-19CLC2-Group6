#include"allroles.h"
#ifndef _COURSE_H_
#define _COURSE_H_

bool isValidYear(string year) {
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

bool isSemesterExist(string yearIn, int choose) {
	string semesterIn;
	switch (choose)
	{
	case 1:
		semesterIn = "HK1";
		break;
	case 2:
		semesterIn = "HK2";
		break;
	case 3:
		semesterIn = "HK3";
		break;
	}
	ifstream semFileIn("../../Semester.txt");
	if (!semFileIn.is_open()) {
		return false;
	}else {
		int numberOfSem;
		semFileIn >> numberOfSem;
		semFileIn.ignore();
		string existYear;
		string existSem;
		for (int i = 0; i < numberOfSem; i++) {
			getline(semFileIn, existYear);
			getline(semFileIn, existSem);
			if (yearIn == existYear && semesterIn == existSem) {
				return true;
			}
		}
		return false;
	}
}

void createYearSemester() {
	ClearPrintDelay();
	string year;
	string semester;
	int choose;
	cout << "\n\tEnter academic year(YYYY-YYYY): ";
	cin >> year;
	cout << "\tChoose semester:" << endl;
	cout << "\t1. Hoc ki 1" << endl;
	cout << "\t2. Hoc ki 2" << endl;
	cout << "\t3. Hoc ki 3" << endl;
	cout << "\n\tYour choice: ";
	cin >> choose;
	while (choose < 1 || choose > 3 || cin.fail() || !isValidYear(year) || isSemesterExist(year, choose))
	{
		cin.clear();
		cin.ignore(32767, '\n');
		string err = "";
		if (!isValidYear(year)) {
			err += "\n\tThe academic year you type is illegal!";
		}
		else if (isSemesterExist(year, choose)) {
			err += "\n\tThe academic year and semester you type have been existed!";
		}
		if (choose < 1 || choose > 3 || cin.fail()) {
			err += "\n\tYour choice is illegal!";
		}
		if (err.length()) {
			ClearPrintDelay(err);
		}
		if (!isValidYear(year) || isSemesterExist(year, choose)) {
			cout << "\n\tEnter academic year(YYYY-YYYY): ";
			cin >> year;
		}
		else {
			cout << "\n\tEnter academic year(YYYY-YYYY): " << year << endl;
		}
		cout << "\tChoose semester:" << endl;
		cout << "\t1. Hoc ki 1" << endl;
		cout << "\t2. Hoc ki 2" << endl;
		cout << "\t3. Hoc ki 3" << endl;
		cout << "\n\tYour choice: ";
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
		semFileIn >> numberOfSem;
		semFileIn.ignore();
		string tmp, remain = "";
		while (!semFileIn.eof()) {
			getline(semFileIn, tmp);
			remain += (tmp + "\n");
		}
		ofstream semFileOut("../../Semester.txt");
		semFileOut << ++numberOfSem << endl;
		semFileOut << remain;
		semFileOut << year << endl;
		semFileOut << semester;
	}
	else {
		ofstream semFileOut("../../Semester.txt");
		semFileOut << "1\n";
		semFileOut << year + "\n";
		semFileOut << semester;
	}
 }

void standardPathFile(string &path) {
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\') {
			path[i] = '/';
		}
	}
}

void importSchedule() {
	ClearPrintDelay();
	Semester sem;
	int choose;
	cout << "\n\tEnter academic year(YYYY-YYYY): ";
	cin >> sem.year;
	cout << "\tEnter class ID: ";
	cin >> sem.classID;
	cout << "\tEnter csv file path: ";
	cin >> sem.csvPath;
	cout << "\tChoose semester:" << endl;
	cout << "\t1. Hoc ki 1" << endl;
	cout << "\t2. Hoc ki 2" << endl;
	cout << "\t3. Hoc ki 3" << endl;
	cout << "\n\tYour choice: ";
	cin >> choose;
	while (choose < 1 || choose > 3 || cin.fail() || !isValidYear(sem.year) || !isSemesterExist(sem.year, choose))
	{
		cin.clear();
		cin.ignore(32767, '\n');
		string err = "";
		if (!isValidYear(sem.year)) {
			err += "\n\tThe academic year you type is illegal!";
		}
		else if (!isSemesterExist(sem.year, choose)) {
			err += "\n\tThe academic year and semester you type have not been existed!\n\tCreate before import!";
		}
		if (choose < 1 || choose > 3 || cin.fail()) {
			err += "\n\tYour choice is illegal!";
		}
		if (err.length()) {
			ClearPrintDelay(err);
			if (!isSemesterExist(sem.year, choose)) {
				return;
			}
		}
		if (!isValidYear(sem.year) || isSemesterExist(sem.year, choose)) {
			cout << "\n\tEnter academic year(YYYY-YYYY): ";
			cin >> sem.year;
		}
		else {
			cout << "\n\tEnter academic year(YYYY-YYYY): " << sem.year << endl;
		}
		cout << "\tEnter class ID: ";
		cin >> sem.classID;
		cout << "\tEnter csv file path: ";
		cin >> sem.csvPath;
		cout << "\tChoose semester:" << endl;
		cout << "\t1. Hoc ki 1" << endl;
		cout << "\t2. Hoc ki 2" << endl;
		cout << "\t3. Hoc ki 3" << endl;
		cout << "\n\tYour choice: ";
		cin >> choose;
	}

	standardPathFile(sem.csvPath);
	switch (choose)
	{
	case 1:
		sem.name = "HK1";
		break;
	case 2:
		sem.name = "HK2";
		break;
	case 3:
		sem.name = "HK3";
		break;
	}

	ifstream fin(sem.csvPath);
	if (!fin.is_open()){
		ClearPrintDelay("\n\tCan't open csv file you enter!");
		return;
	}
	else {
		int count = 0;
		string fisrtline;
		Course* cour;
		string no;
		getline(fin, fisrtline);
		while (fin.good()) {
			getline(fin, no, '\n');
			if (!no.length()) {
				break;
			}
			count++;
		}
		cour = new Course[count];
		fin.close();
		fin.open(sem.csvPath);
		getline(fin, fisrtline);
		for (int i = 0; i < count; i++) {
			getline(fin, no, ',');
			if (!no.length()) {
				break;
			}
			getline(fin, cour[i].courseID, ',');
			getline(fin, cour[i].courseName, ',');
			getline(fin, cour[i].classID, ',');
			getline(fin, cour[i].lecturerUsername, ',');
			getline(fin, cour[i].lecturerName, ',');
			getline(fin, cour[i].degree, ',');
			getline(fin, cour[i].startDate, ',');
			getline(fin, cour[i].endDate, ',');
			getline(fin, cour[i].day, ',');
			getline(fin, cour[i].startHour, ',');
			getline(fin, cour[i].endHour, ',');
			getline(fin, cour[i].startMin, ',');
			getline(fin, cour[i].endMin, ',');
			getline(fin, cour[i].room, '\n');
			cour[i].startDate.erase(5, 1);
			cour[i].startDate.erase(2, 1);
			cour[i].startDate.insert(2, 1, ' ');
			cour[i].startDate.insert(5, 1, ' ');
			cour[i].endDate.erase(5, 1);
			cour[i].endDate.erase(2, 1);
			cour[i].endDate.insert(2, 1, ' ');
			cour[i].endDate.insert(5, 1, ' ');
		}
		ofstream fout;
		fout.open("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
		fout << count << endl;
		for (int i = 0; i < count; i++) {
			fout << cour[i].courseID << endl;
			fout << cour[i].courseName << endl;
			fout << cour[i].classID << endl;
			fout << cour[i].lecturerUsername << endl;
			fout << cour[i].lecturerName << endl;
			fout << cour[i].degree << endl;
			fout << cour[i].startDate << endl;
			fout << cour[i].endDate << endl;
			fout << cour[i].day << endl;
			fout << cour[i].startHour << " " << cour[i].endHour << endl;
			fout << cour[i].startMin << " " << cour[i].endMin << endl;
			fout << cour[i].room << endl;
		}
		fout.close();
	}
	fin.close();
	ClearPrintDelay("\n\tImport successfully!");
}

void courseMenu()
{
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Create academic year and semester" << endl;
	cout << "\t2. Import schedule" << endl;
	cout << "\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 2 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Create academic year and semester" << endl;
		cout << "\t2. Import schedule" << endl;
		cout << "\tEnter  your choice: ";
		cin >> choose;
	}
	switch (choose)
	{
	case 0:
		break;
	case 1:
		createYearSemester();
		courseMenu();
		break;
	case 2:
		importSchedule();
		courseMenu();
		break;
	}
}
#endif 
