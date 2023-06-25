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
		HasPtr(HasPtr &&org) noexcept :value(org.value),pts(org.pts) {org.pts=nullptr;}
		HasPtr & operator=(HasPtr rhs) {swap(*this,rhs);return *this;}
		HasPtr & operator=(HasPtr &&rhs) noexcept;
		bool operator<(const HasPtr &rhs) const {return *pts<*rhs.pts;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
inline HasPtr & HasPtr::operator=(HasPtr &&rhs) noexcept
{
	if(this!=&rhs)
	{
		delete pts;
		pts=rhs.pts;
		value=rhs.value;
		rhs.pts=nullptr;
	}
	return *this;
}
inline void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.value,rhs.value);
	swap(lhs.pts,rhs.pts);
}
std::ostream & print(std::ostream &os,const HasPtr &hp)
{
	os<<*hp.pts<<std::endl;
	return os;
}
int main(void)
{
    HasPtr h("hi mom!");
    HasPtr h2(h);
    HasPtr h3 = h;
    h2 = h3;
    h2 = std::move(h3);
    return 0;
}
