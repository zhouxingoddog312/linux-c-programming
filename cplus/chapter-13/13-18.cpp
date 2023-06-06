class Employee
{
public:
	Employee():unique_sn(sn++) {}
	Employee(const std::string &str):name(str),unique_sn(sn++) {}
private:
	std::string name;
	unsigned unique_sn;
	static unsigned sn;
};
unsigned Employee::sn=0;
