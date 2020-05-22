#include "allroles.h"

void createStudent(string filepath) {
	string id;
	string password;
	string name;
	string DoB;
	string classID;
	bool status;
	int NumberOfStudent;
	Student student[1000];

	cout << "Student ID: ";
	getline(cin, id);
	cout << "Student name: ";
	getline(cin, name);
	cout << "Date of Birth (DD MM YYYY): ";
	getline(cin, DoB);
	cout << "Student password will be DDMMYYYY (DoB without space)" << endl;
	string S = DoB;
	S.erase(5, 1);
	S.erase(2, 1);
	password = S;
	classID = filepath;
	cout << "Status: ";
	cin >> status;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
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
	NumberOfStudent += 1;
	ofstream fout;
	fout.open("../../" + filepath + "-Student.txt");
	fout << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent-1; i++) {
		fout << student[i].id << endl;
		fout << student[i].password << endl;
		fout << student[i].name << endl;
		fout << student[i].DoB << endl;
		fout << student[i].classID << endl;
		fout << student[i].status << endl;
		fout << endl;
	}
	fout << id << endl;
	fout << password << endl;
	fout << name << endl;
	fout << DoB << endl;
	fout << classID << endl;
	fout << status << endl;
	fout << endl;
	fout.close();
	
	Student std[1000];
	ifstream in;
	ofstream out;
	in.open("../../Student.txt");
	in >> NumberOfStudent;
	int temp = NumberOfStudent;
	for (int i = 0; i < NumberOfStudent; i++) {
		in.ignore();
		getline(in, std[i].id);
		getline(in, std[i].password);
		getline(in, std[i].name);
		in >> std[i].status;
	}
	NumberOfStudent += 1;
	out.open("../../Student.txt");
	out << NumberOfStudent << endl;;
	for (int i = 0; i < temp; i++) {
		out << std[i].id << endl;
		out << std[i].password << endl;
		out << std[i].name << endl;
		out << std[i].status << endl;
	}
	out << id << endl;
	out << password << endl;
	out << name << endl;
	out << status << endl;

	in.close();
	out.close();
}

void removeStudent(string filepath, Student student[]) {
	int NumberOfStudent = 0;
	string findingID;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
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
	fout.open("../../" + filepath + "-Student.txt");
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

	Student std[1000];

	ifstream inMain;
	inMain.open("../../Student.txt");
	if (!inMain.is_open())
		cout << "Can't open file!!" << endl;
	else {
		inMain >> NumberOfStudent;
		for (int i = 0; i < NumberOfStudent; i++) {
			inMain.ignore();
			getline(inMain, std[i].id);
			getline(inMain, std[i].password);
			getline(inMain, std[i].name);
			inMain >> std[i].status;		}
	}
	inMain.close();
	i = 0;
	for (i = 0; i < NumberOfStudent; i++) {
		if (findingID == std[i].id) {
			break;
		}
	}
	if (i < NumberOfStudent) {
		NumberOfStudent = NumberOfStudent - 1;
		for (int j = i; j < NumberOfStudent; j++)
			std[j] = std[j + 1];
	}

	ofstream outMain;
	outMain.open("../../Student.txt");
	outMain << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		outMain << std[i].id << endl;
		outMain << std[i].password << endl;
		outMain << std[i].name << endl;
		outMain << std[i].status << endl;
	}
	outMain.close();
}

void editStudent(string filepath, Student student[]) {
	int NumberOfStudent = 0;
	string findingID;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
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
	int i;
	int temp;
	for (i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			temp = i;
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
				cin.ignore();
				cout << "Input name: ";
				getline(cin, student[i].name);
				break; 
			}
			case 2: {
				cin.ignore();
				cout << "Input password: ";
				getline(cin, student[i].password);
				break;
			}
			case 3: {
				cin.ignore();
				cout << "Input DoB: ";
				getline(cin, student[i].DoB);
				break;
			}
			case 4: {
				cout << "Input status: ";
				cin >> student[i].status;
				break;
			}
			}
			break;
		}
	}

	ofstream fout;
	fout.open("../../" + filepath + "-Student.txt");
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
	
	Student std[1000];
	fin.open("../../Student.txt");
	int NumberOfStudents;
	fin >> NumberOfStudents;
	for (int i = 0; i < NumberOfStudents; i++) {
		fin.ignore();
		getline(fin, std[i].id);
		getline(fin, std[i].password);
		getline(fin, std[i].name);
		fin >> std[i].status;
	}
	for (int i = 0; i < NumberOfStudents; i++) {
		if (findingID == std[i].id) {
			std[i].id = student[temp].id;
			std[i].password=student[temp].password;
			std[i].name= student[temp].name;
			std[i].status= student[temp].status;
			break;
		}
	}
	ofstream outMain;
	outMain.open("../../Student.txt");
	outMain << NumberOfStudents << endl;
	for (int i = 0; i < NumberOfStudents; i++) {
		outMain << std[i].id << endl;
		outMain << std[i].password << endl;
		outMain << std[i].name << endl;
		outMain << std[i].status << endl;
	}
	outMain.close();
}

void viewStudents(string filepath, Student student[]) {
	int NumberOfStudent = 0;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
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

void moveStudent(string filepath, Student student[])
{
	string findingID;
	Student temp;
	int NumberOfStudent = 0;
	int i;
	ifstream fin1;
	fin1.open("../../" + filepath + "-Student.txt");
	if (!fin1.is_open()) {
		cout << "Class's not found";
	}
	else {
		fin1 >> NumberOfStudent;
		for (i = 0; i < NumberOfStudent; i++) {
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
	fout1.open("../../" + filepath + "-Student.txt");
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
	getline(cin, anotherClass);

	ifstream fin2;
	fin2.open("../../" + anotherClass + "-Student.txt");
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
	student[i].id = temp.id;
	student[i].password = temp.password;
	student[i].name = temp.name;
	student[i].DoB = temp.DoB;
	student[i].classID = temp.classID;
	student[i].status = temp.status;
	
	ofstream fout2;
	fout2.open("../../" + anotherClass + "-Student.txt");
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

void importStudent(ifstream& fin, Student& std)
{
	fin >> std.No;
	fin.ignore();
	getline(fin, std.id, ',');
	getline(fin, std.name, ',');
	getline(fin, std.gender, ',');
	getline(fin, std.DoB, ',');
	getline(fin, std.classID, '\n');
}

void importCsv(string filepath, Student student[])
{
	ifstream fin;
	fin.open("../../" + filepath + "-Student.csv");
	if (!fin.is_open())
		cout << "Can't find class!!" << endl;
	else {
		int count = 0;
		string fisrtline;
		getline(fin, fisrtline);
		while (fin.good()) {
			importStudent(fin, student[count]);
			student[count].status = 1;
			if (student[count].id.length() == 0)
				break;
			string S = student[count].DoB;
			S.erase(5,1);
			S.erase(2,1);
			student[count].password = S;
			S.insert(2, 1,' ');
			S.insert(5, 1,' ');
			student[count].DoB = S;
			count += 1;
		}
		ofstream fout;
		fout.open("../../" + filepath + "-Student.txt");
		fout << count << endl;
		for (int i = 0; i < count; i++) {
			fout << student[i].id << endl;
			fout << student[i].password << endl;
			fout << student[i].name << endl;
			fout << student[i].DoB << endl;
			fout << student[i].classID << endl;
			fout << student[i].status << endl;
			fout << endl;
		}

		Student std[1000];
		ifstream in;
		ofstream out;
		in.open("../../Student.txt");
		int NumberOfStudent;
		in >> NumberOfStudent;
		int temp = NumberOfStudent;
		for (int i = 0; i < NumberOfStudent; i++) {
			in.ignore();
			getline(in, std[i].id);
			getline(in, std[i].password);
			getline(in, std[i].name);
			in >> std[i].status;
		}
		NumberOfStudent += count;
		out.open("../../Student.txt");
		out << NumberOfStudent << endl;;
		for (int i = 0; i < temp; i++) {
			out << std[i].id << endl;
			out << std[i].password << endl;
			out << std[i].name << endl;
			out << std[i].status << endl;
		}
		for (int i = 0; i < count; i++) {
			out << student[i].id << endl;
			out << student[i].password << endl;
			out << student[i].name << endl;
			out << student[i].status << endl;
		}
		in.close();
		out.close();
		fout.close();

	}
	fin.close();
}

void classMenu()
{
	Class clas[100];
	Student student[1000];
	string classID;
	ClearPrintDelay();
	int choose;

	cout << "0. Exit" << endl;
	cout << "1. Import Csv" << endl;
	cout << "2. Add new student" << endl;
	cout << "3. Edit a student" << endl;
	cout << "4. Remove a student" << endl;
	cout << "5. Move student from class A to B" << endl;
	cout << "6. View list of classes" << endl;
	cout << "7. View students of a class" << endl;
	cout << endl;
	cout << "Enter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 7 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("Your choice is illegal. Try again.");
		cout << "0. Exit" << endl;
		cout << "1. Import Csv" << endl;
		cout << "2. Add new student" << endl;
		cout << "3. Edit a student" << endl;
		cout << "4. Remove a student" << endl;
		cout << "5. Move student from class A to B" << endl;
		cout << "6. View list of classes" << endl;
		cout << "7. View students of a class" << endl;

		cin >> choose;
	}

	cout << endl;
	cin.ignore();
	switch (choose)
	{
	case 0:
		MainMenu();
		break;
	case 1:
		cout << "Enter classID: ";
		getline(cin, classID);
		importCsv(classID, student);
		break;
	case 2:
		cout << "Enter classID: ";
		getline(cin, classID);
		createStudent(classID);
		break;
	case 3:
		cout << "Enter classID: ";
		getline(cin, classID);
		editStudent(classID, student);
		break;
	case 4:
		cout << "Enter classID: ";
		getline(cin, classID);
		removeStudent(classID, student);
		break;
	case 5:
		cout << "Enter classID: ";
		getline(cin, classID);
		moveStudent(classID, student);
		break;
	case 6:
		viewClasses(clas);
		break;
	case 7:
		cout << "Enter classID: ";
		getline(cin, classID);
		viewStudents(classID, student);
		break;
	}
}