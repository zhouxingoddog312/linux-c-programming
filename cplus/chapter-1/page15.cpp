#include <iostream>
int main()
{
	int CurrVal=0,Val=0;
	if(std::cin>>CurrVal)
	{
		int cnt=1;
		while(std::cin>>Val)
		{
			if(CurrVal==Val)
				cnt++;
			else
			{
				std::cout<<CurrVal<<" occurs "<<cnt<<" times."<<std::endl;
				CurrVal=Val;
				cnt=1;
			}
		}
		std::cout<<CurrVal<<" occurs "<<cnt<<" time."<<std::endl;
	}
	return 0;
}
