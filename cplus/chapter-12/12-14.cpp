#include <iostream>
#include <memory>
using namespace std;
struct destination{};
struct connection{};
connection connect(destination *d)
{
	cout<<"打开连接"<<endl;
	return connection();
}
void disconnect(connection c)
{
	cout<<"关闭连接"<<endl;
}
void end_connection(connection *pc)
{
	disconnect(*pc);
}
void f1(destination &d)
{
	cout<<"f1开始"<<endl;
	connection c=connect(&d);
	cout<<"f1结束"<<endl;
}
void f2(destination &d)
{
	cout<<"f2开始"<<endl;
	connection c=connect(&d);
	shared_ptr<connection> p(&c,end_connection);
	cout<<"f2结束"<<endl;
}
int main(void)
{
	destination d;
	f1(d);
	f2(d);
	return 0;
}
