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
void MainMenu();
void Login();
bool CheckLogin(string rolepath, User* user);
void UserMenu(User& user);
void ClearPrintDelay(string message);
void ClearPrintDelay();
void ViewProfile(User user);
#endif
