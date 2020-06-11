#include"allroles.h"

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
			err += "\n\n\tThe academic year you type is illegal!";
		}
		else if (isSemesterExist(year, choose)) {
			err += "\n\n\tThe academic year and semester you type have been existed!";
		}
		if (choose < 1 || choose > 3 || cin.fail()) {
			err += "\n\n\tYour choice is illegal!";
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
	ClearPrintDelay("\n\tCreate successfully!");
 }

void standardPathFile(string &path) {
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\') {
			path[i] = '/';
		}
	}
}

void getDayOfWeek(Date& date) {
	int numberOfDay = 0;
	int daysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//string dayOfWeek[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" , "Sunday" };
	for (int i = 1970; i < date.year; i++) {
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
			numberOfDay += 366;
		}
		else {
			numberOfDay += 365;
		}
	}
	if (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0)) {
		daysOfMonth[1] = 29;
	}
	for (int i = 0; i < date.month - 1; i++) {
		numberOfDay += daysOfMonth[i];
	}
	numberOfDay += date.day;
	date.dayFromTheOrigin = numberOfDay;
	numberOfDay = (numberOfDay % 7 + 2) % 7;
	date.DOW = numberOfDay;
}

void getDate(Date& date, int dayFromTheOrigin) {
	int countYear = 1970;
	int dayOfYear;
	int daysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//string dayOfWeek[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" , "Sunday" };
	while (true) {
		if (((countYear % 4 == 0) && (countYear % 100 != 0)) || (countYear % 400 == 0)) {
			dayOfYear = 366;
		}
		else {
			dayOfYear = 365;
		}
		if (dayFromTheOrigin <= dayOfYear) {
			break;
		}
		else {
			dayFromTheOrigin -= dayOfYear;
		}
		countYear++;
	}
	date.year = countYear;
	if (((countYear % 4 == 0) && (countYear % 100 != 0)) || (countYear % 400 == 0)) {
		daysOfMonth[1] = 29;
	}
	for (int i = 0; i < 12; i++) {
		if (dayFromTheOrigin - daysOfMonth[i] <= 0) {
			date.month = i + 1;
			break;
		}
		dayFromTheOrigin -= daysOfMonth[i];
	}
	date.day = dayFromTheOrigin;
}

void getListOfWeek(Attendance& list, Date& start, Date& end, int theDay) {
	Date tmpDate;
	getDayOfWeek(start);
	getDayOfWeek(end);
	int dayStart, dayEnd, count = 0;
	//Date startWeek, endWeek;
	if (start.DOW > theDay) {
		dayStart = start.dayFromTheOrigin + (6 - start.DOW) + theDay + 1;
	}
	else {
		dayStart = start.dayFromTheOrigin + (theDay - start.DOW);
	}
	if (end.DOW < theDay) {
		dayEnd = end.dayFromTheOrigin - end.DOW - (6 - theDay) - 1;
	}
	else {
		dayEnd = end.dayFromTheOrigin + (theDay - end.DOW);
	}
	//getDate(startWeek, dayStart);
	//getDate(endWeek, dayEnd);
	list.numberOfWeek = (dayEnd - dayStart) / 7 + 1;
	list.listOfWeek = new Date[list.numberOfWeek];
	for (int i = dayStart; i <= dayEnd; i += 7) {
		getDate(tmpDate, i);
		list.listOfWeek[count++] = tmpDate;
	}
}

bool isValidClass(string classID) {
	ifstream classFile("../../Class.txt");
	string tmpClassID;
	while(!classFile.eof()) {
		getline(classFile, tmpClassID);
		if (tmpClassID == classID) {
			return true;
		}
	}
	return false;
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
	while (choose < 1 || choose > 3 || cin.fail() || !isValidYear(sem.year) || !isSemesterExist(sem.year, choose) || !isValidClass(sem.classID))
	{
		cin.clear();
		cin.ignore(32767, '\n');

		string err = "";

		if (!isValidYear(sem.year)) {
			err += "\n\n\tThe academic year you type is illegal!";
		}
		else if(choose < 1 || choose > 3 || cin.fail()) {
			err += "\n\n\tYour choice is illegal!";
		} 
		else if (!isSemesterExist(sem.year, choose)) {
			err += "\n\n\tThe academic year and semester you type have not been existed!\n\tCreate before import!";
		}
		
		if (!isValidClass(sem.classID)) {
			err += "\n\n\tThe classID you enter not found!";
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
		string no, tmpDay;
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
			fin >> cour[i].startDate.day;
			fin.ignore();
			fin >> cour[i].startDate.month;
			fin.ignore();
			fin >> cour[i].startDate.year;
			fin.ignore();
			fin >> cour[i].endDate.day;
			fin.ignore();
			fin >> cour[i].endDate.month;
			fin.ignore();
			fin >> cour[i].endDate.year;
			fin.ignore();
			getline(fin, tmpDay, ',');
			if (tmpDay == "MON") {
				cour[i].day = 0;
			}
			else if (tmpDay == "TUE") {
				cour[i].day = 1;
			}
			else if (tmpDay == "WED") {
				cour[i].day = 2;
			}
			else if (tmpDay == "THU") {
				cour[i].day = 3;
			}
			else if (tmpDay == "FRI") {
				cour[i].day = 4;
			}
			else if (tmpDay == "SAT") {
				cour[i].day = 5;
			}
			else if (tmpDay == "SUN") {
				cour[i].day = 6;
			}
			getListOfWeek(cour[i].atd, cour[i].startDate, cour[i].endDate, cour[i].day);
			fin >> cour[i].startHour;
			fin.ignore();
			fin >> cour[i].endHour;
			fin.ignore();
			fin >> cour[i].startMin;
			fin.ignore();
			fin >> cour[i].endMin;
			fin.ignore();
			getline(fin, cour[i].room, '\n');
			cour[i].status = true;
		}
		ofstream fout;
		fout.open("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
		fout << count;
		for (int i = 0; i < count; i++) {
			fout << endl << cour[i].courseID ;
			fout << endl << cour[i].courseName ;
			fout << endl << cour[i].classID;
			fout << endl << cour[i].lecturerUsername;
			fout << endl << cour[i].lecturerName;
			fout << endl << cour[i].degree;
			fout << endl << cour[i].startDate.day << " " << cour[i].startDate.month << " " << cour[i].startDate.year;
			fout << endl << cour[i].endDate.day << " " << cour[i].endDate.month << " " << cour[i].endDate.year;
			fout << endl << cour[i].day;
			fout << endl << cour[i].startHour << " " << cour[i].endHour;
			fout << endl << cour[i].startMin << " " << cour[i].endMin;
			fout << endl << cour[i].room;
			fout << endl << cour[i].status;
		}
		//create course files of class schedule
		for (int i = 0; i < count; i++) {
			//get class students
			int NumberOfStudent = 0;
			StudentInCourse* studentInCour = nullptr;
			ifstream studentFile("../../" + sem.classID + "-Student.txt");
			if (!studentFile.is_open()) {
				ClearPrintDelay("\n\tYou have to import student file of class " + sem.classID + " first!");
				return;
			}
			studentFile >> NumberOfStudent;
			studentInCour = new StudentInCourse[NumberOfStudent];
			for (int j = 0; j < NumberOfStudent; j++) {
				studentFile.ignore();
				getline(studentFile, studentInCour[j].std.id);
				getline(studentFile, studentInCour[j].std.password);
				getline(studentFile, studentInCour[j].std.name);
				getline(studentFile, studentInCour[j].std.DoB);
				getline(studentFile, studentInCour[j].std.classID);
				studentFile >> studentInCour[j].std.status;
				studentInCour[j].scb.midterm = -1;
				studentInCour[j].scb.final = -1;
				studentInCour[j].scb.bonus = -1;
				studentInCour[j].scb.total = -1;
				studentInCour[j].listOfCheckIn = new bool[cour[i].atd.numberOfWeek];
				for (int k = 0; k < cour[i].atd.numberOfWeek; k++) {
					studentInCour[j].listOfCheckIn[k] = false;
				}
				studentInCour[j].statusInCourse = 1;
			}
			studentFile.close();
			//write to class course
			ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + cour[i].courseID + "-Student.txt");
			courseFile << NumberOfStudent;
			for (int j = 0; j < NumberOfStudent; j++) {
				courseFile << endl << studentInCour[j].std.id ;
				courseFile << endl << studentInCour[j].std.password;
				courseFile << endl << studentInCour[j].std.name;
				courseFile << endl << studentInCour[j].std.DoB;
				courseFile << endl << studentInCour[j].std.classID;
				courseFile << endl << studentInCour[j].std.status;
				courseFile << endl << studentInCour[j].scb.midterm;
				courseFile << endl << studentInCour[j].scb.final;
				courseFile << endl << studentInCour[j].scb.bonus;
				courseFile << endl << studentInCour[j].scb.total;
				for (int k = 0; k < cour[i].atd.numberOfWeek; k++) {
					courseFile << endl << studentInCour[j].listOfCheckIn[k];
				}
				courseFile << endl << studentInCour[j].statusInCourse;
			}
			courseFile.close();
			for (int j = 0; j < NumberOfStudent; j++) {
				delete[] studentInCour[j].listOfCheckIn;
			}
			delete[] studentInCour;
		}
		for (int i = 0; i < count; i++) {
			delete[] cour[i].atd.listOfWeek;
		}
		delete[] cour;
		fout.close();
	}
	fin.close();
	ClearPrintDelay("\n\tImport successfully!");
}

void addCourse(Semester sem) {
	Course addCourse;
	string tmpDay;
	cout << "\n\tEnter: " << endl;
	cout << "\tCourse ID: ";
	getline(cin, addCourse.courseID);
	cout << "\tCourse name: ";
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + addCourse.courseID + "-Student.txt");
	if (courseFileIn.is_open()) {
		ClearPrintDelay("\n\tThis course has been existed!");
		courseFileIn.close();
		return;
	}
	getline(cin, addCourse.courseName);
	cout << "\tClass ID: " << sem.classID << endl;
	addCourse.classID = sem.classID;
	cout << "\tLecturer username: ";
	getline(cin, addCourse.lecturerUsername);
	cout << "\tLecturer name: ";
	getline(cin, addCourse.lecturerName);
	cout << "\tLecturer degree: ";
	getline(cin, addCourse.degree);
	cout << "\tStart date(D M Y): ";
	cin >> addCourse.startDate.day >> addCourse.startDate.month >> addCourse.startDate.year;
	cout << "\tEnd date(D M Y): ";
	cin >> addCourse.endDate.day >> addCourse.endDate.month >> addCourse.endDate.year;
	cin.ignore();
	cout << "\tDay of Week(capitalize the first three letters): ";
	getline(cin, tmpDay);
	if (tmpDay == "MON") {
		addCourse.day = 0;
	}
	else if (tmpDay == "TUE") {
		addCourse.day = 1;
	}
	else if (tmpDay == "WED") {
		addCourse.day = 2;
	}
	else if (tmpDay == "THU") {
		addCourse.day = 3;
	}
	else if (tmpDay == "FRI") {
		addCourse.day = 4;
	}
	else if (tmpDay == "SAT") {
		addCourse.day = 5;
	}
	else if (tmpDay == "SUN") {
		addCourse.day = 6;
	}
	getListOfWeek(addCourse.atd, addCourse.startDate, addCourse.endDate, addCourse.day);
	cout << "\tStart hour, minute: ";
	cin >> addCourse.startHour >> addCourse.startMin;
	cout << "\tEnd hour, minute: ";
	cin >> addCourse.endHour >> addCourse.endMin;
	cin.ignore();
	cout << "\tRoom: ";
	getline(cin, addCourse.room);
	addCourse.status = true;

	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	int numberOfCour;
	scheduleFileIn >> numberOfCour;
	scheduleFileIn.ignore();
	string tmp, remain = "";
	while (!scheduleFileIn.eof()) {
		getline(scheduleFileIn, tmp);	
		remain += (tmp + "\n");
	}
	ofstream scheduleFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	scheduleFileOut << ++numberOfCour << endl;
	scheduleFileOut << remain;
	scheduleFileOut << addCourse.courseID << endl;
	scheduleFileOut << addCourse.courseName << endl;
	scheduleFileOut << addCourse.classID << endl;
	scheduleFileOut << addCourse.lecturerUsername << endl;
	scheduleFileOut << addCourse.lecturerName << endl;
	scheduleFileOut << addCourse.degree << endl;
	scheduleFileOut << addCourse.startDate.day << " " << addCourse.startDate.month << " " << addCourse.startDate.year << endl;
	scheduleFileOut << addCourse.endDate.day << " " << addCourse.endDate.month << " " << addCourse.endDate.year << endl;
	scheduleFileOut << addCourse.day << endl;
	scheduleFileOut << addCourse.startHour << " " << addCourse.startMin << endl;
	scheduleFileOut << addCourse.endHour << " " << addCourse.endMin << endl;
	scheduleFileOut << addCourse.room << endl;
	scheduleFileOut << addCourse.status;
	scheduleFileIn.close();
	scheduleFileOut.close();
	// get student in class
	int NumberOfStudent = 0;
	StudentInCourse* studentInCour = nullptr;
	ifstream studentFile("../../" + sem.classID + "-Student.txt");
	if (!studentFile.is_open()) {
		ClearPrintDelay("\n\tYou have to import student file of class " + sem.classID + " first!");
		return;
	}
	studentFile >> NumberOfStudent;
	studentInCour = new StudentInCourse[NumberOfStudent];
	for (int j = 0; j < NumberOfStudent; j++) {
		studentFile.ignore();
		getline(studentFile, studentInCour[j].std.id);
		getline(studentFile, studentInCour[j].std.password);
		getline(studentFile, studentInCour[j].std.name);
		getline(studentFile, studentInCour[j].std.DoB);
		getline(studentFile, studentInCour[j].std.classID);
		studentFile >> studentInCour[j].std.status;
		studentInCour[j].scb.midterm = -1;
		studentInCour[j].scb.final = -1;
		studentInCour[j].scb.bonus = -1;
		studentInCour[j].scb.total = -1;
		studentInCour[j].listOfCheckIn = new bool[addCourse.atd.numberOfWeek];
		for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
			studentInCour[j].listOfCheckIn[k] = false;
		}
		studentInCour[j].statusInCourse = 1;
	}
	studentFile.close();
	//write to class course
	ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + addCourse.courseID + "-Student.txt");
	courseFile << NumberOfStudent;
	for (int j = 0; j < NumberOfStudent; j++) {
		courseFile << endl << studentInCour[j].std.id;
		courseFile << endl << studentInCour[j].std.password;
		courseFile << endl << studentInCour[j].std.name;
		courseFile << endl << studentInCour[j].std.DoB;
		courseFile << endl << studentInCour[j].std.classID;
		courseFile << endl << studentInCour[j].std.status;
		courseFile << endl << studentInCour[j].scb.midterm;
		courseFile << endl << studentInCour[j].scb.final;
		courseFile << endl << studentInCour[j].scb.bonus;
		courseFile << endl << studentInCour[j].scb.total;
		for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
			courseFile << endl << studentInCour[j].listOfCheckIn[k];
		}
		courseFile << endl << studentInCour[j].statusInCourse;
	}
	courseFile.close();
	for (int j = 0; j < NumberOfStudent; j++) {
		delete[] studentInCour[j].listOfCheckIn;
	}
	delete[] studentInCour;
	delete[] addCourse.atd.listOfWeek;
}

void reCreateCourseFile(Semester sem, Course &addCourse, Course &oldCourse, string newCourseID, bool isChangeDate) {
	// get student in class
	int NumberOfStudent = 0;
	StudentInCourse* studentInCour = nullptr;
	bool* tmpCheckList;
	ifstream studentFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + addCourse.courseID + "-Student.txt");
	getListOfWeek(addCourse.atd, addCourse.startDate, addCourse.endDate, addCourse.day);
	getListOfWeek(oldCourse.atd, oldCourse.startDate, oldCourse.endDate, oldCourse.day);
	studentFile >> NumberOfStudent;
	studentFile.ignore();
	studentInCour = new StudentInCourse[NumberOfStudent];
	for (int j = 0; j < NumberOfStudent; j++) {
		getline(studentFile, studentInCour[j].std.id);
		getline(studentFile, studentInCour[j].std.password);
		getline(studentFile, studentInCour[j].std.name);
		getline(studentFile, studentInCour[j].std.DoB);
		getline(studentFile, studentInCour[j].std.classID);
		studentFile >> studentInCour[j].std.status;
		studentFile.ignore();
		studentFile >> studentInCour[j].scb.midterm;
		studentFile.ignore();
		studentFile >> studentInCour[j].scb.final;
		studentFile.ignore();
		studentFile >> studentInCour[j].scb.bonus;
		studentFile.ignore();
		studentFile >> studentInCour[j].scb.total;
		studentFile.ignore();
		studentInCour[j].listOfCheckIn = new bool[addCourse.atd.numberOfWeek];
		if (isChangeDate) { 
			tmpCheckList = new bool[oldCourse.atd.numberOfWeek];
			for (int k = 0; k < oldCourse.atd.numberOfWeek; k++) {
				studentFile >> tmpCheckList[k];
				studentFile.ignore();
			}
			for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
				studentInCour[j].listOfCheckIn[k] = false;
			}
			delete[] tmpCheckList;
		}
		else {
			for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
				studentFile >> studentInCour[j].listOfCheckIn[k];
				studentFile.ignore();
			}
		}
		studentFile >> studentInCour[j].statusInCourse;
		studentFile.ignore();
	}
	studentFile.close();
	//write to class course
	ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + newCourseID + "-Student.txt");
	courseFile << NumberOfStudent;
	for (int j = 0; j < NumberOfStudent; j++) {
		courseFile << endl << studentInCour[j].std.id;
		courseFile << endl << studentInCour[j].std.password;
		courseFile << endl << studentInCour[j].std.name;
		courseFile << endl << studentInCour[j].std.DoB;
		courseFile << endl << studentInCour[j].std.classID;
		courseFile << endl << studentInCour[j].std.status;
		courseFile << endl << studentInCour[j].scb.midterm;
		courseFile << endl << studentInCour[j].scb.final;
		courseFile << endl << studentInCour[j].scb.bonus;
		courseFile << endl << studentInCour[j].scb.total;
		for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
			courseFile << endl << studentInCour[j].listOfCheckIn[k];
		}
		courseFile << endl << studentInCour[j].statusInCourse;
	}
	courseFile.close();
	for (int j = 0; j < NumberOfStudent; j++) {
		delete[] studentInCour[j].listOfCheckIn;
	}
	delete[] studentInCour;
	delete[] addCourse.atd.listOfWeek;
}

void editCourse(Semester sem) {
	string top = "", bottom = "", tmpCourseID, tmpDay, tmpLine;
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
	getline(scheduleFileIn, tmpCourseID);
	top += tmpCourseID;
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
			scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpCourse.room);
			scheduleFileIn >> tmpCourse.status;
			scheduleFileIn.ignore();
			if (!tmpCourse.status) {
				ClearPrintDelay("\n\tThis course has been removed!");
				return;
			}
			while (!scheduleFileIn.eof()) {
				getline(scheduleFileIn, tmpLine);
				bottom += ("\n" + tmpLine);
			}
			break;
		}
		else {
			top += ("\n" + tmpCourseID);
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Course ID" << endl;
	cout << "\t2. Course Name" << endl;
	cout << "\t3. Lecturer Username" << endl;
	cout << "\t4. Lecturer Name" << endl;
	cout << "\t5. Lecturer Degree" << endl;
	cout << "\t6. Start Date, End Date" << endl;
	cout << "\t7. Day of Week" << endl;
	cout << "\t8. Start Hour, Minute" << endl;
	cout << "\t9. End Hour, Minute" << endl;
	cout << "\t10. Room" << endl;
	cout << "\n\tEnter your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 10 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Course ID" << endl;
		cout << "\t2. Course Name" << endl;
		cout << "\t3. Lecturer Username" << endl;
		cout << "\t4. Lecturer Name" << endl;
		cout << "\t5. Lecturer Degree" << endl;
		cout << "\t6. Start Date, End Date" << endl;
		cout << "\t7. Day of Week" << endl;
		cout << "\t8. Start Hour, Minute" << endl;
		cout << "\t9. End Hour, Minute" << endl;
		cout << "\t10. Room" << endl;
		cout << "\n\tEnter your choice: ";
		cin >> choose;
	}
	ClearPrintDelay();
	cin.ignore();
	switch (choose)
	{
	case 0:
		break;
	case 1:
	{
		Course oldCourse;
		string newCourseID, stringPath = "../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt";
		cout << "\n\tEnter Course ID: ";
		getline(cin, newCourseID);
		reCreateCourseFile(sem, tmpCourse, oldCourse, newCourseID, false);
		char* charArrayPath = new char[stringPath.length() + 1];
		for (int i = 0; i < stringPath.length(); i++) {
			charArrayPath[i] = stringPath[i];
		}
		charArrayPath[stringPath.length()] = '\0';
		remove(charArrayPath);
		delete[] charArrayPath;
		tmpCourse.courseID = newCourseID;
		break;
	}
	case 2:
		cout << "\n\tEnter Course Name: ";
		getline(cin, tmpCourse.courseName);
		break;
	case 3:
		cout << "\n\tEnter Lecturer Username: ";
		getline(cin, tmpCourse.lecturerUsername);
		break;
	case 4:
		cout << "\n\tEnter Lecturer Name: ";
		getline(cin, tmpCourse.lecturerName);
		break;
	case 5:
		cout << "\n\tEnter Lecturer Degree: ";
		getline(cin, tmpCourse.degree);
		break;
	case 6:
		{
		Course oldCourse;
		oldCourse.startDate = tmpCourse.startDate;
		oldCourse.endDate = tmpCourse.endDate;
		oldCourse.day = tmpCourse.day;
		cout << "\n\tEnter Start date(D M Y): ";
		cin >> tmpCourse.startDate.day >> tmpCourse.startDate.month >> tmpCourse.startDate.year;
		cin.ignore();
		cout << "\n\tEnter End date(D M Y): ";
		cin >> tmpCourse.endDate.day >> tmpCourse.endDate.month >> tmpCourse.endDate.year;
		cin.ignore();
		reCreateCourseFile(sem, tmpCourse, oldCourse, tmpCourse.courseID, true);
		break;
		}
	case 7:
		{
			cout << "\n\tEnter Day of Week: ";
			getline(cin, tmpDay);
			if (tmpDay == "MON") {
				tmpCourse.day = 0;
			}
			else if (tmpDay == "TUE") {
				tmpCourse.day = 1;
			}
			else if (tmpDay == "WED") {
				tmpCourse.day = 2;
			}
			else if (tmpDay == "THU") {
				tmpCourse.day = 3;
			}
			else if (tmpDay == "FRI") {
				tmpCourse.day = 4;
			}
			else if (tmpDay == "SAT") {
				tmpCourse.day = 5;
			}
			else if (tmpDay == "SUN") {
				tmpCourse.day = 6;
			}
			Course oldCourse;
			oldCourse.startDate = tmpCourse.startDate;
			oldCourse.endDate = tmpCourse.endDate;
			oldCourse.day = tmpCourse.day;
			reCreateCourseFile(sem, tmpCourse, oldCourse, tmpCourse.courseID, true);
			break;
		}
	case 8:
		cout << "\n\tEnter Start Hour, Minute: ";
		cin >> tmpCourse.startHour >> tmpCourse.startMin;
		cin.ignore();
		break;
	case 9:
		cout << "\n\tEnter End Hour, Minute: ";
		cin >> tmpCourse.endHour >> tmpCourse.endMin;
		cin.ignore();
		break;
	case 10:
		cout << "\n\tEnter Room: ";
		getline(cin, tmpCourse.room);
		break;
	}
	ofstream scheduleFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	scheduleFileOut << top << endl;
	scheduleFileOut << tmpCourse.courseID << endl;
	scheduleFileOut << tmpCourse.courseName << endl;
	scheduleFileOut << tmpCourse.classID << endl;
	scheduleFileOut << tmpCourse.lecturerUsername << endl;
	scheduleFileOut << tmpCourse.lecturerName << endl;
	scheduleFileOut << tmpCourse.degree << endl;
	scheduleFileOut << tmpCourse.startDate.day << " " << tmpCourse.startDate.month << " " << tmpCourse.startDate.year << endl;
	scheduleFileOut << tmpCourse.endDate.day << " " << tmpCourse.endDate.month << " " << tmpCourse.endDate.year << endl;
	scheduleFileOut << tmpCourse.day << endl;
	scheduleFileOut << tmpCourse.startHour << " " << tmpCourse.startMin << endl;
	scheduleFileOut << tmpCourse.endHour << " " << tmpCourse.endMin << endl;
	scheduleFileOut << tmpCourse.room << endl;
	scheduleFileOut << tmpCourse.status;
	scheduleFileOut << bottom;
	scheduleFileOut.close();
}

void removeCourse(Semester sem) {
	string top = "", bottom = "", tmpCourseID, tmpDay, tmpLine;
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
	getline(scheduleFileIn, tmpCourseID);
	top += tmpCourseID;
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
			scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
			scheduleFileIn.ignore();
			getline(scheduleFileIn, tmpCourse.room);
			scheduleFileIn >> tmpCourse.status;
			scheduleFileIn.ignore();
			while (!scheduleFileIn.eof()) {
				getline(scheduleFileIn, tmpLine);
				bottom += ("\n" + tmpLine);
			}
			break;
		}
		else {
			top += ("\n" + tmpCourseID);
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}

	string stringPath = "../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt";
	char* charArrayPath = new char[stringPath.length() + 1];
	for (int i = 0; i < stringPath.length(); i++) {
		charArrayPath[i] = stringPath[i];
	}
	charArrayPath[stringPath.length()] = '\0';
	remove(charArrayPath);
	delete[] charArrayPath;

	tmpCourse.status = false;
	ofstream scheduleFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	scheduleFileOut << top << endl;
	scheduleFileOut << tmpCourse.courseID << endl;
	scheduleFileOut << tmpCourse.courseName << endl;
	scheduleFileOut << tmpCourse.classID << endl;
	scheduleFileOut << tmpCourse.lecturerUsername << endl;
	scheduleFileOut << tmpCourse.lecturerName << endl;
	scheduleFileOut << tmpCourse.degree << endl;
	scheduleFileOut << tmpCourse.startDate.day << " " << tmpCourse.startDate.month << " " << tmpCourse.startDate.year << endl;
	scheduleFileOut << tmpCourse.endDate.day << " " << tmpCourse.endDate.month << " " << tmpCourse.endDate.year << endl;
	scheduleFileOut << tmpCourse.day << endl;
	scheduleFileOut << tmpCourse.startHour << " " << tmpCourse.startMin << endl;
	scheduleFileOut << tmpCourse.endHour << " " << tmpCourse.endMin << endl;
	scheduleFileOut << tmpCourse.room << endl;
	scheduleFileOut << tmpCourse.status;
	scheduleFileOut << bottom;
	scheduleFileOut.close();
}

void addStudentToCourse(Semester sem) {
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
	// get old students
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	if (!courseFileIn.is_open()) {
		ClearPrintDelay("\n\tCan't open course of class file!");
		return;
	}

	int numStuInCourse = 0;
	courseFileIn >> numStuInCourse;
	courseFileIn.ignore();
	string oldContent = "", tmpLine;
	while (!courseFileIn.eof()) {
		getline(courseFileIn, tmpLine);
		oldContent += ("\n" + tmpLine);
	}
	courseFileIn.close();
	// get info of new student
	StudentInCourse newStudent;
	cout << "\n\tEnter Student ID: ";
	getline(cin, newStudent.std.id);
	cout << "\tEnter Student Password: ";
	getline(cin, newStudent.std.password);
	cout << "\tEnter Student Name: ";
	getline(cin, newStudent.std.name);
	cout << "\tEnter Student DOB(DD MM YYYY): ";
	getline(cin, newStudent.std.DoB);
	cout << "\tEnter Student Class ID: ";
	getline(cin, newStudent.std.classID);
	newStudent.std.status = true;
	newStudent.scb.midterm = -1;
	newStudent.scb.final = -1;
	newStudent.scb.bonus = -1;
	newStudent.scb.total = -1;
	newStudent.listOfCheckIn = new bool[tmpCourse.atd.numberOfWeek];
	for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
		newStudent.listOfCheckIn[k] = false;
	}
	newStudent.statusInCourse = 1;
	// add new student
	ofstream courseFileOut("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	courseFileOut << ++numStuInCourse;
	courseFileOut << oldContent;
	courseFileOut << endl << newStudent.std.id;
	courseFileOut << endl << newStudent.std.password;
	courseFileOut << endl << newStudent.std.name;
	courseFileOut << endl << newStudent.std.DoB;
	courseFileOut << endl << newStudent.std.classID;
	courseFileOut << endl << newStudent.std.status;
	courseFileOut << endl << newStudent.scb.midterm;
	courseFileOut << endl << newStudent.scb.final;
	courseFileOut << endl << newStudent.scb.bonus;
	courseFileOut << endl << newStudent.scb.total;
	for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
		courseFileOut << endl << newStudent.listOfCheckIn[k];
	}
	courseFileOut << endl << newStudent.statusInCourse;
	courseFileOut.close();
	delete[] newStudent.listOfCheckIn;
	delete[] tmpCourse.atd.listOfWeek;
}

void removeStudentInCourse(Semester sem) {
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
			tmpStudent.statusInCourse = 0;
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

void viewListOfCourses(Semester sem) {
	int numberOfClass = 0;
	Class* classes = nullptr;
	ifstream classFile;
	classFile.open("../../Class.txt");
	if (!classFile.is_open()) {
		ClearPrintDelay("Class.txt not found");
		return;
	}
	classFile >> numberOfClass;
	classes = new Class[numberOfClass];
	for (int i = 0; i < numberOfClass; i++) {
		getline(classFile, classes[i].classID);
	}
	ClearPrintDelay();
	Course tmpCourse;
	string tmpDay;
	int numberOfCourse = 0;
	bool isCourseExist;
	for (int i = 0; i < numberOfClass; i++) {
		isCourseExist = false;
		ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + classes[i].classID + "-Schedule.txt");
		if (scheduleFileIn.is_open()) {
			scheduleFileIn >> numberOfCourse;
			scheduleFileIn.ignore();
			while (!scheduleFileIn.eof()) {
				getline(scheduleFileIn, tmpCourse.courseID);
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
				scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
				scheduleFileIn.ignore();
				scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
				scheduleFileIn.ignore();
				getline(scheduleFileIn, tmpCourse.room);
				scheduleFileIn >> tmpCourse.status;
				scheduleFileIn.ignore();
				if (tmpCourse.status) {
					if (!isCourseExist) {
						cout << "\n\t================ " << classes[i].classID << " ================\n";
						isCourseExist = true;
					}
					cout << endl << "\tCourse ID: " << tmpCourse.courseID;
					cout << endl << "\tCourse Name: " << tmpCourse.courseName;
					cout << endl << "\tLeturer Username: " << tmpCourse.lecturerUsername;
					cout << endl << "\tLeturer Name: " << tmpCourse.lecturerName;
					cout << endl << "\tLeturer Degree: " << tmpCourse.degree;
					cout << endl << "\tStart Date: " << tmpCourse.startDate.day << "/" << tmpCourse.startDate.month << "/" << tmpCourse.startDate.year;
					cout << endl << "\tEnd Date: " << tmpCourse.endDate.day << "/" << tmpCourse.endDate.month << "/" << tmpCourse.endDate.year;
					cout << endl << "\tDay of Week: ";
					switch (tmpCourse.day)
					{
					case 0:
						cout << "Monday";
						break;
					case 1:
						cout << "Tuesday";
						break;
					case 2:
						cout << "Wednesday";
						break;
					case 3:
						cout << "Thursday";
						break;
					case 4:
						cout << "Friday";
						break;
					case 5:
						cout << "Saturday";
						break;
					case 6:
						cout << "Sunday";
						break;
					}
					cout << endl << "\tStart Hour, Minute: " << tmpCourse.startHour << ":" << tmpCourse.startMin;
					cout << endl << "\tEnd Hour, Minute: " << tmpCourse.endHour << ":" << tmpCourse.endMin;
					cout << endl << "\tRoom :" << tmpCourse.room << endl;
					cout << "\n\t --------------------------------------\n";
				}
			}
			scheduleFileIn.close();
		}
	}
	delete[] classes;
	system("pause");
}

void viewListOfStuInCour(Semester sem) {
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
			cout << endl << "\n\tStudent ID: " << tmpStudent.std.id;
			cout << endl << "\tPassword: " << tmpStudent.std.password;
			cout << endl << "\tStudent Name: " << tmpStudent.std.name;
			cout << endl << "\tDay of Birth: " << tmpStudent.std.DoB << endl;
		}
	}
	cout << "\n\t==================================\n";
	system("pause");
	courseFileIn.close();
}

void viewAtdListOfCour(Semester sem) {
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
			for (int i = 0; i < tmpCourse.atd.numberOfWeek; i++) {
				cout << endl << "\t\t------------------";
				cout << endl << "\t    Date: " << tmpCourse.atd.listOfWeek[i].day << " / " << tmpCourse.atd.listOfWeek[i].month << " / " << tmpCourse.atd.listOfWeek[i].year;
				cout << endl << "\t    Attendance: ";
				if(tmpStudent.listOfCheckIn[i])
					cout << "Yes";
				else
					cout << "No";
			}
			cout << endl;
		}
	}
	cout << "\n\t==================================\n";
	system("pause");
	courseFileIn.close();
}

void scheduleMenu(Semester sem) {
	ClearPrintDelay();
	ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-Schedule.txt");
	if (!scheduleFileIn.is_open()) {
		ClearPrintDelay("\n\tYou have to import schedule file of class " + sem.classID + " first!");
		return;
	}
	scheduleFileIn.close();
	// schedule menu
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Add a new course" << endl;
	cout << "\t2. Edit a course" << endl;
	cout << "\t3. Remove a course" << endl;
	cout << "\t4. Add student to a course" << endl;
	cout << "\t5. Remove student in a course" << endl;
	cout << "\t6. View list of student in a course" << endl;
	cout << "\t7. View attendance list of a course" << endl;
	cout << "\n\tEnter your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 7 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Add a new course" << endl;
		cout << "\t2. Edit a course" << endl;
		cout << "\t3. Remove a course" << endl;
		cout << "\t4. Add student to a course" << endl;
		cout << "\t5. Remove student in a course" << endl;
		cout << "\t6. View list of student in a course" << endl;
		cout << "\t7. View attendance list of a course" << endl;
		cout << "\n\tEnter your choice: ";
		cin >> choose;
	}
	ClearPrintDelay();
	cin.ignore();
	switch (choose)
	{
	case 0:
		break;
	case 1:
		addCourse(sem);
		scheduleMenu(sem);
		break;
	case 2:
		editCourse(sem);
		scheduleMenu(sem);
		break;
	case 3:
		removeCourse(sem);
		scheduleMenu(sem);
		break;
	case 4:
		addStudentToCourse(sem);
		scheduleMenu(sem);
		break;
	case 5:
		removeStudentInCourse(sem);
		scheduleMenu(sem);
		break;
	case 6:
		viewListOfStuInCour(sem);
		scheduleMenu(sem);
		break;
	case 7:
		viewAtdListOfCour(sem);
		scheduleMenu(sem);
		break;
	}
}

void courseMenu()
{
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Create academic year and semester" << endl;
	cout << "\t2. Import schedule" << endl;
	cout << "\t3. Specific Class Course Menu" << endl;
	cout << "\t4. View all course of Semester" << endl;
	cout << "\n\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 4 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Create academic year and semester" << endl;
		cout << "\t2. Import schedule" << endl;
		cout << "\t3. Specific Class Course Menu" << endl;
		cout << "\t4. View all course of Semester" << endl;
		cout << "\n\tEnter  your choice: ";
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
	case 3:
		{
		ClearPrintDelay();
		Semester sem;
		int choose;
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
		cin >> choose;
		while (choose < 1 || choose > 3 || cin.fail() || !isValidYear(sem.year) || !isSemesterExist(sem.year, choose) || !isValidClass(sem.classID))
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

			if (!isValidClass(sem.classID)) {
				err += "\n\n\tThe classID you enter not found!";
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
		scheduleMenu(sem);
		courseMenu();
		break;
		}
	case 4:
		{
		ClearPrintDelay();
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
		courseMenu();
		break;
		}
	}
}
