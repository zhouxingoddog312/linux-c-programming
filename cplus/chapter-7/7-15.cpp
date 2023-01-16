#include <iostream>
#include <string>
struct Person
{
	std::string name;
	std::string address;
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
	Person()=default;
	Person(const std::string &s):name(s){}
	Person(const std::string &s1,const std::string &s2):name{s1},address{s2}{}
	Person(std::istream &is);
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
Person::Person(std::istream &is)
{
	read(is,*this);
}
