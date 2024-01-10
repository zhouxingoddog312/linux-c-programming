#include <iostream>
#include <bitset>
using namespace std;
void check(bitset<10> &question,size_t index,bool answ)
{
	question.set(index,answ);
}
int main(void)
{
	char ch;
	bool answ;
	bitset<10> question,grade,answer("1000100101");
	for(size_t i=0;i!=question.size();++i)
	{
		cout<<"Enter the answer of question "<<i<<": ";
		cin.get(ch);
		if(ch=='1'||ch=='y'||ch=='Y')
			answ=1;
		else
			answ=0;
		check(question,i,answ);
	}
	cout<<"question is:"<<question<<endl;
	grade=~(question^answer);
	cout<<"grade is:"<<grade<<endl;
	cout<<"一共得了（分）："<<grade.count()<<endl;
	return 0;
}
