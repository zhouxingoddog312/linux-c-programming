#include "Employee.h"
std::ostream & operator<<(std::ostream &os,const Employee &src)
{
	os<<src.name<<" "<<src.Age<<" "<<src.salary<<" "<<src.Phone_Number;
	return os;
}
