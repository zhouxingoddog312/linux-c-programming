#include <iostream>
int main()
{
	int i=0,&r=i;
	const int ci=i,&cr=ci;
	auto a=r;
	std::cout<<"a="<<a<<std::endl;
	a=42;
	std::cout<<"a="<<a<<std::endl;
	auto b=ci;
	std::cout<<"b="<<b<<std::endl;
	b=42;
	std::cout<<"b="<<b<<std::endl;
	auto c=cr;
	std::cout<<"c="<<c<<std::endl;
	c=42;
	std::cout<<"c="<<c<<std::endl;
	auto d=&i;
	std::cout<<"d="<<d<<std::endl;
	d=42;
	std::cout<<"d="<<d<<std::endl;
	auto e=&ci;
	std::cout<<"e="<<e<<std::endl;
	e=42;
	std::cout<<"e="<<e<<std::endl;
	auto &g=ci;
	std::cout<<"g="<<g<<std::endl;
	g=42;
	std::cout<<"g="<<g<<std::endl;
	return 0;
}
