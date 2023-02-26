class Employee
{
public:
	Employee():Employee("",0,0,0){}
	Employee(std::string s):Employee(s,0,0,0){}
	Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
private:
	std::string name;
	unsigned int Age=0;
	double salary=0;
	unsigned int Phone_Number=0;
}
