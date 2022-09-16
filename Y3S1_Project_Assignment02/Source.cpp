// Jacob Brooker
// CSCN 73030
// September 16, 2022

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#ifdef _DEBUG
	#define PRINTSTUDENTNAMES(student_vec)for(STUDENT_DATA student: (student_vec)){printStudent(student);}
#endif

//#define PRERELEASE

#ifndef PRERELEASE
typedef struct student_data {
	std::string first_name;
	std::string last_name;
}STUDENT_DATA, *PSTUDENT_DATA;

void printStudent(const STUDENT_DATA& student)
{
	std::cout << "Student: " << student.first_name << "," << student.last_name << std::endl;
}

STUDENT_DATA createStudent(const std::string& firstname, const std::string& lastname)
{
	STUDENT_DATA stud;
	stud.first_name = firstname;
	stud.last_name = lastname;
	return stud;
}

std::vector<STUDENT_DATA> loadStudents() {
	std::vector<STUDENT_DATA> student_data;

	std::ifstream myfile("StudentData.txt");

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			std::string data;
			getline(myfile, data);
			std::stringstream student(data);
			std::string first_name;
			std::string last_name;
			getline(student, last_name, ',');
			getline(student, first_name);
			student_data.push_back(createStudent(first_name, last_name));
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	return student_data;
}

#elif defined(PRERELEASE)

typedef struct student_data {
	std::string first_name;
	std::string last_name;
	std::string email;
}STUDENT_DATA, * PSTUDENT_DATA;

STUDENT_DATA createStudent(const std::string& firstname, const std::string& lastname, const std::string& email)
{
	STUDENT_DATA stud;
	stud.first_name = firstname;
	stud.last_name = lastname;
	stud.email = email;
	return stud;
}

void printStudent(const STUDENT_DATA& student)
{
	// just need to figure out the print when defined PRERELEASE
	std::cout << "Student: " << student.first_name << "," << student.last_name << " ";
	std::cout << student.email;
	std::cout << std::endl;
}

std::vector<STUDENT_DATA> loadStudents() {
	std::vector<STUDENT_DATA> student_data;
	
	std::ifstream myfile("StudentData_Emails.txt");

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			std::string data;
			getline(myfile, data);
			std::stringstream student(data);
			std::string first_name;
			std::string last_name;
			getline(student, last_name, ',');
			getline(student, first_name,',');
			std::string email;
			getline(student, email);
			student_data.push_back(createStudent(first_name, last_name, email));
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	return student_data;
}
#endif

int main() {
	const std::vector<STUDENT_DATA> student_data = loadStudents();

#ifdef PRERELEASE
	std::cout << "Executing in PreRelease mode..." << std::endl;
#endif

#ifndef _DEBUG
	std::cout << "Executing in Release mode..." << std::endl;
#elif _DEBUG
	PRINTSTUDENTNAMES(student_data)
#endif

	return 1;
}