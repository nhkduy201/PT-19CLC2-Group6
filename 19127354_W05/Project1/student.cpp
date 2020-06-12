#include"allroles.h"
void getCurrentDate(Date& currentDate) {
	time_t result = time(NULL);
	char charArrayDate[26];
	ctime_s(charArrayDate, sizeof charArrayDate, &result);
	string stringDate = charArrayDate;
	string tmpDOB = stringDate.substr(0, 3);
	string tmpYear = stringDate.substr(20, 4);
	currentDate.year = stoi(tmpYear);
	string tmpMon = stringDate.substr(4, 3);
	string tmpDay = stringDate.substr(8, 2);
	string tmpHour = stringDate.substr(11, 2);
	string tmpMin = stringDate.substr(14, 2);

	if (tmpHour[0] == '0') {
		tmpHour = tmpHour.substr(1, 1);
	}
	currentDate.time.min = stoi(tmpMin);
	if (tmpMin[0] == '0') {
		tmpMin = tmpMin.substr(1, 1);
	}

	currentDate.day = stoi(tmpDay);
	currentDate.time.hour = stoi(tmpHour);
	currentDate.time.min = stoi(tmpMin);

	/*if (tmpDOB == "Mon") {
		currentDate.DOW = 0;
	}
	else if (tmpDOB == "Tue") {
		currentDate.DOW = 1;
	}
	else if (tmpDOB == "Wed") {
		currentDate.DOW = 2;
	}
	else if (tmpDOB == "Thu") {
		currentDate.DOW = 3;
	}
	else if (tmpDOB == "Fri") {
		currentDate.DOW = 4;
	}
	else if (tmpDOB == "Sat") {
		currentDate.DOW = 5;
	}
	else if (tmpDOB == "Sun") {
		currentDate.DOW = 6;
	}*/
	if (tmpMon == "Jan") {
		currentDate.month = 1;
	}
	else if (tmpMon == "Feb") {
		currentDate.month = 2;
	}
	else if (tmpMon == "Mar") {
		currentDate.month = 3;
	}
	else if (tmpMon == "Apr") {
		currentDate.month = 4;
	}
	else if (tmpMon == "May") {
		currentDate.month = 5;
	}
	else if (tmpMon == "Jun") {
		currentDate.month = 6;
	}
	else if (tmpMon == "Jul") {
		currentDate.month = 7;
	}
	else if (tmpMon == "Aug") {
		currentDate.month = 8;
	}
	else if (tmpMon == "Sep") {
		currentDate.month = 9;
	}
	else if (tmpMon == "Oct") {
		currentDate.month = 10;
	}
	else if (tmpMon == "Nov") {
		currentDate.month = 11;
	}
	else if (tmpMon == "Dec") {
		currentDate.month = 12;
	}
}

void studentCheckIn(Semester sem, string studentID, string courseID) {
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	tmpCourse.courseID = courseID;
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
			scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
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
	tmpStudent.std.id = studentID;
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
			Date curDate;
			bool validCheckIn = false;
			getCurrentDate(curDate);
			for (int k = 0; k < tmpCourse.atd.numberOfWeek; k++) {
				validCheckIn = tmpCourse.atd.listOfWeek[k].day == curDate.day
					&& tmpCourse.atd.listOfWeek[k].month == curDate.month
					&& tmpCourse.atd.listOfWeek[k].year == curDate.year
					&& (curDate.time.hour * 60 + curDate.time.min >= tmpCourse.startHour * 60 + tmpCourse.startMin)
					&& (curDate.time.hour * 60 + curDate.time.min < tmpCourse.endHour * 60 + tmpCourse.endMin);
				if (validCheckIn && tmpStudent.listOfCheckIn[k]) {
					ClearPrintDelay("\n\tAlready Check-in!");
					return;
				}
				else if(validCheckIn && !tmpStudent.listOfCheckIn[k]) {
					tmpStudent.listOfCheckIn[k] = true;
				}
			}
			if (!validCheckIn) {
				ClearPrintDelay("\n\tThere is no course happening now!");
				return;
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
	ClearPrintDelay("\n\tCheck-in successfully!");
}

void viewCheckInResult(Semester sem, string studentID, string courseID) {
		string tmpCourseID, tmpDay;
		bool isCourseFound = false;
		Course tmpCourse;
		tmpCourse.courseID = courseID;
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
				scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
				scheduleFileIn.ignore();
				scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
				break;
			}
		}
		scheduleFileIn.close();
		if (!isCourseFound) {
			ClearPrintDelay("\n\tYour course ID not found!");
			return;
		}

		//get student matched, get top remain, bottom remain
		string bottom = "", tmpStudentID, tmpLine;
		bool isStudentFound = false;
		int changeWeek;
		StudentInCourse tmpStudent;
		tmpStudent.std.id = studentID;
		ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
		if (!courseFileIn.is_open()) {
			ClearPrintDelay("\n\tCan't open course of class file!");
			return;
		}
		getline(courseFileIn, tmpStudentID);
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
				cout << "\n\t==================================";
				cout << endl << "\n\t    Student ID: " << tmpStudent.std.id;
				cout << endl << "\t    Student Name: " << tmpStudent.std.name;
				for (int i = 0; i < tmpCourse.atd.numberOfWeek; i++) {
					cout << endl << "\t\t------------------";
					cout << endl << "\t    Date: " << tmpCourse.atd.listOfWeek[i].day << " / " << tmpCourse.atd.listOfWeek[i].month << " / " << tmpCourse.atd.listOfWeek[i].year;
					cout << endl << "\t    Attendance: ";
					if (tmpStudent.listOfCheckIn[i])
						cout << "Yes";
					else
						cout << "No";
				}
				cout << "\n\n\t==================================\n";
				system("pause");
				break;
			}
		}
		courseFileIn.close();
}

void viewSchedule(Semester sem, string ID) {
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
	StudentInCourse tmpStudent;
	Course tmpCourse;
	string tmpDay;
	int numberOfCourse = 0;
	int numberOfStudent = 0;
	bool isCourseExist;
	for (int i = 0; i < numberOfClass; i++)
	{
		isCourseExist = false;
		ifstream scheduleFileIn("../../" + sem.year + "-" + sem.name + "-" + classes[i].classID + "-Schedule.txt");
		if (scheduleFileIn.is_open()) {
			scheduleFileIn >> numberOfCourse;
			scheduleFileIn.ignore();
			while (!scheduleFileIn.eof()) {
				getline(scheduleFileIn, tmpCourse.courseID);
				ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + classes[i].classID + "-" + tmpCourse.courseID + "-Student.txt");
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
				scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
				scheduleFileIn.ignore();
				scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
				scheduleFileIn.ignore();
				getline(scheduleFileIn, tmpCourse.room);
				scheduleFileIn >> tmpCourse.status;
				scheduleFileIn.ignore();
				if (tmpCourse.status) {
					if (courseFileIn.is_open()) {
						courseFileIn >> numberOfStudent;
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
							if (tmpStudent.std.id == ID && tmpStudent.std.status == 1 && tmpStudent.statusInCourse == 1) {
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
								break;
							}
						}
					}
				}
			}
			scheduleFileIn.close();
		}
	}
	delete[] classes;
	system("pause");
	// code here
}

void viewStdScore(Semester sem, string studentID, string courseID) {
	string tmpCourseID, tmpDay;
	bool isCourseFound = false;
	Course tmpCourse;
	tmpCourse.courseID = courseID;
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
			scheduleFileIn >> tmpCourse.startHour >> tmpCourse.startMin;
			scheduleFileIn.ignore();
			scheduleFileIn >> tmpCourse.endHour >> tmpCourse.endMin;
			break;
		}
	}
	scheduleFileIn.close();
	if (!isCourseFound) {
		ClearPrintDelay("\n\tYour course ID not found!");
		return;
	}

	//get student matched, get top remain, bottom remain
	string bottom = "", tmpStudentID, tmpLine;
	bool isStudentFound = false;
	int changeWeek;
	StudentInCourse tmpStudent;
	tmpStudent.std.id = studentID;
	ifstream courseFileIn("../../" + sem.year + "-" + sem.name + "-" + sem.classID + "-" + tmpCourse.courseID + "-Student.txt");
	if (!courseFileIn.is_open()) {
		ClearPrintDelay("\n\tCan't open course of class file!");
		return;
	}
	getline(courseFileIn, tmpStudentID);
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
			cout << "\n\t==================================";
			cout << endl << "\n\t    Student ID: " << tmpStudent.std.id;
			cout << endl << "\t    Student Name: " << tmpStudent.std.name;
			cout << endl << "\t    BirthDate:    " << tmpStudent.std.classID;
			cout << endl << "\t     Name: " << tmpStudent.std.name;
			cout << endl << "\t\t------------------";
			cout << endl << "\t    MidTerm: " << tmpStudent.scb.midterm;
			cout << endl << "\t    Final:   " << tmpStudent.scb.final;
			cout << endl << "\t    Bonus:   " << tmpStudent.scb.bonus;
			cout << endl << "\t    Total:   " << tmpStudent.scb.total;
			system("pause");
			break;
		}
	}
	if (!isStudentFound) {
		ClearPrintDelay("\n\tYou don't study at this course!!");
		return;
	}
	courseFileIn.close();
}


void studentMenu(string studentID) {
	ClearPrintDelay();
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
	int choose;
	cout << "\n\t0. Back" << endl;
	cout << "\t1. Check-in" << endl;
	cout << "\t2. View check-in result" << endl;
	cout << "\t3. View schedule" << endl;
	cout << "\n\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 3 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Check-in" << endl;
		cout << "\t2. View check-in result" << endl;
		cout << "\t3. View schedule" << endl;
		cout << "\n\tEnter  your choice: ";
		cin >> choose;
	}
	cin.ignore();
	ClearPrintDelay();
	switch (choose)
	{
		case 0:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			{
				if (choose == 1)
				{
					string courseID;
					cout << "\n\tEnter course ID: ";
					cin >> courseID;
					studentCheckIn(sem, studentID, courseID);
				}
				else if (choose == 2) {
					string courseID;
					cout << "\n\tEnter course ID: ";
					cin >> courseID;
					viewCheckInResult(sem, studentID, courseID);
				}
				else if (choose == 3) {
					viewSchedule(sem, sem.classID);
				}
				else if (choose == 4) {
					string courseID;
					cout << "\n\tEnter course ID: ";
					cin >> courseID;
					viewStdScore(sem, studentID, courseID);
				}
				break;
			}
	}

}
