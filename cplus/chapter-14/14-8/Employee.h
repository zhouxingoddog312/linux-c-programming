#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <iostream>
class Employee
{
	friend std::ostream & operator<<(std::ostream &,const Employee &);
	friend std::istream & operator>>(std::istream &,Employee &);
	friend bool operator==(const Employee &,const Employee &);
	friend bool operator!=(const Employee &,const Employee &);
	public:
		Employee()=default;
		Employee(std::string s):name(s){}
		Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
		Employee & operator=(const Employee &);
		Employee & operator=(Employee &&);
		Employee & operator=(const std::string &);
	private:
		std::string name;
		unsigned int Age=0;
		double salary=0;
		unsigned int Phone_Number=0;
};
std::ostream & operator<<(std::ostream &,const Employee &);
std::istream & operator>>(std::istream &,Employee &);
bool operator==(const Employee &,const Employee &);
bool operator!=(const Employee &,const Employee &);
#endif
