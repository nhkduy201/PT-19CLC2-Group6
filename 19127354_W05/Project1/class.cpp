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
	int NumberOfStudent = 0;
	string findingID;
	ifstream fin;
	fin.open(filepath + ".txt");
	if (!fin.is_open()) {
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
		fout << endl;
	}
	fout.close();
}

void editStudent(string filepath, Student student[]) {
	int NumberOfStudent = 0;
	string findingID;
	ifstream fin;
	fin.open(filepath + ".txt");
	if (!fin.is_open()) {
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
		fout << endl;
	}
	fout.close();
}

void viewStudents(string filepath, Student student[]) {
	int NumberOfStudent = 0;
	ifstream fin;
	fin.open(filepath + ".txt");
	if (!fin.is_open()) {
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

	ClearPrintDelay();
	for (int i = 0; i < NumberOfStudent; i++) {
		cout << student[i].id << endl;
		cout << student[i].name << endl;
		cout << student[i].DoB << endl;
		cout << student[i].classID << endl;
		cout << student[i].status << endl;
		cout << endl;
	}
}

void viewClasses(Class a[]) {
	int NumberOfClass = 0;
	ifstream fin;
	fin.open("../../Class.txt");
	if (!fin.is_open()) {
		cout << "Missing file" << endl;
	}
	else {
		fin >> NumberOfClass;
		for (int i = 0; i < NumberOfClass; i++) {
			fin >> a[i].classID;
		}
	}
	ClearPrintDelay();
	for (int i = 0; i < NumberOfClass; i++) {
		cout << a[i].classID << endl;
	}
}

void importCsv(string filepath, Student student[])
{

}

void moveStudent(string filepath, Student student[])
{
	string findingID;
	Student temp;
	int NumberOfStudent = 0;
	int i;
	ifstream fin1;
	fin1.open(filepath + ".txt");
	if (!fin1.is_open()) {
		cout << "Class's not found";
	}
	else {
		fin1 >> NumberOfStudent;
		for (int i = 0; i < NumberOfStudent; i++) {
			fin1.ignore();
			getline(fin1, student[i].id);
			getline(fin1, student[i].password);
			getline(fin1, student[i].name);
			getline(fin1, student[i].DoB);
			getline(fin1, student[i].classID);
			fin1 >> student[i].status;
			fin1.ignore();
		}
	}
	fin1.close();
	cout << "Input Student ID you want to move: ";
	getline(cin, findingID);

	for (i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			temp.id = student[i].id;
			temp.password = student[i].password;
			temp.name = student[i].name;
			temp.DoB = student[i].DoB;
			temp.classID = student[i].classID;
			temp.status = student[i].status;
			break;
		}
	}
	if (i < NumberOfStudent) {
		NumberOfStudent = NumberOfStudent - 1;
		for (int j = i; j < NumberOfStudent; j++)
			student[j] = student[j + 1];
	}

	ofstream fout1;
	fout1.open(filepath + ".txt");
	fout1 << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		fout1 << student[i].id << endl;
		fout1 << student[i].password << endl;
		fout1 << student[i].name << endl;
		fout1 << student[i].DoB << endl;
		fout1 << student[i].classID << endl;
		fout1 << student[i].status << endl;
		fout1 << endl;
	}
	fout1.close();
	string anotherClass;
	cout << "Enter the class you want " << findingID << " to move to: ";
	cin.ignore();
	getline(cin, anotherClass);

	ifstream fin2;
	fin2.open(anotherClass + ".txt");
	if (!fin2.is_open()) {
		cout << "Class's not found";
	}
	else {
		fin2 >> NumberOfStudent;
		for (i = 0; i < NumberOfStudent; i++) {
			fin2.ignore();
			getline(fin2, student[i].id);
			getline(fin2, student[i].password);
			getline(fin2, student[i].name);
			getline(fin2, student[i].DoB);
			getline(fin2, student[i].classID);
			fin2 >> student[i].status;
			fin2.ignore();
		}
	}
	fin2.close();
	NumberOfStudent = NumberOfStudent + 1;
	for (i = 0; i < NumberOfStudent; i++) {
		if (i == NumberOfStudent - 1) {
			student[i].id = temp.id;
			student[i].password = temp.password;
			student[i].name = temp.name;
			student[i].DoB = temp.DoB;
			student[i].classID = temp.classID;
			student[i].status = temp.status;
		}
	}

	ofstream fout2;
	fout2.open(anotherClass + ".txt");
	fout2 << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		fout2 << student[i].id << endl;
		fout2 << student[i].password << endl;
		fout2 << student[i].name << endl;
		fout2 << student[i].DoB << endl;
		fout2 << student[i].classID << endl;
		fout2 << student[i].status << endl;
		fout2 << endl;
	}
	fout2.close();
}



