#include <iostream>
int main()
{
	int val1,val2,tmp;
	std::cout<<"Enter two integer:";
	std::cin>>val1>>val2;
	if(val1<val2)
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	std::cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<std::endl;
	for(;val1>=val2;val1--)
		std::cout<<val1<<" ";
	std::cout<<std::endl;
	return 0;
}
