#include <iostream>
#include <string>
class Person
{
	friend std::istream & read(std::istream &is,Person &rp);
	friend std::ostream & print(std::ostream &os,const Person &rp);
private:
	std::string name;
	std::string address;
public:
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
	Person()=default;
	explicit Person(const std::string &s):name(s){}
	Person(const std::string &s1,const std::string &s2):name{s1},address{s2}{}
	explicit Person(std::istream &is);
};
std::istream & read(std::istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
std::ostream & print(std::ostream &os,const Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
Person::Person(std::istream &is)
{
	read(is,*this);
}
