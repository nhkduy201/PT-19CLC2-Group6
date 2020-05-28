#pragma once
#ifndef _ALLROLE_H_
#define _ALLROLE_H_
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;

// allroles
struct DateOfBirth {
	string day, month, year;
};
struct User {
	string role;
	string name;
	string username;
	string password;
	string degree = "";
	string classID;
	DateOfBirth DoB = { "", "", "" };
	int pos;
	bool active = true;
};
void MainMenu();
void Login();
bool CheckLogin(string rolepath, User* user, bool& isWrongPw);
void UserMenu(User& user);
void ClearPrintDelay(string message);
void ClearPrintDelay();
void ViewProfile(User user);
// staff class
struct Student {
	int No;
	string id;
	string password;
	string name;
	string gender;
	string DoB;
	string classID;
	bool status;
};
struct Class {
	string classID;
};
void removeStudent(string filepath);
void createStudent(string filepath);
void editStudent(string filepath);
void viewStudents(string filepath);
void viewClasses();
void moveStudent(string filepath);
void changePassInClass(string filepath, string findingID, string password);
void classMenu();
// staff course
struct Semester {
	string name;
	string year;
	string classID;
	string csvPath;
};
struct AttendanceTime {
	int numOfWeek;
	string* listOfWeekTime;
};
struct Course {
	string courseID;
	string courseName;
	string classID;
	string lecturerUsername;
	string lecturerName;
	string degree;
	string startDate;
	string endDate;
	string day;
	string startHour;
	string startMin;
	AttendanceTime atd;
	string endHour;
	string endMin;
	string room;
};
struct Scoreboard {
	double midterm = -1;
	double final = -1;
	double bobus = -1;
	double total = -1;
};
struct StudentInCourse {
	Student std;
	Scoreboard scb;
	bool* listOfCheckIn;
};
void courseMenu();
void createYearSemester();
bool isValidYear(string year);
bool isSemesterExist(string yearIn, int choose);
void importSchedule();
void standardPathFile(string& path);
#endif