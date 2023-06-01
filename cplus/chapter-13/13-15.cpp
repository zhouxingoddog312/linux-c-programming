#include <iostream>
unsigned idx=0;
class numbered
{
friend void f(numbered s);
public:
	numbered():mysn(idx++) {}
	numbered(const numbered &ori_num):mysn(idx++) {}
private:
	unsigned mysn=0;
};
using std::cout;
using std::endl;
void f(numbered s)
{
	cout<<s.mysn<<endl;
}
int main(void)
{
	numbered a,b=a,c=b;
	f(a);
	f(b);
	f(c);
	return 0;
}
