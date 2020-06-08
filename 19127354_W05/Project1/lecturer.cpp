#include "allroles.h"
void editScbOfStu(Semester sem) {
	//get course
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	cout << "\n\tEnter courseID: ";
	getline(cin, tmpCourse.courseID);
	ClearPrintDelay();
	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	while (!scheduleFileIn.eof()) {
		getline(scheduleFileIn, tmpCourseID);
		if (tmpCourseID == tmpCourse.courseID) {
			isCourseFound = true;
			getline(scheduleFileIn, tmpCourse.courseName);
			getline(scheduleFileIn, tmpCourse.classID);
			getline(scheduleFileIn, tmpCourse.lecturerUsername);
			getline(scheduleFileIn, tmpCourse.lecturerName);
			getline(scheduleFileIn, tmpCourse.degree);
			scheduleFileIn >> tmpCourse.startDate.day >> tmpCourse.startDate.month >> tmpCourse.startDate.year;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endDate.day >> tmpCourse.endDate.month >> tmpCourse.endDate.year;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpDay);
			if (tmpDay == "0") {
				tmpCourse.day = 0;
			}
			else if (tmpDay == "1") {
				tmpCourse.day = 1;
			}
			else if (tmpDay == "2") {
				tmpCourse.day = 2;
			}
			else if (tmpDay == "3") {
				tmpCourse.day = 3;
			}
			else if (tmpDay == "4") {
				tmpCourse.day = 4;
			}
			else if (tmpDay == "5") {
				tmpCourse.day = 5;
			}
			else if (tmpDay == "6") {
				tmpCourse.day = 6;
			}
			getListOfWeek(tmpCourse.atd, tmpCourse.startDate, tmpCourse.endDate, tmpCourse.day);
			break;
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}

	//get student matched, get top remain, bottom remain
	string top = "", bottom = "", tmpStudentID, tmpLine;
	bool isStudentFound = false;
	int changeScore;
	StudentInCourse tmpStudent;
	cout << "\n\tEnter Student ID: ";
	getline(cin, tmpStudent.std.id);
	ClearPrintDelay();
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	if (!courseFileIn.is_open()) {
		ClearPrintDelay("\n\tCan't open course of class file!");
		return;
	}
	getline(courseFileIn, tmpStudentID);
	top += tmpStudentID;
	while (!courseFileIn.eof()) {
		getline(courseFileIn, tmpStudentID);
		if (tmpStudentID == tmpStudent.std.id) {
			isStudentFound = true;
			getline(courseFileIn, tmpStudent.std.password);
			getline(courseFileIn, tmpStudent.std.name);
			getline(courseFileIn, tmpStudent.std.DoB);
			getline(courseFileIn, tmpStudent.std.classID);
			courseFileIn >> tmpStudent.std.status;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.midterm;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.final;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.bonus;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.total;
			courseFileIn.ignore();
			tmpStudent.listOfCheckIn = new bool[tmpCourse.atd.numberOfWeek];
			for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
				courseFileIn >> tmpStudent.listOfCheckIn[k];
				courseFileIn.ignore();
			}
			courseFileIn >> tmpStudent.statusInCourse;
			courseFileIn.ignore();
			cout << "Enter scores(enter \"-1\" if the score has no change): " << endl;
			cout << "Midterm: ";
			cin >> changeScore;
			if (changeScore != -1) {
				tmpStudent.scb.midterm = changeScore;
			}
			cout << "Final: ";
			cin >> changeScore;
			if (changeScore != -1) {
				tmpStudent.scb.final = changeScore;
			}
			cout << "Bonus: ";
			cin >> changeScore;
			if (changeScore != -1) {
				tmpStudent.scb.bonus = changeScore;
			}
			cout << "Total: ";
			cin >> changeScore;
			if (changeScore != -1) {
				tmpStudent.scb.total = changeScore;
			}

			while (!courseFileIn.eof()) {
				getline(courseFileIn, tmpLine);
				bottom += ("\n" + tmpLine);
			}
			break;
		}
		else {
			top += ("\n" + tmpStudentID);
		}
	}
	courseFileIn.close();
	if (!isStudentFound) {
		ClearPrintDelay("\n\tYour student ID not found!");
		return;
	}

	ofstream courseFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	courseFileOut << top;
	courseFileOut << endl << tmpStudent.std.id;
	courseFileOut << endl << tmpStudent.std.password;
	courseFileOut << endl << tmpStudent.std.name;
	courseFileOut << endl << tmpStudent.std.DoB;
	courseFileOut << endl << tmpStudent.std.classID;
	courseFileOut << endl << tmpStudent.std.status;
	courseFileOut << endl << tmpStudent.scb.midterm;
	courseFileOut << endl << tmpStudent.scb.final;
	courseFileOut << endl << tmpStudent.scb.bonus;
	courseFileOut << endl << tmpStudent.scb.total;
	for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
		courseFileOut << endl << tmpStudent.listOfCheckIn[k];
	}
	courseFileOut << endl << tmpStudent.statusInCourse;
	courseFileOut << bottom;
	courseFileOut.close();
	delete[] tmpStudent.listOfCheckIn;
	delete[] tmpCourse.atd.listOfWeek;
}

void viewScbOfCour(Semester sem) {
	//get course
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	cout << "\n\tEnter courseID: ";
	getline(cin, tmpCourse.courseID);
	ClearPrintDelay();
	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	while (!scheduleFileIn.eof()) {
		getline(scheduleFileIn, tmpCourseID);
		if (tmpCourseID == tmpCourse.courseID) {
			isCourseFound = true;
			getline(scheduleFileIn, tmpCourse.courseName);
			getline(scheduleFileIn, tmpCourse.classID);
			getline(scheduleFileIn, tmpCourse.lecturerUsername);
			getline(scheduleFileIn, tmpCourse.lecturerName);
			getline(scheduleFileIn, tmpCourse.degree);
			scheduleFileIn >> tmpCourse.startDate.day >> tmpCourse.startDate.month >> tmpCourse.startDate.year;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endDate.day >> tmpCourse.endDate.month >> tmpCourse.endDate.year;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpDay);
			if (tmpDay == "0") {
				tmpCourse.day = 0;
			}
			else if (tmpDay == "1") {
				tmpCourse.day = 1;
			}
			else if (tmpDay == "2") {
				tmpCourse.day = 2;
			}
			else if (tmpDay == "3") {
				tmpCourse.day = 3;
			}
			else if (tmpDay == "4") {
				tmpCourse.day = 4;
			}
			else if (tmpDay == "5") {
				tmpCourse.day = 5;
			}
			else if (tmpDay == "6") {
				tmpCourse.day = 6;
			}
			getListOfWeek(tmpCourse.atd, tmpCourse.startDate, tmpCourse.endDate, tmpCourse.day);
			break;
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}

	//get students
	StudentInCourse tmpStudent;
	int numOfStuInCour = 0;
	ClearPrintDelay();
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	if (!courseFileIn.is_open()) {
		ClearPrintDelay("\n\tCan't open course of class file!");
		return;
	}
	courseFileIn >> numOfStuInCour;
	courseFileIn.ignore();
	while (!courseFileIn.eof()) {
		getline(courseFileIn, tmpStudent.std.id);
		getline(courseFileIn, tmpStudent.std.password);
		getline(courseFileIn, tmpStudent.std.name);
		getline(courseFileIn, tmpStudent.std.DoB);
		getline(courseFileIn, tmpStudent.std.classID);
		courseFileIn >> tmpStudent.std.status;
		courseFileIn.ignore();
		courseFileIn >> tmpStudent.scb.midterm;
		courseFileIn.ignore();
		courseFileIn >> tmpStudent.scb.final;
		courseFileIn.ignore();
		courseFileIn >> tmpStudent.scb.bonus;
		courseFileIn.ignore();
		courseFileIn >> tmpStudent.scb.total;
		courseFileIn.ignore();
		tmpStudent.listOfCheckIn = new bool[tmpCourse.atd.numberOfWeek];
		for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
			courseFileIn >> tmpStudent.listOfCheckIn[k];
			courseFileIn.ignore();
		}
		courseFileIn >> tmpStudent.statusInCourse;
		courseFileIn.ignore();
		if (tmpStudent.statusInCourse) {
			cout << "\n\t==================================";
			cout << endl << "\n\t    Student ID: " << tmpStudent.std.id;
			cout << endl << "\t    Student Name: " << tmpStudent.std.name;
			cout << endl << "\t\t------------------";
			cout << endl << "\t    Midterm: " << tmpStudent.scb.midterm;
			cout << endl << "\t    Final: " << tmpStudent.scb.final;
			cout << endl << "\t    Bonus: " << tmpStudent.scb.bonus;
			cout << endl << "\t    Total: " << tmpStudent.scb.total << endl;
		}
	}
	cout << "\n\t==================================\n";
	system("pause");
	courseFileIn.close();
}

void editAtd(Semester sem) {
	//get course
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	cout << "\n\tEnter courseID: ";
	getline(cin, tmpCourse.courseID);
	ClearPrintDelay();
	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	while (!scheduleFileIn.eof()) {
		getline(scheduleFileIn, tmpCourseID);
		if (tmpCourseID == tmpCourse.courseID) {
			isCourseFound = true;
			getline(scheduleFileIn, tmpCourse.courseName);
			getline(scheduleFileIn, tmpCourse.classID);
			getline(scheduleFileIn, tmpCourse.lecturerUsername);
			getline(scheduleFileIn, tmpCourse.lecturerName);
			getline(scheduleFileIn, tmpCourse.degree);
			scheduleFileIn >> tmpCourse.startDate.day >> tmpCourse.startDate.month >> tmpCourse.startDate.year;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endDate.day >> tmpCourse.endDate.month >> tmpCourse.endDate.year;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpDay);
			if (tmpDay == "0") {
				tmpCourse.day = 0;
			}
			else if (tmpDay == "1") {
				tmpCourse.day = 1;
			}
			else if (tmpDay == "2") {
				tmpCourse.day = 2;
			}
			else if (tmpDay == "3") {
				tmpCourse.day = 3;
			}
			else if (tmpDay == "4") {
				tmpCourse.day = 4;
			}
			else if (tmpDay == "5") {
				tmpCourse.day = 5;
			}
			else if (tmpDay == "6") {
				tmpCourse.day = 6;
			}
			getListOfWeek(tmpCourse.atd, tmpCourse.startDate, tmpCourse.endDate, tmpCourse.day);
			break;
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}

	//get student matched, get top remain, bottom remain
	string top = "", bottom = "", tmpStudentID, tmpLine;
	bool isStudentFound = false;
	int changeWeek;
	StudentInCourse tmpStudent;
	cout << "\n\tEnter Student ID: ";
	getline(cin, tmpStudent.std.id);
	ClearPrintDelay();
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	if (!courseFileIn.is_open()) {
		ClearPrintDelay("\n\tCan't open course of class file!");
		return;
	}
	getline(courseFileIn, tmpStudentID);
	top += tmpStudentID;
	while (!courseFileIn.eof()) {
		getline(courseFileIn, tmpStudentID);
		if (tmpStudentID == tmpStudent.std.id) {
			isStudentFound = true;
			getline(courseFileIn, tmpStudent.std.password);
			getline(courseFileIn, tmpStudent.std.name);
			getline(courseFileIn, tmpStudent.std.DoB);
			getline(courseFileIn, tmpStudent.std.classID);
			courseFileIn >> tmpStudent.std.status;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.midterm;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.final;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.bonus;
			courseFileIn.ignore();
			courseFileIn >> tmpStudent.scb.total;
			courseFileIn.ignore();
			tmpStudent.listOfCheckIn = new bool[tmpCourse.atd.numberOfWeek];
			for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
				courseFileIn >> tmpStudent.listOfCheckIn[k];
				courseFileIn.ignore();
			}
			courseFileIn >> tmpStudent.statusInCourse;
			courseFileIn.ignore();
			cout << "Enter weeks(enter \"0\" to exit): " << endl;
			do {
				cout << "Week: ";
				cin >> changeWeek;
				if (changeWeek < 0 || changeWeek > tmpCourse.atd.numberOfWeek) {
					cout << "The week is illegal. Try again!" << endl;
				}
				else {
					if (changeWeek) {
						tmpStudent.listOfCheckIn[changeWeek - 1] = !tmpStudent.listOfCheckIn[changeWeek - 1];
					}
				}
			} while (changeWeek);

			while (!courseFileIn.eof()) {
				getline(courseFileIn, tmpLine);
				bottom += ("\n" + tmpLine);
			}
			break;
		}
		else {
			top += ("\n" + tmpStudentID);
		}
	}
	courseFileIn.close();
	if (!isStudentFound) {
		ClearPrintDelay("\n\tYour student ID not found!");
		return;
	}

	ofstream courseFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	courseFileOut << top;
	courseFileOut << endl << tmpStudent.std.id;
	courseFileOut << endl << tmpStudent.std.password;
	courseFileOut << endl << tmpStudent.std.name;
	courseFileOut << endl << tmpStudent.std.DoB;
	courseFileOut << endl << tmpStudent.std.classID;
	courseFileOut << endl << tmpStudent.std.status;
	courseFileOut << endl << tmpStudent.scb.midterm;
	courseFileOut << endl << tmpStudent.scb.final;
	courseFileOut << endl << tmpStudent.scb.bonus;
	courseFileOut << endl << tmpStudent.scb.total;
	for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
		courseFileOut << endl << tmpStudent.listOfCheckIn[k];
	}
	courseFileOut << endl << tmpStudent.statusInCourse;
	courseFileOut << bottom;
	courseFileOut.close();
	delete[] tmpStudent.listOfCheckIn;
	delete[] tmpCourse.atd.listOfWeek;
}

void importScoreboard(Semester sem) {
	// get course
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	cout << "\n\tEnter courseID: ";
	getline(cin, tmpCourse.courseID);
	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	while (!scheduleFileIn.eof()) {
		getline(scheduleFileIn, tmpCourseID);
		if (tmpCourseID == tmpCourse.courseID) {
			isCourseFound = true;
			getline(scheduleFileIn, tmpCourse.courseName);
			getline(scheduleFileIn, tmpCourse.classID);
			getline(scheduleFileIn, tmpCourse.lecturerUsername);
			getline(scheduleFileIn, tmpCourse.lecturerName);
			getline(scheduleFileIn, tmpCourse.degree);
			scheduleFileIn >> tmpCourse.startDate.day >> tmpCourse.startDate.month >> tmpCourse.startDate.year;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endDate.day >> tmpCourse.endDate.month >> tmpCourse.endDate.year;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpDay);
			if (tmpDay == "0") {
				tmpCourse.day = 0;
			}
			else if (tmpDay == "1") {
				tmpCourse.day = 1;
			}
			else if (tmpDay == "2") {
				tmpCourse.day = 2;
			}
			else if (tmpDay == "3") {
				tmpCourse.day = 3;
			}
			else if (tmpDay == "4") {
				tmpCourse.day = 4;
			}
			else if (tmpDay == "5") {
				tmpCourse.day = 5;
			}
			else if (tmpDay == "6") {
				tmpCourse.day = 6;
			}
			getListOfWeek(tmpCourse.atd, tmpCourse.startDate, tmpCourse.endDate, tmpCourse.day);
			break;
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}
	//get student scoreboard from csv file
	string csvPath;
	cout << "\tEnter csv file path: ";
	cin >> csvPath;
	standardPathFile(csvPath);
	ifstream fin(csvPath);
	StudentInCourse* stuInFile;
	if (!fin.is_open()) {
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
		stuInFile = new StudentInCourse[count];
		fin.close();
		fin.open(csvPath);
		getline(fin, fisrtline);
		for (int i = 0; i < count; i++) {
			getline(fin, no, ',');
			if (!no.length()) {
				break;
			}
			getline(fin, stuInFile[i].std.id, ',');
			getline(fin, stuInFile[i].std.name, ',');
			fin >> stuInFile[i].scb.midterm;
			fin.ignore();
			fin >> stuInFile[i].scb.final;
			fin.ignore();
			fin >> stuInFile[i].scb.bonus;
			fin.ignore();
			fin >> stuInFile[i].scb.total;
			fin.ignore();
		}
		//get student in db
		double tmpScore;
		ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
		if (!courseFileIn.is_open()) {
			ClearPrintDelay("\n\tCan't open course of class file!");
			return;
		}
		int numStuInCourse = 0;
		courseFileIn >> numStuInCourse;
		if (count != numStuInCourse) {
			ClearPrintDelay("\n\tImport file and file in database not matched!");
			return;
		}
		courseFileIn.ignore();
		string name, id;
		for (int i = 0; i < count; i++) {
			getline(courseFileIn, id);
			getline(courseFileIn, stuInFile[i].std.password);
			getline(courseFileIn, name);
			if (stuInFile[i].std.id != id || stuInFile[i].std.name != name) {
				ClearPrintDelay("\n\tImport file and file in database not matched!");
				return;
			}
			getline(courseFileIn, stuInFile[i].std.DoB);
			getline(courseFileIn, stuInFile[i].std.classID);
			courseFileIn >> stuInFile[i].std.status;
			courseFileIn.ignore();
			courseFileIn >> tmpScore;
			courseFileIn.ignore();
			courseFileIn >> tmpScore;
			courseFileIn.ignore();
			courseFileIn >> tmpScore;
			courseFileIn.ignore();
			courseFileIn >> tmpScore;
			courseFileIn.ignore();
			stuInFile[i].listOfCheckIn = new bool[tmpCourse.atd.numberOfWeek];
			for (int j = 0; j < tmpCourse.atd.numberOfWeek; j++) {
				courseFileIn >> stuInFile[i].listOfCheckIn[j];
				courseFileIn.ignore();
			}
			courseFileIn >> stuInFile[i].statusInCourse;
			courseFileIn.ignore();
		}
		courseFileIn.close();
		// write to db again
		ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
		courseFile << numStuInCourse;
		for (int j = 0; j < numStuInCourse; j++) {
			courseFile << endl << stuInFile[j].std.id;
			courseFile << endl << stuInFile[j].std.password;
			courseFile << endl << stuInFile[j].std.name;
			courseFile << endl << stuInFile[j].std.DoB;
			courseFile << endl << stuInFile[j].std.classID;
			courseFile << endl << stuInFile[j].std.status;
			courseFile << endl << stuInFile[j].scb.midterm;
			courseFile << endl << stuInFile[j].scb.final;
			courseFile << endl << stuInFile[j].scb.bonus;
			courseFile << endl << stuInFile[j].scb.total;
			for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
				courseFile << endl << stuInFile[j].listOfCheckIn[k];
			}
			courseFile << endl << stuInFile[j].statusInCourse;
		}
		for (int j = 0; j < numStuInCourse; j++) {
			delete[] stuInFile[j].listOfCheckIn;
		}
		delete[] stuInFile;
		courseFile.close();
	}
	fin.close();
	ClearPrintDelay("\n\tImport successfully!");
}

void lecturerMenu() {
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Import scoreboard of a course" << endl;
	cout << "\t2. View all course of Semester" << endl;
	cout << "\t3. View list of student in a course" << endl;
	cout << "\t4. View attendance list of a course" << endl;
	cout << "\t5. View scoreboard of course" << endl;
	cout << "\t6. Edit an attendance of a student in a course" << endl;
	cout << "\t7. Edit a scoreboard of a student in a course" << endl;
	cout << "\n\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 7 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Import scoreboard of a course" << endl;
		cout << "\t2. View all course of Semester" << endl;
		cout << "\t3. View list of student in a course" << endl;
		cout << "\t4. View attendance list of a course" << endl;
		cout << "\t5. View scoreboard of course" << endl;
		cout << "\t6. Edit an attendance of a student in a course" << endl;
		cout << "\t7. Edit a scoreboard of a student in a course" << endl;
		cout << "\n\tEnter  your choice: ";
		cin >> choose;
	}

	ClearPrintDelay();
	switch (choose)
	{
	case 0:
		break;
	case 2:
		{
		Semester sem;
		int choose;
		// get semester
		cout << "\n\tEnter academic year(YYYY-YYYY): ";
		cin >> sem.year;
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
				err += "\n\n\tThe academic year you type is illegal!";
			}
			else if (choose < 1 || choose > 3 || cin.fail()) {
				err += "\n\n\tYour choice is illegal!";
			}
			else if (!isSemesterExist(sem.year, choose)) {
				err += "\n\n\tThe academic year and semester you type have not been existed!\n\tCreate before import!";
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
			sem.name = "HK1";
			break;
		case 2:
			sem.name = "HK2";
			break;
		case 3:
			sem.name = "HK3";
			break;
		}
		viewListOfCourses(sem);
		lecturerMenu();
		break;
		}
		break;

	case 1:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	{
		Semester sem;
		int anotherChoose;
		// get semester
		cout << "\n\tEnter academic year(YYYY-YYYY): ";
		cin >> sem.year;
		cout << "\tEnter class ID: ";
		cin >> sem.classID;
		cout << "\tChoose semester:" << endl;
		cout << "\t1. Hoc ki 1" << endl;
		cout << "\t2. Hoc ki 2" << endl;
		cout << "\t3. Hoc ki 3" << endl;
		cout << "\n\tYour choice: ";
		cin >> anotherChoose;
		while (anotherChoose < 1 || anotherChoose > 3 || cin.fail() || !isValidYear(sem.year) || !isSemesterExist(sem.year, anotherChoose) || !isValidClass(sem.classID))
		{
			cin.clear();
			cin.ignore(32767, '\n');

			string err = "";

			if (!isValidYear(sem.year)) {
				err += "\n\n\tThe academic year you type is illegal!";
			}
			else if (anotherChoose < 1 || anotherChoose > 3 || cin.fail()) {
				err += "\n\n\tYour choice is illegal!";
			}
			else if (!isSemesterExist(sem.year, anotherChoose)) {
				err += "\n\n\tThe academic year and semester you type have not been existed!\n\tCreate before import!";
			}

			if (!isValidClass(sem.classID)) {
				err += "\n\n\tThe classID you enter not found!";
			}

			if (err.length()) {
				ClearPrintDelay(err);
				if (!isSemesterExist(sem.year, anotherChoose)) {
					return;
				}
			}

			if (!isValidYear(sem.year) || isSemesterExist(sem.year, anotherChoose)) {
				cout << "\n\tEnter academic year(YYYY-YYYY): ";
				cin >> sem.year;
			}
			else {
				cout << "\n\tEnter academic year(YYYY-YYYY): " << sem.year << endl;
			}

			cout << "\tEnter class ID: ";
			cin >> sem.classID;
			cout << "\tChoose semester:" << endl;
			cout << "\t1. Hoc ki 1" << endl;
			cout << "\t2. Hoc ki 2" << endl;
			cout << "\t3. Hoc ki 3" << endl;
			cout << "\n\tYour choice: ";
			cin >> anotherChoose;
		}
		cin.ignore();
		ClearPrintDelay();
		switch (anotherChoose)
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
		if (choose == 3)
		{
			viewListOfStuInCour(sem);
		}
		else if (choose == 4) {
			viewAtdListOfCour(sem);
		}
		else if (choose == 1) {
			importScoreboard(sem);
		}
		else if (choose == 5) {
			viewScbOfCour(sem);
		}
		else if (choose == 6) {
			editAtd(sem);
		}
		else if (choose == 7) {
			editScbOfStu(sem);
		}
		lecturerMenu();
		break;
	}
	}

}