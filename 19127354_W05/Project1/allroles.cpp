#pragma once
#include"allroles.h"
void ClearPrintDelay() {
	system("cls");
}
void ClearPrintDelay(string message) {
	system("cls");
	cout << message << endl;
	Sleep(3000);
	system("cls");
}
void ChangePassword(User& user) {
	ClearPrintDelay();
	string rolepath = "../../" + user.role + ".txt", remain = "",
		oldPassword, newPassword, confirmPassword, tmp;
	int posstart = user.pos + user.username.length() + 2;
	int posend = posstart + user.password.length() + 2;
	int choose = -1;
	cout << "Enter old password: ";
	cin >> oldPassword;
	cout << "Enter new password: ";
	cin >> newPassword;
	cout << "Confirm new password: ";
	cin >> confirmPassword;
	while (oldPassword != user.password || newPassword != confirmPassword) {
		ClearPrintDelay("Your old password is wrong or confirm new password failed!");
		cout << "0. Back" << endl;
		cout << "1. Try again" << endl;
		cout << "Your choice: ";
		cin >> choose;
		while (choose < 0 || choose > 1 || cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			ClearPrintDelay("Your choose is illegal. Try again.");
			cout << "0. Back" << endl;
			cout << "1. Try again" << endl;
			cout << "Your choice: ";
			cin >> choose;
		}
		if (choose == 0) {
			break;
		}
		else {
			ClearPrintDelay();
			cout << "Enter old password: ";
			cin >> oldPassword;
			cout << "Enter new password: ";
			cin >> newPassword;
			cout << "Confirm new password: ";
			cin >> confirmPassword;
		}
	}
	if (choose != 0) {
		user.password = newPassword;
		fstream rolefile(rolepath, ios::in | ios::out);
		if (!rolefile.is_open()) {
			cout << "error";
		}
		else {
			rolefile.seekg(posend, ios::beg);
			while (!rolefile.eof()) {
				getline(rolefile, tmp);
				remain += (tmp + "\n");
			}
			fstream rolefile(rolepath, ios::in | ios::out);
			rolefile.seekp(posstart, ios::beg);
			rolefile << newPassword << endl;
			rolefile << remain;
			rolefile.close();
			ClearPrintDelay("Change successfully!");
		}
	}
}
void ViewProfile(User user) {
	ClearPrintDelay();
	cout << "Role: " << uppercase << user.role << endl;
	cout << "Name: " << uppercase << user.name << endl;
	cout << "Username: " << user.username << endl;
	if (user.role == "Lecturer") {
		cout << "Degree: " << user.degree << endl;
	}
	if (user.role == "Student") {
		cout << "Date of birth: " << user.DoB.day + "-" + user.DoB.month + "-" + user.DoB.year << endl;
	}
	system("pause");
}
void UserMenu(User& user) {
	ClearPrintDelay();
	int choose;
	cout << "0. Log out" << endl;
	cout << "1. View profile" << endl;
	cout << "2. Change password" << endl;
	cout << "Your choice: ";
	cin >> choose;
	while (choose < 0 || choose > 2 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("Your choice is illegal. Try again.");
		cout << "0. Log out" << endl;
		cout << "1. View profile" << endl;
		cout << "2. Change password" << endl;
		cout << "Your choice: ";
		cin >> choose;
	}
	switch (choose) {
	case 0:
		MainMenu();
		break;
	case 1:
		ViewProfile(user);
		UserMenu(user);
		break;
	case 2:
		ChangePassword(user);
		UserMenu(user);
	}
}

bool CheckLogin(string rolepath, User* user) {
	ClearPrintDelay();
	ifstream rolefile(rolepath);
	int NumberOfAcount;
	int pos;
	string active;
	string username;
	string password;
	string newline;
	if (rolepath == "../../Staff.txt") {
		user->role = "Staff";
	}
	else if (rolepath == "../../Lecturer.txt") {
		user->role = "Lecturer";
	}
	else {
		user->role = "Student";
	}
	if (rolefile.is_open()) {
		rolefile >> NumberOfAcount;
		getline(rolefile, newline);
		for (int i = 0; i < NumberOfAcount; i++) {
			pos = rolefile.tellg();
			getline(rolefile, username);
			getline(rolefile, password);
			getline(rolefile, user->name);
			if (rolepath == "../../Lecturer.txt") {
				getline(rolefile, user->degree);
			}
			if (rolepath == "../../Student.txt") {
				getline(rolefile, active);
				if (active == "1") {
					user->active = true;
				}
				else {
					user->active = false;
				}
				user->DoB.day = password.substr(0, 2);
				user->DoB.month = password.substr(2, 2);
				user->DoB.year = password.substr(4);
			}
			if (user->username == username && user->password == password) {
				if (!user->active) {
					return false;
				}
				user->pos = pos;
				return true;
			}
		}
		return false;
	}
	else {
		cout << "Error check log in!";
	}
}
void Login() {
	ClearPrintDelay();
	string staffpath = "../../Staff.txt";
	string lecturerpath = "../../Lecturer.txt";
	string studentpath = "../../Student.txt";
	User user;
	cout << "Username: ";
	cin >> user.username;
	cout << "Password: ";
	cin >> user.password;
	if (CheckLogin(staffpath, &user)) {
		ClearPrintDelay("Log in successfully!\nWelcome " + user.role + " " + user.name);
		UserMenu(user);
	}
	else if (CheckLogin(lecturerpath, &user)) {
		ClearPrintDelay("Log in successfully!\nWelcome " + user.role + " " + user.name);
		UserMenu(user);
	} if (CheckLogin(studentpath, &user)) {
		ClearPrintDelay("Log in successfully!\nWelcome " + user.role + " " + user.name);
		UserMenu(user);
	}
	else {
		ClearPrintDelay("Your account not found!");
		MainMenu();
	}
}
void MainMenu() {
	ClearPrintDelay();
	int choose;
	cout << "0. Exit" << endl;
	cout << "1. Log in" << endl;
	cout << "Your choice: ";
	cin >> choose;
	while (choose < 0 || choose > 1 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("Your choice is illegal. Try again.");
		cout << "0. Exit" << endl;
		cout << "1. Log in" << endl;
		cout << "Your choice: ";
		cin >> choose;
	}
	switch (choose) {
	case 0:
		return;
		break;
	case 1:
		ClearPrintDelay();
		Login();
		break;
	}
}
