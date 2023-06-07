#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class HasPtr
{
	friend void swap(HasPtr &,HasPtr &);
	friend std::ostream & print(std::ostream &,const HasPtr &);
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		bool operator<(const HasPtr &rhs) const {return *pts<*rhs.pts;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
inline void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.value,rhs.value);
	swap(lhs.pts,rhs.pts);
	std::cout<<"swap complete."<<std::endl;
}
std::ostream & print(std::ostream &os,const HasPtr &hp)
{
	os<<*hp.pts<<std::endl;
	return os;
}
using std::vector;
using std::cout;
using std::string;
int main(void)
{
	vector<HasPtr> hpv;
	string s="z y x a c d e f i h j k o q p r t s n m l";
	for(auto str:s)
		hpv.push_back(HasPtr(string("")+str));
	for(auto pv:hpv)
		print(cout,pv);
	sort(hpv.begin(),hpv.end());
	for(auto pv:hpv)
		print(cout,pv);
	return 0;
}
