#include <iostream>
#include <bitset>
using namespace std;
void check(bitset<10> question,size_t index,bool answ)
{
	question.set(index,answ);
}
int main(void)
{
	char ch;
	bool answ;
	bitset<10> question,answer("1000100101");
	for(size_t i=0;i!=question.size();++i)
	{
		cout<<"Enter the answer of question "<<i<<": ";
		cin.get(ch);

		check(question,i,)
	}
}
