#include <iostream>
#include <fstream>
int main(int argc,char *argv[])
{
	std::ifstream in(argv[1]);
	char *str=new char[100];
	while(in.getline(str,100,'\n'))
	{
		std::cout.write(str,in.gcount());
		std::cout<<'\n';
	}
	delete [] str;
}
