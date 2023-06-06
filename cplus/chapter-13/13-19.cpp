class Employee
{
public:
	Employee():unique_sn(sn++) {}
	Employee(const std::string &str):name(str),unique_sn(sn++) {}
	Employee(const Employee &rhs):name(rhs.name),unique_sn(sn++) {}
	Employee & operator=(const Employee &rhs) {name=rhs.name;return *this;}
	~Employee() {}
private:
	std::string name;
	unsigned unique_sn;
	static unsigned sn;
};
unsigned Employee::sn=0;
