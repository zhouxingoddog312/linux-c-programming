#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
class Foo
{
	public:
		Foo sorted() &&;
		Foo sorted() const &;
	private:
		std::vector<int> data;
};
Foo Foo::sorted() &&
{
	std::cout<<"右值引用版本"<<std::endl;
	sort(data.begin(),data.end());
	return *this;
}
#ifdef _A
Foo Foo::sorted() const &
{
	std::cout<<"左值引用版本"<<std::endl;
	Foo ret(*this);
	return ret.sorted();
}
#else
Foo Foo::sorted() const &
{
	std::cout<<"左值引用版本"<<std::endl;
	return Foo(*this).sorted();
}
#endif
int main(void)
{
	Foo a;
	a.sorted();
	return 0;
}
