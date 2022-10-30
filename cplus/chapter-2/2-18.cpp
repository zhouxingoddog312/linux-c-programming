#include <iostream>
int main()
{
	int *ptr,a;
	//更改指针的值
	ptr=nullptr;
	ptr=&a;
	//更改指针所指对象的值
	*ptr=3;
	std::cout<<"a="<<a<<std::endl;
	return 0;
}
