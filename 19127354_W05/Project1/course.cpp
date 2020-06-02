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
		if (dayFromTheOrigin - daysOfMonth[i] < 0) {
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
		fout << count << endl;
		for (int i = 0; i < count; i++) {
			fout << cour[i].courseID << endl;
			fout << cour[i].courseName << endl;
			fout << cour[i].classID << endl;
			fout << cour[i].lecturerUsername << endl;
			fout << cour[i].lecturerName << endl;
			fout << cour[i].degree << endl;
			fout << cour[i].startDate.day << " " << cour[i].startDate.month << " " << cour[i].startDate.year << endl;
			fout << cour[i].endDate.day << " " << cour[i].endDate.month << " " << cour[i].endDate.year << endl;
			fout << cour[i].day << endl;
			fout << cour[i].startHour << " " << cour[i].endHour << endl;
			fout << cour[i].startMin << " " << cour[i].endMin << endl;
			fout << cour[i].room << endl;
			fout << cour[i].status << endl;
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
				studentInCour[j].scb.bobus = -1;
				studentInCour[j].scb.total = -1;
				studentInCour[j].listOfCheckIn = new bool[cour[i].atd.numberOfWeek];
				for (int k = 0; k < cour[i].atd.numberOfWeek; k++) {
					studentInCour[j].listOfCheckIn[k] = true;
				}
				studentInCour[j].statusInCourse = 1;
			}
			studentFile.close();
			//write to class course
			ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + cour[i].courseID + "-Student.txt");
			courseFile << NumberOfStudent << endl;
			for (int j = 0; j < NumberOfStudent; j++) {
				courseFile << studentInCour[j].std.id << endl;
				courseFile << studentInCour[j].std.password << endl;
				courseFile << studentInCour[j].std.name << endl;
				courseFile << studentInCour[j].std.DoB << endl;
				courseFile << studentInCour[j].std.classID << endl;
				courseFile << studentInCour[j].std.status << endl;
				courseFile << studentInCour[j].scb.midterm << endl;
				courseFile << studentInCour[j].scb.final << endl;
				courseFile << studentInCour[j].scb.bobus << endl;
				courseFile << studentInCour[j].scb.total << endl;
				for (int k = 0; k < cour[i].atd.numberOfWeek; k++) {
					courseFile << studentInCour[j].listOfCheckIn[k] << endl;
				}
				courseFile << studentInCour[j].statusInCourse << endl;
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
		studentInCour[j].scb.bobus = -1;
		studentInCour[j].scb.total = -1;
		studentInCour[j].listOfCheckIn = new bool[addCourse.atd.numberOfWeek];
		for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
			studentInCour[j].listOfCheckIn[k] = true;
		}
		studentInCour[j].statusInCourse = 1;
	}
	studentFile.close();
	//write to class course
	ofstream courseFile("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + addCourse.courseID + "-Student.txt");
	courseFile << NumberOfStudent << endl;
	for (int j = 0; j < NumberOfStudent; j++) {
		courseFile << studentInCour[j].std.id << endl;
		courseFile << studentInCour[j].std.password << endl;
		courseFile << studentInCour[j].std.name << endl;
		courseFile << studentInCour[j].std.DoB << endl;
		courseFile << studentInCour[j].std.classID << endl;
		courseFile << studentInCour[j].std.status << endl;
		courseFile << studentInCour[j].scb.midterm << endl;
		courseFile << studentInCour[j].scb.final << endl;
		courseFile << studentInCour[j].scb.bobus << endl;
		courseFile << studentInCour[j].scb.total << endl;
		for (int k = 0; k < addCourse.atd.numberOfWeek; k++) {
			courseFile << studentInCour[j].listOfCheckIn[k] << endl;
		}
		courseFile << studentInCour[j].statusInCourse << endl;
	}
	courseFile.close();
	for (int j = 0; j < NumberOfStudent; j++) {
		delete[] studentInCour[j].listOfCheckIn;
	}
	delete[] studentInCour;
	delete[] addCourse.atd.listOfWeek;
}

void editCourse(Semester sem) {
	string top, bottom;
	bool isCourseFound = false;
	Course tmpCourse;
	cout << "\n\tEnter courseID: ";
	getline(cin, tmpCourse.courseID);
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Course ID" << endl;
	cout << "\t2. Course Name" << endl;
	cout << "\t3. Lecturer Username" << endl;
	cout << "\t4. Lecturer Name" << endl;
	cout << "\t5. Start Date" << endl;
	cout << "\t6. End Date" << endl;
	cout << "\t7. Start Hour, Minute" << endl;
	cout << "\t8. End Hour, Minute" << endl;
	cout << "\t9. Room" << endl;
	cout << "\n\tEnter your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 9 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Course ID" << endl;
		cout << "\t2. Course Name" << endl;
		cout << "\t3. Lecturer Username" << endl;
		cout << "\t4. Lecturer Name" << endl;
		cout << "\t5. Start Date" << endl;
		cout << "\t6. End Date" << endl;
		cout << "\t7. Start Hour, Minute" << endl;
		cout << "\t8. End Hour, Minute" << endl;
		cout << "\t9. Room" << endl;
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
		
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	}
}

void scheduleMenu(Semester sem) {
	ClearPrintDelay();
	// schedule menu
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Add a new course" << endl;
	cout << "\t2. Edit a course" << endl;
	cout << "\t3. Remove a course" << endl;
	cout << "\n\tEnter your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 3 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Add a new course" << endl;
		cout << "\t2. Edit a course" << endl;
		cout << "\t3. Remove a course" << endl;
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
		//editCourse(sem);
		//scheduleMenu(sem);
		break;
	case 3:
		//removeCourse(sem);
		//scheduleMenu(sem);
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
	cout << "\t3. Schedule menu" << endl;
	cout << "\n\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 3 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Create academic year and semester" << endl;
		cout << "\t2. Import schedule" << endl;
		cout << "\t3. Schedule menu" << endl;
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
}
