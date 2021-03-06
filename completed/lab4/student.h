#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>
using namespace std;
const static double minGpaForHonor = 3.5;

class Student
{
public:
    Student();
    Student(const char initId[], double initGPA);
	bool isLessThanByID(const Student& aStudent) const;
	bool qualifyForHonor(double &) const;
	void print()const;
private:
    const static int MAX_CHAR = 100;
	char 	id[MAX_CHAR];
	double	gpa;
    //TRY TO PUT MINGPA AND MAXCHAR BACK IN HERE
};
#endif
