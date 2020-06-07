#include "allroles.h"

void createStudent(string filepath) {
	string id;
	string password;
	string name;
	string DoB;
	string classID;
	bool status;
	int NumberOfStudent;
	Student* student = nullptr;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	cout << "\tStudent ID: ";
	getline(cin, id);
	cout << "\tStudent name: ";
	getline(cin, name);
	cout << "\tDate of Birth (DD MM YYYY): ";
	getline(cin, DoB);
	cout << "\tDefault student password will be DDMMYYYY (DoB without space)" << endl;
	string S = DoB;
	S.erase(5, 1);
	S.erase(2, 1);
	password = S;
	classID = filepath;
	cout << "\tStatus: ";
	cin >> status;
	
	fin >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		fin.ignore();
		getline(fin, student[i].id);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		getline(fin, student[i].DoB);
		getline(fin, student[i].classID);
		fin >> student[i].status;
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
	}
	fout << id << endl;
	fout << password << endl;
	fout << name << endl;
	fout << DoB << endl;
	fout << classID << endl;
	fout << status << endl;
	fout.close();
	
	Student* studentOut;
	ifstream in;
	ofstream out;
	in.open("../../Student.txt");
	if (!in.is_open()) {
		ClearPrintDelay("\n\tStudent.txt not found");
		return;
	}
	in >> NumberOfStudent;
	studentOut = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		in.ignore();
		getline(in, studentOut[i].id);
		getline(in, studentOut[i].password);
		getline(in, studentOut[i].name);
		getline(in, studentOut[i].classID);
		in >> studentOut[i].status;
	}
	NumberOfStudent += 1;
	out.open("../../Student.txt");
	out << NumberOfStudent << endl;;
	for (int i = 0; i < NumberOfStudent - 1; i++) {
		out << studentOut[i].id << endl;
		out << studentOut[i].password << endl;
		out << studentOut[i].name << endl;
		out << studentOut[i].classID << endl;
		out << studentOut[i].status << endl;
	}
	out << id << endl;
	out << password << endl;
	out << name << endl;
	out << classID << endl;
	out << status << endl;

	delete[] student;
	delete[] studentOut;
	in.close();
	out.close();
	ClearPrintDelay("\n\tCreate successfully!");
}

void removeStudent(string filepath) {
	int NumberOfStudent = 0;
	Student* student = nullptr;
	string findingID;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	fin >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		fin.ignore();
		getline(fin, student[i].id);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		getline(fin, student[i].DoB);
		getline(fin, student[i].classID);
		fin >> student[i].status;
	}
	
	fin.close();
	cout << "\tInput Student ID you want to remove: ";
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
	}
	fout.close();

	Student* studentOut = nullptr;

	ifstream inMain;
	inMain.open("../../Student.txt");
	if (!inMain.is_open()) {
		ClearPrintDelay("\n\tStudent.txt not found");
		return;
	}
	inMain >> NumberOfStudent;
	studentOut = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		inMain.ignore();
		getline(inMain, studentOut[i].id);
		getline(inMain, studentOut[i].password);
		getline(inMain, studentOut[i].name);
		getline(inMain, studentOut[i].classID);
		inMain >> studentOut[i].status;		
		}
	inMain.close();
	i = 0;
	for (i = 0; i < NumberOfStudent; i++) {
		if (findingID == studentOut[i].id) {
			break;
		}
	}
	if (i < NumberOfStudent) {
		NumberOfStudent = NumberOfStudent - 1;
		for (int j = i; j < NumberOfStudent; j++)
			studentOut[j] = studentOut[j + 1];
	}

	ofstream outMain;
	outMain.open("../../Student.txt");
	outMain << NumberOfStudent << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		outMain << studentOut[i].id << endl;
		outMain << studentOut[i].password << endl;
		outMain << studentOut[i].name << endl;
		outMain << studentOut[i].classID << endl;
		outMain << studentOut[i].status << endl;
	}
	outMain.close();
	delete[] student;
	delete[] studentOut;
	ClearPrintDelay("\n\tRemove successfully!");
}

void editStudent(string filepath) {
	int NumberOfStudent = 0;
	string findingID;
	Student* student = nullptr;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	fin >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		fin.ignore();
		getline(fin, student[i].id);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		getline(fin, student[i].DoB);
		getline(fin, student[i].classID);
		fin >> student[i].status;
	}
	
	fin.close();
	cout << "\tInput Student ID you want to edit: ";
	getline(cin, findingID);
	int temp;
	ClearPrintDelay();
	for (int i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			temp = i;
			int choose;
			cout << "\n\t1. Edit name\n";
			cout << "\t2. Edit password\n";
			cout << "\t3. Edit DoB\n";
			cout << "\t4. Edit status\n";
			cout << "\n\tYour choice: ";
			cin >> choose;

			while (choose < 1 || choose > 4 || cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				ClearPrintDelay("\n\tYour choice is illegal. Try again.");
				cout << "\n\t1. Edit name\n";
				cout << "\t2. Edit password\n";
				cout << "\t3. Edit DoB\n";
				cout << "\t4. Edit status\n";
				cout << "\n\tYour choice: ";
				cin >> choose;
			}
			ClearPrintDelay();
			switch (choose){
			case 1: {
				cin.ignore();
				cout << "\n\tInput name: ";
				getline(cin, student[i].name);
				break; 
			}
			case 2: {
				cin.ignore();
				cout << "\n\tInput password: ";
				getline(cin, student[i].password);
				break;
			}
			case 3: {
				cin.ignore();
				cout << "\n\tInput DoB (DD MM YYYY): ";
				getline(cin, student[i].DoB);
				break;
			}
			case 4: {
				cout << "\n\tInput status: ";
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
	}
	fout.close();
	
	Student* studentOut;
	fin.open("../../Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tStudent.txt not found");
		return;
	}
	int NumberOfStudents;
	fin >> NumberOfStudents;
	studentOut = new Student[NumberOfStudents];
	for (int i = 0; i < NumberOfStudents; i++) {
		fin.ignore();
		getline(fin, studentOut[i].id);
		getline(fin, studentOut[i].password);
		getline(fin, studentOut[i].name);
		getline(fin, studentOut[i].classID);
		fin >> studentOut[i].status;
	}
	for (int i = 0; i < NumberOfStudents; i++) {
		if (findingID == studentOut[i].id) {
			studentOut[i].id = student[temp].id;
			studentOut[i].password=student[temp].password;
			studentOut[i].name= student[temp].name;
			studentOut[i].classID = student[temp].classID;
			studentOut[i].status= student[temp].status;
			break;
		}
	}
	ofstream outMain;
	outMain.open("../../Student.txt");
	outMain << NumberOfStudents << endl;
	for (int i = 0; i < NumberOfStudents; i++) {
		outMain << studentOut[i].id << endl;
		outMain << studentOut[i].password << endl;
		outMain << studentOut[i].name << endl;
		outMain << studentOut[i].classID << endl;
		outMain << studentOut[i].status << endl;
	}
	outMain.close();
	delete[] student;
	delete[] studentOut;
	ClearPrintDelay("\n\tEdit successfully!");
}

void viewStudents(string filepath) {
	int NumberOfStudent = 0;
	Student* student = nullptr;
	ifstream fin;
	fin.open("../../" + filepath + "-Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	fin >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		fin.ignore();
		getline(fin, student[i].id);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		getline(fin, student[i].DoB);
		getline(fin, student[i].classID);
		fin >> student[i].status;
	}
	fin.close();

	ClearPrintDelay();
	cout << endl;
	for (int i = 0; i < NumberOfStudent; i++) {
		cout << "\t" << student[i].id << endl;
		cout << "\t" << student[i].name << endl;
		cout << "\t" << student[i].DoB << endl;
		cout << "\t" << student[i].classID << endl;
		cout << "\t" << student[i].status << endl;
	}
	delete[] student;
	system("pause");
}

void viewClasses() {
	int NumberOfClass = 0;
	Class* classes = nullptr;
	ifstream fin;
	fin.open("../../Class.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("Class.txt not found");
		return;
	}
	fin >> NumberOfClass;
	classes = new Class[NumberOfClass];
	for (int i = 0; i < NumberOfClass; i++) {
		getline(fin, classes[i].classID);
	}
	ClearPrintDelay();
	for (int i = 0; i < NumberOfClass; i++) {
		cout << "\t" << classes[i].classID << endl;
	}
	cout << endl;
	delete[] classes;
	system("pause");
}

void moveStudent(string filepath)
{
	string findingID;
	Student* student = nullptr;
	Student temp;
	int NumberOfStudent = 0;
	int i;
	ifstream fin1;
	fin1.open("../../" + filepath + "-Student.txt");
	if (!fin1.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	string anotherClass;
	cout << "\tTo class: ";
	getline(cin, anotherClass);

	ifstream fin2;
	fin2.open("../../" + anotherClass + "-Student.txt");
	if (!fin2.is_open()) {
		ClearPrintDelay("\n\tClass " + anotherClass + " not found");
		return;
	}
	cout << "\tEnter Student ID: ";
	getline(cin, findingID);
	fin1 >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (i = 0; i < NumberOfStudent; i++) {
		fin1.ignore();
		getline(fin1, student[i].id);
		getline(fin1, student[i].password);
		getline(fin1, student[i].name);
		getline(fin1, student[i].DoB);
		getline(fin1, student[i].classID);
		fin1 >> student[i].status;
	}
	fin1.close();

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
	}
	fout1.close();
	
	fin2 >> NumberOfStudent;
	NumberOfStudent = NumberOfStudent + 1;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent - 1; i++) {
		fin2.ignore();
		getline(fin2, student[i].id);
		getline(fin2, student[i].password);
		getline(fin2, student[i].name);
		getline(fin2, student[i].DoB);
		getline(fin2, student[i].classID);
		fin2 >> student[i].status;
	}
	fin2.close();
	student[NumberOfStudent - 1].id = temp.id;
	student[NumberOfStudent - 1].password = temp.password;
	student[NumberOfStudent - 1].name = temp.name;
	student[NumberOfStudent - 1].DoB = temp.DoB;
	student[NumberOfStudent - 1].classID = anotherClass;
	student[NumberOfStudent - 1].status = temp.status;
	
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
	}
	fout2.close();
	// change in Student.txt
	Student* studentArray;
	ifstream studenttxtIN;
	studenttxtIN.open("../../Student.txt");
	if (!studenttxtIN.is_open()) {
		ClearPrintDelay("\n\tStudent.txt not found");
		return;
	}
	int NumberOfStudents;
	studenttxtIN >> NumberOfStudents;
	studentArray = new Student[NumberOfStudents];
	for (int i = 0; i < NumberOfStudents; i++) {
		studenttxtIN.ignore();
		getline(studenttxtIN, studentArray[i].id);
		getline(studenttxtIN, studentArray[i].password);
		getline(studenttxtIN, studentArray[i].name);
		getline(studenttxtIN, studentArray[i].classID);
		studenttxtIN >> studentArray[i].status;
	}
	for (int i = 0; i < NumberOfStudents; i++) {
		if (temp.id == studentArray[i].id) {
			studentArray[i].id = temp.id;
			studentArray[i].password = temp.password;
			studentArray[i].name = temp.name;
			studentArray[i].classID = anotherClass;
			studentArray[i].status = temp.status;
			break;
		}
	}
	ofstream studenttxtOUT;
	studenttxtOUT.open("../../Student.txt");
	studenttxtOUT << NumberOfStudents << endl;
	for (int i = 0; i < NumberOfStudents; i++) {
		studenttxtOUT << studentArray[i].id << endl;
		studenttxtOUT << studentArray[i].password << endl;
		studenttxtOUT << studentArray[i].name << endl;
		studenttxtOUT << studentArray[i].classID << endl;
		studenttxtOUT << studentArray[i].status << endl;
	}
	studenttxtOUT.close();
	delete[] student;
	delete[] studentArray;
	ClearPrintDelay("\n\tMove successfully!");
}

void importStudent(ifstream& fin, Student& studentOut)
{
	string no;
	getline(fin, no, ',');
	getline(fin, studentOut.id, ',');
	getline(fin, studentOut.name, ',');
	getline(fin, studentOut.gender, ',');
	getline(fin, studentOut.DoB, ',');
	getline(fin, studentOut.classID, '\n');
}

void importCsv(string classID, string filePath)
{
	if (!isValidClass(classID)) {
		ClearPrintDelay("\n\tThe classID you enter not found!");
		return;
	}
	ifstream fin;
	Student* student = nullptr;
	standardPathFile(filePath);
	fin.open(filePath);
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + classID + " CSV file not found");
		return;
	}
	int count = 0;
	string firstline;
	getline(fin, firstline);
	while (fin.good()) {
		getline(fin, firstline);
		if (!firstline.length()) {
			break;
		}
		count++;
	}
	fin.close();
	student = new Student[count];
	fin.open(filePath);
	getline(fin, firstline);
	for (int i = 0; i < count; i++) {
		importStudent(fin, student[i]);
		student[i].status = 1;
		string S = student[i].DoB;
		S.erase(5,1);
		S.erase(2,1);
		student[i].password = S;
		S.insert(2, 1,' ');
		S.insert(5, 1,' ');
		student[i].DoB = S;
	}
	ofstream fout;
	fout.open("../../" + classID + "-Student.txt");
	fout << count << endl;
	for (int i = 0; i < count; i++) {
		fout << student[i].id << endl;
		fout << student[i].password << endl;
		fout << student[i].name << endl;
		fout << student[i].DoB << endl;
		fout << student[i].classID << endl;
		fout << student[i].status << endl;
	}

	Student* studentOut;
	ifstream in;
	ofstream out;
	in.open("../../Student.txt");
	int NumberOfStudent = 0;
	in >> NumberOfStudent;
	studentOut = new Student[NumberOfStudent];
	int temp = NumberOfStudent;
	for (int i = 0; i < NumberOfStudent; i++) {
		in.ignore();
		getline(in, studentOut[i].id);
		getline(in, studentOut[i].password);
		getline(in, studentOut[i].name);
		getline(in, studentOut[i].classID);
		in >> studentOut[i].status;
	}
	out.open("../../Student.txt");
	NumberOfStudent += count;
	out << NumberOfStudent << endl;
	for (int i = 0; i < temp; i++) {
		out << studentOut[i].id << endl;
		out << studentOut[i].password << endl;
		out << studentOut[i].name << endl;
		out << studentOut[i].classID << endl;
		out << studentOut[i].status << endl;
	}

	for (int i = 0; i < count; i++) {
		out << student[i].id << endl;
		out << student[i].password << endl;
		out << student[i].name << endl;
		out << student[i].classID << endl;
		out << student[i].status << endl;
	}
	in.close();
	out.close();
	fout.close();
	delete[] student;
	delete[] studentOut;
	fin.close();
	ClearPrintDelay("\n\tImport successfully!");
}

void changePassInClass(string filepath, string findingID, string newPassword) {
	int NumberOfStudent = 0;
	ifstream fin;
	Student* student = nullptr;
	fin.open("../../" + filepath + "-Student.txt");
	if (!fin.is_open()) {
		ClearPrintDelay("\n\tClass " + filepath + " not found");
		return;
	}
	fin >> NumberOfStudent;
	student = new Student[NumberOfStudent];
	for (int i = 0; i < NumberOfStudent; i++) {
		fin.ignore();
		getline(fin, student[i].id);
		getline(fin, student[i].password);
		getline(fin, student[i].name);
		getline(fin, student[i].DoB);
		getline(fin, student[i].classID);
		fin >> student[i].status;
	}
	fin.close();

	for (int i = 0; i < NumberOfStudent; i++) {
		if (findingID == student[i].id) {
			student[i].password = newPassword;
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
	}
	delete[] student;
	fout.close();
}

void classMenu()
{
	string classID;
	string csvFilePath;
	ClearPrintDelay();
	int choose;

	cout << "\n\t0. Back" << endl;
	cout << "\t1. Import Csv" << endl;
	cout << "\t2. Add new student" << endl;
	cout << "\t3. Edit a student" << endl;
	cout << "\t4. Remove a student" << endl;
	cout << "\t5. Move student from class A to B" << endl;
	cout << "\t6. View list of classes" << endl;
	cout << "\t7. View students of a class\n" << endl;
	cout << "\tEnter  your choice: ";
	cin >> choose;

	while (choose < 0 || choose > 7 || cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		ClearPrintDelay("\n\tYour choice is illegal. Try again.");
		cout << "\n\t0. Back" << endl;
		cout << "\t1. Import Csv" << endl;
		cout << "\t2. Add new student" << endl;
		cout << "\t3. Edit a student" << endl;
		cout << "\t4. Remove a student" << endl;
		cout << "\t5. Move student from class A to B" << endl;
		cout << "\t6. View list of classes" << endl;
		cout << "\t7. View students of a class\n" << endl;
		cout << "\tEnter  your choice: ";
		cin >> choose;
	}
	cout << endl;
	cin.ignore();
	ClearPrintDelay();
	switch (choose)
	{
	case 0:
		break;
	case 1:
		cout << "\n\tEnter classID: ";
		getline(cin, classID);
		cout << "\n\tEnter CSV path: ";
		getline(cin, csvFilePath);
		importCsv(classID, csvFilePath);
		break;
	case 2:
		cout << "\n\tEnter classID: ";
		getline(cin, classID);
		createStudent(classID);
		break;
	case 3:
		cout << "\n\tEnter classID: ";
		getline(cin, classID);
		editStudent(classID);
		break;
	case 4:
		cout << "\n\tEnter classID: ";
		getline(cin, classID);
		removeStudent(classID);
		break;
	case 5:
		cout << "\n\tFrom class: ";
		getline(cin, classID);
		moveStudent(classID);
		break;
	case 6:
		viewClasses();
		break;
	case 7:
		cout << "\n\tEnter classID: ";
		getline(cin, classID);
		viewStudents(classID);
		break;
	}
}