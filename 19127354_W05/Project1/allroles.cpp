#pragma once
#include"allroles.h"
void ClearPrintDelay() {
	system("cls");
}
void ClearPrintDelay(string message) {
	system("cls");
	cout << message;
	Sleep(2000);
	system("cls");
}
void ChangePassword(User& user) {
	ClearPrintDelay();
	string rolepath = "../../" + user.role + ".txt", remain = "",
		oldPassword, newPassword, confirmPassword, tmp;
	int posstart = user.pos + user.username.length() + 2;
	int posend = posstart + user.password.length() + 2;
	int choose = -1;
	cout << "\n\tEnter old password: ";
	cin >> oldPassword;
	cout << "\n\tEnter new password: ";
	cin >> newPassword;
	cout << "\n\tConfirm new password: ";
	cin >> confirmPassword;
	while (oldPassword != user.password || newPassword != confirmPassword) {
		if (oldPassword != user.password) {
			ClearPrintDelay("\n\tYour old password is wrong!");
		}
		else {
			ClearPrintDelay("\n\tConfirm new password failed!");
		}
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Try again" << endl;
		cout << "\n\tYour choice: ";
		cin >> choose;
		while (choose < 0 || choose > 1 || cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			ClearPrintDelay("\n\tYour choose is illegal. Try again.");
			cout << "\n\t0. Back" << endl;
			cout << "\t1. Try again" << endl;
			cout << "\n\tYour choice: ";
			cin >> choose;
		}
		if (choose == 0) {
			break;
		}
		else {
			ClearPrintDelay();
			cout << "\n\tEnter old password: ";
			cin >> oldPassword;
			cout << "\n\tEnter new password: ";
			cin >> newPassword;
			cout << "\n\tConfirm new password: ";
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
			changePassInClass(user.classID, user.username, newPassword);
			ClearPrintDelay("\n\tChange successfully!");
		}
	}
}
void ViewProfile(User user) {
	ClearPrintDelay();
	cout << "\n\tRole: " << uppercase << user.role << endl;
	cout << "\tName: " << uppercase << user.name << endl;
	cout << "\tUsername: " << user.username << endl;
	if (user.role == "Lecturer") {
		cout << "\tDegree: " << user.degree << endl << endl;
	}else
	if (user.role == "Student") {
		cout << "\tClass: " << user.classID << endl;
		cout << "\tDate of birth: " << user.DoB.day + "-" + user.DoB.month + "-" + user.DoB.year << endl << endl;
	}
	else {
		cout << endl;
	}
	system("pause");
}
void UserMenu(User& user) {
	ClearPrintDelay();
	int choose;
	cout << "\n\t0. Log out" << endl;
	cout << "\t1. View profile" << endl;
	cout << "\t2. Change password" << endl;
	cout << "\t3. " + user.role + " Menu" << endl;
	cout << "\tYour choice: ";
	cin >> choose;
	while (choose < 0 || choose > 3 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Log out" << endl;
		cout << "\t1. View profile" << endl;
		cout << "\t2. Change password" << endl;
		cout << "\t3. " + user.role + " Menu" << endl;
		cout << "\tYour choice: ";
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
		break;
	case 3:
		if (user.role == "Staff") {
			classMenu();
			UserMenu(user);
		}
		else if (user.role == "Lecturer") {
			ClearPrintDelay("\n\tYour role feature has not been completed. We're so sorry about that!");
			UserMenu(user);
		}
		else {
			ClearPrintDelay("\n\tYour role feature has not been completed. We're so sorry about that!");
			UserMenu(user);
		}
	}
}

bool CheckLogin(string rolepath, User* user, bool& isWrongPw) {
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
				getline(rolefile, user->classID);
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
			else if (user->username == username && user->password != password) {
				isWrongPw = true;
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
	bool isWrongPw = false;
	cout << "\n\tUsername: ";
	cin >> user.username;
	cout << "\n\tPassword: ";
	cin >> user.password;
	if (CheckLogin(staffpath, &user, isWrongPw)) {
		ClearPrintDelay("\n\t _    _  _____  _      _____  _____ ___  ___ _____ \n\t| |  | ||  ___|| |    /  __ \\|  _  ||  \\/  ||  ___|\n\t| |  | || |__  | |    | /  \\/| | | || .  . || |__  \n\t| |/\\| ||  __| | |    | |    | | | || |\\/| ||  __| \n\t\\  /\\  /| |___ | |____| \\__/\\\\ \\_/ /| |  | || |___ \n\t \\/  \\/ \\____/ \\_____/ \\____/ \\___/ \\_|  |_/\\____/ \n\n\t" + user.role + ": " + user.name);
		UserMenu(user);
	}
	else if (CheckLogin(lecturerpath, &user, isWrongPw)) {
		ClearPrintDelay("\n\t _    _  _____  _      _____  _____ ___  ___ _____ \n\t| |  | ||  ___|| |    /  __ \\|  _  ||  \\/  ||  ___|\n\t| |  | || |__  | |    | /  \\/| | | || .  . || |__  \n\t| |/\\| ||  __| | |    | |    | | | || |\\/| ||  __| \n\t\\  /\\  /| |___ | |____| \\__/\\\\ \\_/ /| |  | || |___ \n\t \\/  \\/ \\____/ \\_____/ \\____/ \\___/ \\_|  |_/\\____/ \n\n\t" + user.role + ": " + user.name);
		UserMenu(user);
	}else if (CheckLogin(studentpath, &user, isWrongPw)) {
		ClearPrintDelay("\n\t _    _  _____  _      _____  _____ ___  ___ _____ \n\t| |  | ||  ___|| |    /  __ \\|  _  ||  \\/  ||  ___|\n\t| |  | || |__  | |    | /  \\/| | | || .  . || |__  \n\t| |/\\| ||  __| | |    | |    | | | || |\\/| ||  __| \n\t\\  /\\  /| |___ | |____| \\__/\\\\ \\_/ /| |  | || |___ \n\t \\/  \\/ \\____/ \\_____/ \\____/ \\___/ \\_|  |_/\\____/ \n\n\t" + user.role + ": " + user.name);
		UserMenu(user);
	}
	else {
		if (isWrongPw) {
			ClearPrintDelay("\n\tWrong password!");
		}
		else {
			ClearPrintDelay("\n\tYour account not found!");
		}
		MainMenu();
	}
}
void MainMenu() {
	ClearPrintDelay();
	int choose;
	cout << "\n\t___  ___        _         ___  ___                    \n\t|  \\/  |       (_)        |  \\/  |                    \n\t| .  . |  __ _  _  _ __   | .  . |  ___  _ __   _   _ \n\t| |\\/| | / _` || || '_ \\  | |\\/| | / _ \\| '_ \\ | | | |\n\t| |  | || (_| || || | | | | |  | ||  __/| | | || |_| |\n\t\\_|  |_/ \\__,_||_||_| |_| \\_|  |_/ \\___||_| |_| \\__,_|\n" << endl;
	cout << "\t0. Exit" << endl;
	cout << "\t1. Log in" << endl;
	cout << "\tYour choice: ";
	cin >> choose;
	while (choose < 0 || choose > 1 || cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t___  ___        _         ___  ___                    \n\t|  \\/  |       (_)        |  \\/  |                    \n\t| .  . |  __ _  _  _ __   | .  . |  ___  _ __   _   _ \n\t| |\\/| | / _` || || '_ \\  | |\\/| | / _ \\| '_ \\ | | | |\n\t| |  | || (_| || || | | | | |  | ||  __/| | | || |_| |\n\t\\_|  |_/ \\__,_||_||_| |_| \\_|  |_/ \\___||_| |_| \\__,_|\n" << endl;
		cout << "\t0. Exit" << endl;
		cout << "\t1. Log in" << endl;
		cout << "\tYour choice: ";
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
