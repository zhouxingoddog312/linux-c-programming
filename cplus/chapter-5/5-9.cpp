#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	int cnt=0;
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')
			cnt++;
	}
	cout<<"cnt= "<<cnt<<"\n";
	return 0;
}
