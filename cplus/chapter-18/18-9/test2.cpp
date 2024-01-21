#include <iostream>
#include "Sales_data.h"
int main(void)
{
	Sales_data a("111",2,30),b("112",3,50);
	try
	{
		a+b;
	}
	catch(const isbn_mismatch &e)
	{
		std::cerr<<e.what()<<": left isbn ("<<e.left<<") right isbn ("<<e.right<<")"<<std::endl;
	}
	return  0;
}
