[toc]
### 12.1
在此代码结尾，b1包含4个元素，b2超出作用范围，以销毁。
### 12.2
```
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlob
{
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
inline void StrBlob::check(size_type i,const string &msg) const
{
	if(i>=data->size())
		throw out_of_range(msg);
}
string &StrBlob::front()
{
	check(0,"front on empty StrBlob");
	return data->front();
}
string &StrBlob::back()
{
	check(0,"back on empty StrBlob");
	return data->back();
}
const std::string &StrBlob::front() const
{
	check(0,"front on empty StrBlob");
	return data->front();
}
const std::string &StrBlob::back() const
{
	check(0,"back on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back()
{
	check(0,"pop_back on empty StrBlob");
	data->pop_back();
}
```
### 12.3
不需要，因为const StrBlob对象的data数据成员是常量指针，而不是指向常量的指针，所以不管它是否是const，data所指向的vector都可以调用push_back和pop_back。
### 12.4
因为std::vector<std::string>::size_type是无符号类型，它的取值范围是0和正整数。
### 12.5
未编写接受初始化列表参数的显式函数，好处在于，在需要StrBlob的地方可以直接使用列表代替，并且可以直接使用列表对StrBlob对象进行拷贝形式的初始化。
坏处在于，对于接受StrBlob的函数，直接传递一个列表，则会生成一个StrBlob临时量。函数结束时，该临时量被销毁，有可能导致内存泄漏。
### 12.6
```
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
vector<int> *create()
{
	return new vector<int>();
}
vector<int> *scan(istream &is,vector<int> *pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(vector<int> *pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
	delete pivec;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
```
### 12.7
```
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
shared_ptr<vector<int>> create()
{
	return make_shared<vector<int>>();
}
shared_ptr<vector<int>> scan(istream &is,shared_ptr<vector<int>> pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(shared_ptr<vector<int>> pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
```
### 12.8
int型指针可以转换为bool，应该改为`int *p=new (nothrow) int;`这样的话，new分配内存成功时`return p;`会返回true，new分配内存失败时p的值为nullptr，`return p;`会返回false。
### 12.9
`int *q=new int(42),*r=new int(100);`int型指针q指向堆中动态分配的一个初始值为42的int型对象，int型指针r指向堆中动态分配的一个初始值为100的int型对象。
`r=q;`r指向与q相同的对象，而r原先指向的动态分配的内存将无法释放。
`auto q2=make_shared<int>(42),r2=make_shared<int>(100);`shared_ptr\<int\>类对象q2，指向堆中动态分配的一个初始值为42的int型对象。shared_ptr\<int\>类对象r2，指向堆中动态分配的一个初始值为100的int型对象。
`r2=q2;`r2指向与q2相同的对象，而r2的引用计数递减1，变为0，其原先指向的对象会自动释放。
### 12.10
正确，利用智能指针p创建一个临时量，再赋予process的形参ptr，这时候智能指针的引用计数变为2，在函数运行结束后，ptr被销毁，智能指针的引用计数变为1。
### 12.11
这样操作将另一个独立的智能指针也绑定到了get()返回的指针上，由于p和ptr是相互独立创建的，因此各自的引用计数都是1.当process函数结束时，ptr被销毁，这会导致ptr所指向的内存被释放，从而让p成为空悬指针。
### 12.12
- `process(sp)`合法，将智能指针sp赋予形参ptr，引用计数变为2，函数结束，ptr被销毁，引用计数变为1.
- `process(new int())`不合法，接受内置指针类型参数的智能指针构造函数是explicit的，所以无法将一个内置指针隐式转换为一个智能指针，而process函数需要接受一个智能指针参数。
- `process(p)`同上
- `process(shared_ptr<int>(p))`调用合法，但会导致p变为一个空悬指针。操作中利用内置指针p创建一个智能指针临时量赋予形参ptr，在process函数结束时，ptr被销毁，引用计数变为0，其指向的内存会被释放，同时p继续指向（已经释放的）内存。
### 12.13
这样会导致sp变成一个空悬指针，当我们试图使用sp时，将发生未定义的行为，而且当sp被销毁时，它所指向的内存会被第二次delete。
