#pragma once
#ifndef _ALLROLE_H_
#define _ALLROLE_H_
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>
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
void importStudent(ifstream& fin, Student& studentOut);
void importCsv(string classID, string filePath);
// staff course
struct Semester {
	string name;
	string year;
	string classID;
	string csvPath;
};
struct Date {
	int day, month, year, DOW;
	int dayFromTheOrigin;
};
struct Attendance {
	int numberOfWeek;
	Date* listOfWeek = nullptr;
};
struct Course {
	string courseID;
	string courseName;
	string classID;
	string lecturerUsername;
	string lecturerName;
	string degree;
	Date startDate;
	Date endDate;
	int day;
	Attendance atd;
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	string room;
	bool status;
};
struct Scoreboard {
	double midterm = -1;
	double final = -1;
	double bonus = -1;
	double total = -1;
};
struct StudentInCourse {
	Student std;
	Scoreboard scb;
	bool* listOfCheckIn;
	bool statusInCourse;
};
void courseMenu();
void createYearSemester();
bool isValidYear(string year);
bool isValidClass(string classID);
bool isSemesterExist(string yearIn, int choose);
void getDayOfWeek(Date& date);
void getDate(Date& date, int dayFromTheOrigin);
void getListOfWeek(Attendance& list, Date& start, Date& end, int theDay);
void importSchedule();
void standardPathFile(string& path);
void scheduleMenu(Semester sem);
void addCourse(Semester sem);
void editCourse(Semester sem);
void reCreateCourseFile(Semester sem, Course& addCourse, Course& oldCourse, string newCourseID, bool isChangeDate);
void removeCourse(Semester sem);
void addStudentToCourse(Semester sem);
void removeStudentInCourse(Semester sem);
void viewListOfCourses(Semester sem);
void viewListOfStuInCour(Semester sem);
void viewAtdListOfCour(Semester sem);
// lecturer
void lecturerMenu();
void importScoreboard(Semester sem);
void editAtd(Semester sem);
void viewScbOfCour(Semester sem);
void editScbOfStu(Semester sem);
#endif