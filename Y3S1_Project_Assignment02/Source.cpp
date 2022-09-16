#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

typedef struct student_data {
	std::string first_name;
	std::string last_name;
}STUDENT_DATA, *PSTUDENT_DATA;

STUDENT_DATA createStudent(std::string firstname, std::string lastname)
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
			getline(student, first_name, ',');
			getline(student, last_name);
			student_data.push_back(createStudent(first_name, last_name));
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	return student_data;
}

int main() {
	std::vector<STUDENT_DATA> student_data = loadStudents();

#ifdef _DEBUG
	for(STUDENT_DATA i: student_data)
	{
		std::cout << "Student: " << i.first_name << "," << i.last_name << std::endl;
	}
#endif


	return 1;
}