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
//	A *pa=new C;
//	B *pb=dynamic_cast<B *>(pa);
	B *pb=new B;
	if(C *pc=dynamic_cast<C *>(pb))
		std::cout<<"yes"<<std::endl;
	else
		std::cout<<"no"<<std::endl;
//	A *pa=new D;
//	B *pb=dynamic_cast<B *>(pa);
	return 0;
}
