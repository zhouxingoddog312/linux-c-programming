#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <iostream>
class Employee
{
	friend std::ostream & operator<<(std::ostream &,const Employee &);
	public:
		Employee()=default;
		Employee(std::string s):name(s){}
		Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
	private:
		std::string name;
		unsigned int Age=0;
		double salary=0;
		unsigned int Phone_Number=0;
};
std::ostream & operator<<(std::ostream &,const Employee &);
#endif
