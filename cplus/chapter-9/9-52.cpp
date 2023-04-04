#include <iostream>
#include <string>
#include <stack>
using namespace std;
//如果处理的是算式的话，还得考虑计算符号的优先级，比较麻烦，这里就简单的处理为将一对括号内的字符替换为*
int main(void)
{
	string examp="This is (Mooophy(awesome)((((wooooooooo))))) and (ocxs) over";
	char replace='*';
	unsigned left_bracket_count=0;
	stack<char> cstk;
	for(string::const_iterator ps=examp.cbegin();ps!=examp.cend();++ps)
	{
		cstk.push(*ps);
		if(*ps=='(')
			++left_bracket_count;
		if(*ps==')'&&left_bracket_count)
		{
			while(cstk.top()!='(')
				cstk.pop();
			cstk.pop();
			cstk.push(replace);
			--left_bracket_count;
		}
	}
	examp.clear();
	while(!cstk.empty())
	{
		examp.insert(examp.begin(),cstk.top());
		cstk.pop();
	}
	cout<<examp<<endl;
	return 0;
}
