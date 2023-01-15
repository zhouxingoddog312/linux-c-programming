#include <iostream>
#include <string>
struct Person
{
	std::string name;
	std::string address;
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
};
istream & read(istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
ostream & print(ostream &os,Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
