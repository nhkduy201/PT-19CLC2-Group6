#pragma once
#ifndef _ALLROLE_H_
#define _ALLROLE_H_
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;
struct DateOfBirth {
	string day, month, year;
};
struct User {
	string role;
	string name;
	string username;
	string password;
	string degree = "";
	DateOfBirth DoB = { "", "", "" };
	int pos;
	bool active = true;
};

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

void MainMenu();
void Login();
bool CheckLogin(string rolepath, User* user);
void UserMenu(User& user);
void ClearPrintDelay(string message);
void ClearPrintDelay();
void ViewProfile(User user);
void removeStudent(string filepath, Student student[]);
void createStudent(string filepath);
void editStudent(string filepath, Student student[]);
void createStudent(string filepath);
void removeStudent(string filepath, Student student[]);
void editStudent(string filepath, Student student[]);
void viewStudents(string filepath, Student student[]);
void viewClasses(Class a[]);
void moveStudent(string filepath, Student student[]);
void classMenu();
#endif
