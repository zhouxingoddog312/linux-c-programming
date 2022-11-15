#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<unsigned> scores(11,0);
	unsigned grade;
	auto beg=scores.begin();
	while(cin>>grade)
	{
		if(grade<=100)
			(*(beg+grade/10))++;
	}
	for(decltype(scores.size())index=0;index!=scores.size();index++)
	{
		if(index<scores.size()-1)
			cout<<scores[index]<<" ";
		else
			cout<<scores[index]<<endl;
	}
	return 0;
}
