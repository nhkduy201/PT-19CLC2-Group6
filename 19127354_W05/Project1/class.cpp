#include "allroles.h"

void createStudent(string filepath) {
	string id;
	string password;
	string name;
	string DoB;
	string classID;
	bool status;

	cin.ignore();
	cout << "Student ID: ";
	getline(cin, id);
	cout << "Student password: ";
	getline(cin, password);
	cout << "Student name: ";
	getline(cin, name);
	cout << "Date of Birth: ";
	getline(cin, DoB);
	cout << "ID of class: ";
	getline(cin, classID);
	cout << "Status: ";
	cin >> status;

	ofstream file;
	file.open(filepath + ".txt", ios::app);
	file << id << endl;
	file << password << endl;
	file << name << endl;
	file << DoB << endl;
	file << classID << endl;
	file << status << endl;
	file << endl;
	file.close();

	ofstream main;
	main.open("../../Student.txt", ios::app);
	main << id << endl;
	main << password << endl;
	main << name << endl;
	main << status << endl;
	main.close();
}

void removeStudent(string filepath, Student student[]) {
	int NumberOfStudent;
	string findingID;
	ifstream fin;
	fin.open(filepath + ".txt");
	if (!fin.is_open) {
		cout << "Class's not found";
	}
	else {
		fin >> NumberOfStudent;
		for (int i = 0; i < NumberOfStudent; i++) {
			fin.ignore();
			getline(fin, student[i].id);
			getline(fin, student[i].password);
			getline(fin, student[i].name);
			getline(fin, student[i].DoB);
			getline(fin, student[i].classID);
			fin >> student[i].status;
			fin.ignore();
		}
	}
	fin.close();
	cout << "Input Student ID you want to remove: ";
	getline(cin, findingID);
	int i;
	for (i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			break;
		}
	}
	if (i < NumberOfStudent) {
		NumberOfStudent = NumberOfStudent - 1;
		for (int j = i; j < NumberOfStudent; j++)
			student[j] = student[j + 1];
	}

	ofstream fout;
	fout.open(filepath + ".txt");
	fout << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		fout << student[i].id << endl;
		fout << student[i].password << endl;
		fout << student[i].name << endl;
		fout << student[i].DoB << endl;
		fout << student[i].classID << endl;
		fout << student[i].status << endl;
	}
	fout.close();
}

void editStudent(string filepath, Student student[]) {
	int NumberOfStudent;
	string findingID;
	ifstream fin;
	fin.open(filepath + ".txt");
	if (!fin.is_open) {
		cout << "Class's not found";
	}
	else {
		fin >> NumberOfStudent;
		for (int i = 0; i < NumberOfStudent; i++) {
			fin.ignore();
			getline(fin, student[i].id);
			getline(fin, student[i].password);
			getline(fin, student[i].name);
			getline(fin, student[i].DoB);
			getline(fin, student[i].classID);
			fin >> student[i].status;
			fin.ignore();
		}
	}
	fin.close();
	cout << "Input Student ID you want to edit: ";
	getline(cin, findingID);

	for (int i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			int choose;
			cout << "1. Edit name\n";
			cout << "2. Edit password\n";
			cout << "3. Edit DoB\n";
			cout << "4. Edit status\n";
			cout << "Your choice: ";
			cin >> choose;

			while (choose < 1 || choose > 4 || cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				ClearPrintDelay("Your choice is illegal. Try again.");
				cout << "1. Edit name\n";
				cout << "2. Edit password\n";
				cout << "3. Edit DoB\n";
				cout << "4. Edit status\n";
				cout << "Your choice: ";
				cin >> choose;
			}
			switch (choose){
			case 1: {
				getline(cin, student[i].name);
				break; 
			}
			case 2: {
				getline(cin, student[i].password);
				break;
			}
			case 3: {
				getline(cin, student[i].DoB);
				break;
			}
			case 4: {
				cin >> student[i].status;
				break;
			}
			}
		}
	}

	ofstream fout;
	fout.open(filepath + ".txt");
	fout << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		fout << student[i].id << endl;
		fout << student[i].password << endl;
		fout << student[i].name << endl;
		fout << student[i].DoB << endl;
		fout << student[i].classID << endl;
		fout << student[i].status << endl;
	}
	fout.close();
}

