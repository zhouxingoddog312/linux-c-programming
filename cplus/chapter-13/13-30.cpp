#include <iostream>
#include <string>
class HasPtr
{
	friend void swap(HasPtr &,HasPtr &);
	friend void print(const HasPtr &);
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.value,rhs.value);
	swap(lhs.pts,rhs.pts);
	std::cout<<"swap complete."<<std::endl;
}
void print(const HasPtr &hp)
{
	std::cout<<*hp.pts<<std::endl;
}
int main(void)
{
	HasPtr a("s1"),b("s2");
	swap(a,b);
	std::cout<<"a"<<std::endl;
	print(a);
	std::cout<<"b"<<std::endl;
	print(b);
	return 0;
}
