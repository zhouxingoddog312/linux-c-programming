#include "Employee.h"
Employee & Employee::operator=(const Employee &rhs)
{
	name=rhs.name;
	Age=rhs.Age;
	salary=rhs.salary;
	Phone_Number=rhs.Phone_Number;
	return *this;
}
Employee & Employee::operator=(Employee &&rhs)
{
	if(this!=&rhs)
	{
		name=std::move(rhs.name);
		Age=rhs.Age;
		salary=rhs.salary;
		Phone_Number=rhs.Phone_Number;
	}
	return *this;
}
Employee & Employee::operator=(const std::string &str)
{
	name=str;
	return *this;
}
std::ostream & operator<<(std::ostream &os,const Employee &src)
{
	os<<src.name<<" "<<src.Age<<" "<<src.salary<<" "<<src.Phone_Number;
	return os;
}
std::istream & operator>>(std::istream &is,Employee &src)
{
	is>>src.name>>src.Age>>src.salary>>src.Phone_Number;
	if(!is)
		src=Employee();
	return is;
}
bool operator==(const Employee &lhs,const Employee &rhs)
{
	return lhs.name==rhs.name&&lhs.Age==rhs.Age&&lhs.salary==rhs.salary&&lhs.Phone_Number==rhs.Phone_Number;
}
bool operator!=(const Employee &lhs,const Employee &rhs)
{
	return !(lhs==rhs);
}
