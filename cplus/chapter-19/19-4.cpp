#include <iostream>
#include <memory>
class A
{
	public:
		A()=default;
		virtual ~A()=default;
};
class B:public A
{
	public:
		B()=default;
		virtual ~B()=default;
};
class C:public B
{
	public:
		C()=default;
		virtual ~C()=default;
};
class D:public B,public A
{
	public:
		D()=default;
		virtual  ~D()=default;
};
int main(void)
{
//运行时会抛出错误
	A *pa=new A;
	try
	{
		C &rc=dynamic_cast<C &>(*pa);
	}
	catch(std::bad_cast err)
	{
		std::cerr<<err.what()<<std::endl;
	}
	return 0;
}
