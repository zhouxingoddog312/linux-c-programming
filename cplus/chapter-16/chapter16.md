[toc]

### 16.1
使用模板实参代替模板参数来创建出模板的一个特定实例，即是实例化。
### 16.2
```c++
#include <cstring>
template <typename T> int compare(const T &v1,const T&v2)
{
	if(v1<v2)
		return -1;
	if(v2<v1)
		return 1;
	return 0;
}
template <unsigned M,unsigned N> int compare(const char (&p1)[M],const char (&p2)[N])
{
	return strcmp(p1,p2);
}
#include <iostream>
int main(void)
{
	std::cout<<compare(1,0)<<std::endl;
	std::cout<<compare("hi","hello")<<std::endl;
	return 0;
}
```
### 16.3
为什么能编译通过？
```
#include <cstring>
template <typename T> int compare(const T &v1,const T&v2)
{
	if(v1<v2)
		return -1;
	if(v2<v1)
		return 1;
	return 0;
}
template <unsigned M,unsigned N> int compare(const char (&p1)[M],const char (&p2)[N])
{
	return strcmp(p1,p2);
}
#include <iostream>
#include "./Sales_data.h"
int main(void)
{
	Sales_data s1("100-11",2,30),s2("100-12",5,20);
	std::cout<<s1<<std::endl;
	std::cout<<s2<<std::endl;
	std::cout<<compare(s1,s2)<<std::endl;
	return 0;
}
```
### 16.4
```
template <typename ITER,typename VAL> ITER find_hb(ITER beg,ITER end,const VAL &val)
{
	while(beg!=end)
	{
		if(*beg!=val)
			++beg;
		else
			break;
	}
	return beg;
}
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	vector<int> ivec{1,2,3,4,5};
	list<string> slist{"hi","hello","hei"};
	auto a=find_hb(ivec.begin(),ivec.end(),3);
	auto b=find_hb(slist.begin(),slist.end(),"hi");
	cout<<*a<<endl;
	cout<<*b<<endl;
	return 0;
}
```
### 16.5
```
#include <iostream>
template <unsigned N,typename T> void print(T (&arr)[N])
{
	for(const T &elem:arr)
		std::cout<<elem<<std::endl;
}
#include <string>
using std::string;
int main(void)
{
	string a[]={"hi","hello","hei"};
	print(a);
	return 0;
}
```
### 16.6
```
template <typename T,unsigned L> T* begin(const T (&arr)[L])
{
	return arr;
}
template <typename T,unsigned L> T* end(const T (&arr)[L])
{
	return arr+L;
}
#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string arr[]={"hi","hello","hei"};
	for(auto p=begin(arr);p!=end(arr);++p)
		cout<<*p<<endl;
	return 0;
}
```
### 16.7
`template <typename T,unsigned L> constexpr L length(const T (&arr)[L]){return L;}`
### 16.8
所有标准库容器都定义了==和!=运算符，但其中只有少数定义了<运算符。因此，尽量使用!=而不是<，可减少你的算法适用容器的限制。
### 16.9
函数模板和类模板都是用模版实参代替模板参数来生成相对应的函数和类的蓝图。
### 16.10
当一个类模板被实例化时，显示模板实参会被绑定到模板参数，编译器使用这些模板实参来实例化出特定的类。
### 16.11
```
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
	List();
	List(const List &);
	List & operator=(const List &);
	~List();
	void insert()(ListItem<elemType> *ptr,elemType value);
private:
	ListItem<elemType> *front,*end;
};
```
### 16.12
==Blob.h==
```
#ifndef BLOB_H
#define BLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
template <typename> class BlobPtr;
template <typename> class Blob;
//Blob
template <typename T> bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &,const Blob<T> &);
template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator!=<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator< <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator<= <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator> <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator>= <T>(const Blob<T> &,const Blob<T> &);
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		Blob():data(std::make_shared<std::vector<T>>()){}
		Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}
		Blob(const Blob &org):data(std::make_shared<std::vector<T>>(*org.data)){}
		Blob &operator=(const Blob &);
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		size_type size() const {return data->size();}
		bool empty() const {return data->empty;}
		void push_back(const T &t){data->push_back(t);}
		void push_back(T &&t){data->push_back(std::move(t));}
		void pop_back();
		T & front();
		T & back();
		const T & front() const;
		const T & back() const;
		BlobPtr<T> begin();
		BlobPtr<T> end();
	private:
		std::shared_ptr<std::vector<T>> data;
		void check(size_type i,const std::string &msg) const;
};
//BlobPtr
template <typename T> bool operator==(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> class BlobPtr
{
	friend bool operator==<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator!=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator< <T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator<=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator><T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator>=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	public:
		typedef typename std::vector<T>::size_type size_type;
		BlobPtr():curr(0){}
		BlobPtr(const Blob<T> &blob,size_type sz=0):wptr(blob.data),curr(sz){}
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		BlobPtr & operator++();
		BlobPtr & operator++(int);
		BlobPtr & operator--();
		BlobPtr & operator--(int);
		BlobPtr operator+(size_type) const;
		BlobPtr operator-(size_type) const;
		BlobPtr operator+=(size_type) const;
		BlobPtr operator-=(size_type) const;
		T & operator*() const;
		T * operator->() const;
	private:
		std::shared_ptr<std::vector<T>> check(size_type i,const std::string &msg) const;
		std::weak_ptr<std::vector<T>> wptr;
		size_type curr=0;
};
//Blob
template <typename T> Blob<T> & Blob<T>::operator=(const Blob &rhs)
{
	data=std::make_shared<std::vector<T>>(*rhs.data);
	return *this;
}
template <typename T> T & Blob<T>::operator[](size_type i)
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> const T & Blob<T>::operator[](size_type i) const
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> void Blob<T>::pop_back()
{
	check(0,"pop_back on empty Blob");
	data->pop_back();
}
template <typename T> T & Blob<T>::front()
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> const T & Blob<T>::front() const
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> T & Blob<T>::back()
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> const T & Blob<T>::back() const
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr<T>(*this);
}
template <typename T> BlobPtr<T> Blob<T>::end()
{
	return BlobPtr<T>(*this,data->size());
}
template <typename T> inline void Blob<T>::check(size_type i,const string &msg) const
{
	if(i>=data->size())
		throw std::out_of_range(msg);
}
template <typename T> bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data==*rhs.data;
}
template <typename T> bool operator!=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data<*rhs.data;
}
template <typename T> bool operator<=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data>*rhs.data;
}
template <typename T> bool operator>=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs<rhs);
}
//BlobPtr
template <typename T> std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string &msg) const
{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound BlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
template <typename T> T & BlobPtr<T>::operator[](size_type i)
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> const T & BlobPtr<T>::operator[](size_type i) const
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++()
{
	check(curr,"increment past end of BlobPtr");
	++curr;
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++(int)
{
	BlobPtr ret=*this;
	++*this;
	return ret;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--()
{
	--curr;
	check(curr,"decrement past the begin of BlobPtr");
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--(int)
{
	BlobPtr ret=*this;
	--*this;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+(size_type i) const
{
	BlobPtr ret(*this);
	ret+=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-(size_type i) const
{
	BlobPtr ret(*this);
	ret-=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+=(size_type i) const
{
	check(curr+i,"increment past end of range");
	while(--i)
		++*this;
	return *this;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-=(size_type i) const
{
	check(curr-i,"decrement past begin of range");
	while(--i)
		--*this;
	return *this;
}
template <typename T> T & BlobPtr<T>::operator*() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
template <typename T> T * BlobPtr<T>::operator->() const
{
	return & this->operator*();
}
template <typename T> bool operator==(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r)
		return (!r||lhs.curr==rhs.curr);
	else
		return false;
}
template <typename T> bool operator!=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r&&l)
		return lhs.curr<rhs.curr;
	else
		return false;
}
template <typename T> bool operator<=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator>=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs<rhs);
}
#endif
```
### 16.13
一对一友好关系
### 16.14
==Screen.h==
```
#ifndef SCREEN_H
#define SCREEN_H
#include <string>
using pos=std::string::size_type;
template <pos H,pos W> class Screen
{
	public:
		Screen():contents(H*W,' '){}
		Screen(char c,pos s=0):contents(H*W,c),cursor(s){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const {pos row=(r-1)*W;return contents[row+c-1];}
		Screen &move(pos r,pos c){pos row=(r-1)*W;cursor=row+c-1;return *this;}
		Screen &set(char c){contents[cursor]=c;return *this;}
		Screen &set(pos r,pos c,char ch){contents[(r-1)*W+c-1]=ch;return *this;}
		Screen &display(std::ostream &os){do_display(os);return *this;}
		const Screen &display(std::ostream &os) const {do_display(os);return *this;}
	private:
		pos cursor=0,height=H,width=W;
		std::string contents;
		void do_display(std::ostream &os) const {os<<contents;}
};
#endif
```
==Screen_test.cpp==
```
#include <iostream>
#include "Screen.h"
int main() {
    Screen<3, 3> screen('x');
    screen.display(std::cout);
    std::cout<<std::endl;
    screen.set(2, 2, 'o');
    screen.display(std::cout);
    std::cout<<std::endl;
    return 0;
}
```
### 16.15
==Screen.h==
```
#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <string>
using pos=std::string::size_type;
template <pos H,pos W> class Screen;
template <pos H,pos W> std::istream & operator>>(std::istream &is,Screen<H,W> &screen);
template <pos H,pos W> std::ostream & operator<<(std::ostream &os,Screen<H,W> &screen);
template <pos H,pos W> class Screen
{
	friend std::istream & operator>><H,W>(std::istream &is,Screen<H,W> &screen);
	friend std::ostream & operator<<<H,W>(std::ostream &os,Screen<H,W> &screen);
	public:
		Screen():contents(H*W,' '){}
		Screen(char c,pos s=0):contents(H*W,c),cursor(s){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const {pos row=(r-1)*W;return contents[row+c-1];}
		Screen &move(pos r,pos c){pos row=(r-1)*W;cursor=row+c-1;return *this;}
		Screen &set(char c){contents[cursor]=c;return *this;}
		Screen &set(pos r,pos c,char ch){contents[(r-1)*W+c-1]=ch;return *this;}
	private:
		pos cursor=0,height=H,width=W;
		std::string contents;
};
template <pos H,pos W> std::istream & operator>>(std::istream &is,Screen<H,W> &screen)
{
	std::string tmp;
	is>>tmp;
	for(auto b1=tmp.begin(),b2=screen.contents.begin();b1!=tmp.end()&&b2!=screen.contents.end();++b1,++b2)
		*b2=*b1;
	return is;
}
template <pos H,pos W> std::ostream & operator<<(std::ostream &os,Screen<H,W> &screen)
{
	os<<screen.contents;
	return os;
}
#endif
```
==Screen_test.cpp==
```
#include <iostream>
#include "Screen.h"
int main() {
    Screen<3, 3> screen('x');
    std::cout<<screen;
    std::cout<<std::endl;
    screen.set(2, 2, 'o');
    std::cout<<screen;
    std::cout<<std::endl;
    std::cin>>screen;
    std::cout<<screen;
    std::cout<<std::endl;
    return 0;
}
```
### 16.16
==Vec.h==
```
#ifndef _VEC_H
#define _VEC_H
#include <memory>
#include <utility>
#include <algorithm>
template <typename> class Vec;
template <typename T> bool operator==(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator!=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator<(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator<=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator>(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator>=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> class Vec
{
	friend bool operator==<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator!=<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator< <T>(const Vec &lhs,const Vec &rhs);
	friend bool operator<=<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator> <T>(const Vec &lhs,const Vec &rhs);
	friend bool operator>=<T>(const Vec &lhs,const Vec &rhs);
	public:
		Vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
		Vec(const Vec &org)
		{
			std::pair<T *,T *> data=alloc_n_copy(org.begin(),org.end());
			elements=data.first;
			first_free=cap=data.second;
		}
		Vec & operator=(const Vec &org)
		{
			auto data=alloc_n_copy(org.begin(),org.end());
			free();
			elements=data.first;
			first_free=cap=data.second;
			return *this;
		}
		T & operator[](std::size_t i) {return elements[i];}
		const T & operator[](std::size_t i) const {return elements[i];}
		~Vec() {free();}
		void push_back(const T &elem)
		{
			chk_n_alloc();
			alloc.construct(first_free++,elem);
		}
		std::size_t size() const {return first_free-elements;}
		std::size_t capacity() {return cap-elements;}
		T *begin() const {return elements;}
		T *end() const {return first_free;}
		void resize(const std::size_t n,const T &orgv);
		void reserve(const std::size_t n);
	private:
		T *elements;
		T *first_free;
		T *cap;
		static std::allocator<T> alloc;
		void chk_n_alloc() {if(size()==capacity()) reallocate();}
		std::pair<T *,T *> alloc_n_copy(const T *,const T *);
		void free();
		void reallocate();
};
//implementation
template <typename T> std::allocator<T> Vec<T>::alloc;
template <typename T> std::pair<T *,T *> Vec<T>::alloc_n_copy(const T *b,const T *e)
{
	T *data=alloc.allocate(e-b);
	return {data,uninitialized_copy(b,e,data)};
}
template <typename T> void Vec<T>::reallocate()
{
	std::size_t newcapacity=size()?size()*2:1;
	T *newdata=alloc.allocate(newcapacity);
	T *dest=newdata;
	T *src=elements;
	for(std::size_t i=0;i!=size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	elements=newdata;
	first_free=dest;
	cap=elements+newcapacity;
}
template <typename T> void Vec<T>::free()
{
	if(elements)
	{
		for(auto p=first_free;p!=elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements,cap-elements);
	}
}
template <typename T> void Vec<T>::reserve(const std::size_t n)
{
	if(n>capacity())
	{
		T *newdata=alloc.allocate(n);
		T *dest=newdata;
		T *src=elements;
		for(std::size_t i=0;i!=size();++i)
			alloc.construct(dest++,std::move(*src++));
		free();
		elements=newdata;
		first_free=dest;
		cap=elements+n;
	}
}
template <typename T> void Vec<T>::resize(const std::size_t n,const T &orgv)
{
	if(n<=size())
	{
		T *b=elements+n;
		T *e=first_free;
		while(b!=e)
			alloc.destroy(b++);
		first_free=elements+n;
	}
	else if(n<=capacity())
	{
		T *b=first_free;
		T *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
	else
	{
		reserve(n);
		T *b=first_free;
		T *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
}
template <typename T> bool operator==(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return (lhs.size()==rhs.size())&&std::equal(lhs.begin(),lhs.end(),rhs.begin());
}
template <typename T> bool operator!=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}
template <typename T> bool operator>=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs<rhs);
}
template <typename T> bool operator>(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator<=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs>rhs);
}
#endif
```
==test.cpp==
```
#include "Vec.h"
#include <string>
#include <iostream>
using std::string;
using std::cin; using std::cout; using std::endl;
using std::istream;
void print(const Vec<string> &svec)
{
    for (string *it = svec.begin(); it != svec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}
Vec<string> getVec(istream &is)
{
    Vec<string> svec;
    string s;
    while (is >> s)
        svec.push_back(s);
    return svec;
}
int main()
{
    Vec<string> svec = getVec(cin);
    print(svec);
    cout << "copy " << svec.size() << endl;
    Vec<string> svec2 = svec;
    print(svec2);
    cout << "assign" << endl;
    Vec<string> svec3;
    svec3 = svec2;
    print(svec3);
    cout << "----- end -----"<<endl;
    return 0;
}
```
### 16.17
其余时候的含义都一样，只有在我们希望通知编译器一个名字表示类型时，必须使用typename，而不能使用class。
### 16.18
- 非法，未指出U是类型参数还是非类型参数`template <typename T,typename U,typename V> void f1(T,U,V)`
- 非法，在模板内不能重用模板参数名`template <typename T> T f2(int &i)`
- 非法，inline说明符应该在模板参数列表之后`template <typename T> inline T foo(T,unsigned int *)`
- 非法，没有函数返回类型`template <typename T> T f4(T,T)`
- 合法。
### 16.19
```
#include <iostream>
#include <vector>
template <typename T> void print(T &arr)
{
	for(typename T::size_type index=0;index!=arr.size();++index)
		std::cout<<arr[index]<<" ";
	std::cout<<std::endl;
}
int main(void)
{
	std::vector<int> ivec={2,4,6,8};
	print(ivec);
	return 0;
}
```
### 16.20
```
#include <iostream>
#include <vector>
template <typename T> void print(T &arr)
{
	for(auto it=arr.begin();it!=arr.end();++it)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
int main(void)
{
	std::vector<int> ivec={2,4,6,8};
	print(ivec);
	return 0;
}
```
### 16.21
```
class DebugDelete
{
	public:
		DebugDelete(std::ostream &s=std::cerr):os(s) {}
		template <typename T> void operator(T *p) const {os<<"deleting unique_ptr"<<std::endl;delete p;}
	private:
		std::ostream &os;
};
```
### 16.22
只写出几个有变动的文件
==DebugDelete.h==
```
#ifndef _DEBUGDELETE_H
#define _DEBUGDELETE_H
class DebugDelete
{
	public:
		DebugDelete(std::ostream &s=std::cerr):os(s) {}
		template <typename T> void operator()(T *p) const {os<<"deleting unique_ptr"<<std::endl;delete p;}
	private:
		std::ostream &os;
};
#endif
```
==TextQuery.cpp==
```
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include "TextQuery.h"
#include "DebugDelete.h"
using namespace std;
TextQuery::TextQuery(ifstream &infile):file(new vector<string>,DebugDelete())
{
	string text;
	while(getline(infile,text))
	{
		file->push_back(text);
		size_t line_number=file->size()-1;
		istringstream line(text);
		string word;
		while(line>>word)
		{
			shared_ptr<set<line_no>> &lines=wm[word];
			if(!lines)
				lines.reset(new set<line_no>);
			lines->insert(line_number);
		}
	}
}
QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}
```
==16-22.cpp==
```
#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"
using namespace std;
void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	while(true)
	{
		cout<<"enter word to look for, or q to quit:";
		string s;
		if(!(cin>>s)||s=="q")
			break;
		print(cout,tq.query(s))<<endl;
	}
}
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	runQueries(infile);
	return 0;
}
```
### 16.23
runQueries函数结束时，TextQuery对象生命期结束，此时会调用其析构函数，析构函数会调用DebugDelete函数对象。
### 16.24
==Blob.h==
```
#ifndef BLOB_H
#define BLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
template <typename> class BlobPtr;
template <typename> class Blob;
//Blob
template <typename T> bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &,const Blob<T> &);
template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator!=<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator< <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator<= <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator> <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator>= <T>(const Blob<T> &,const Blob<T> &);
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		Blob():data(std::make_shared<std::vector<T>>()){}
		Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}
		Blob(const Blob &org):data(std::make_shared<std::vector<T>>(*org.data)){}
		template <typename it> Blob(it b,it e):data(std::make_shared<std::vector<T>>(b,e)) {}
		Blob &operator=(const Blob &);
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		size_type size() const {return data->size();}
		bool empty() const {return data->empty;}
		void push_back(const T &t){data->push_back(t);}
		void push_back(T &&t){data->push_back(std::move(t));}
		void pop_back();
		T & front();
		T & back();
		const T & front() const;
		const T & back() const;
		BlobPtr<T> begin();
		BlobPtr<T> end();
	private:
		std::shared_ptr<std::vector<T>> data;
		void check(size_type i,const std::string &msg) const;
};
//BlobPtr
template <typename T> bool operator==(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> class BlobPtr
{
	friend bool operator==<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator!=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator< <T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator<=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator><T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator>=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	public:
		typedef typename std::vector<T>::size_type size_type;
		BlobPtr():curr(0){}
		BlobPtr(const Blob<T> &blob,size_type sz=0):wptr(blob.data),curr(sz){}
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		BlobPtr & operator++();
		BlobPtr & operator++(int);
		BlobPtr & operator--();
		BlobPtr & operator--(int);
		BlobPtr operator+(size_type) const;
		BlobPtr operator-(size_type) const;
		BlobPtr operator+=(size_type) const;
		BlobPtr operator-=(size_type) const;
		T & operator*() const;
		T * operator->() const;
	private:
		std::shared_ptr<std::vector<T>> check(size_type i,const std::string &msg) const;
		std::weak_ptr<std::vector<T>> wptr;
		size_type curr=0;
};
//Blob
template <typename T> Blob<T> & Blob<T>::operator=(const Blob &rhs)
{
	data=std::make_shared<std::vector<T>>(*rhs.data);
	return *this;
}
template <typename T> T & Blob<T>::operator[](size_type i)
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> const T & Blob<T>::operator[](size_type i) const
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> void Blob<T>::pop_back()
{
	check(0,"pop_back on empty Blob");
	data->pop_back();
}
template <typename T> T & Blob<T>::front()
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> const T & Blob<T>::front() const
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> T & Blob<T>::back()
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> const T & Blob<T>::back() const
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr<T>(*this);
}
template <typename T> BlobPtr<T> Blob<T>::end()
{
	return BlobPtr<T>(*this,data->size());
}
template <typename T> inline void Blob<T>::check(size_type i,const string &msg) const
{
	if(i>=data->size())
		throw std::out_of_range(msg);
}
template <typename T> bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data==*rhs.data;
}
template <typename T> bool operator!=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data<*rhs.data;
}
template <typename T> bool operator<=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data>*rhs.data;
}
template <typename T> bool operator>=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs<rhs);
}
//BlobPtr
template <typename T> std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string &msg) const
{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound BlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
template <typename T> T & BlobPtr<T>::operator[](size_type i)
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> const T & BlobPtr<T>::operator[](size_type i) const
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++()
{
	check(curr,"increment past end of BlobPtr");
	++curr;
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++(int)
{
	BlobPtr ret=*this;
	++*this;
	return ret;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--()
{
	--curr;
	check(curr,"decrement past the begin of BlobPtr");
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--(int)
{
	BlobPtr ret=*this;
	--*this;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+(size_type i) const
{
	BlobPtr ret(*this);
	ret+=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-(size_type i) const
{
	BlobPtr ret(*this);
	ret-=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+=(size_type i) const
{
	check(curr+i,"increment past end of range");
	while(--i)
		++*this;
	return *this;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-=(size_type i) const
{
	check(curr-i,"decrement past begin of range");
	while(--i)
		--*this;
	return *this;
}
template <typename T> T & BlobPtr<T>::operator*() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
template <typename T> T * BlobPtr<T>::operator->() const
{
	return & this->operator*();
}
template <typename T> bool operator==(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r)
		return (!r||lhs.curr==rhs.curr);
	else
		return false;
}
template <typename T> bool operator!=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r&&l)
		return lhs.curr<rhs.curr;
	else
		return false;
}
template <typename T> bool operator<=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator>=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs<rhs);
}
#endif
```
==test.cpp==
```
#include <vector>
#include <string>
using std::string;
using std::vector;
#include <iostream>
using std::cout; using std::endl;

#include "Blob.h"

int main()
{
	vector<string> s={"a","an","the","you"};
	Blob<string> b1(s.begin(),s.end());
	for (BlobPtr<string> p = b1.begin(); p != b1.end(); ++p)
		cout << *p << endl;
	return 0;
}
```
### 16.25
`extern template class vector<string>`>>实例化声明，承诺在程序其他位置有该实例化的一个非extern声明(定义)。
`template class vector<Sales_data>`实例化定义，编译器遇到实例化定义时，将为其生成代码。
### 16.26
不可以。显式实例化时会实例化一个模板的所有成员，这其中当然包含vector接受元素数量的构造函数。因为未提供初始值的vector将会对其包含的元素进行值初始化，该操作由NoDefault的默认构造函数完成，而NoDefault并未提供默认构造函数。
### 16.27
1. 未实例化，函数声明
2. 未实例化，引用
3. 实例化Stack<int>
4. 未实例化，指针
5. 实例化Stack<char>，函数调用
6. 实例化Stack<string> 
### 16.28
```
#ifndef _POINTERS_H
#define _POINTERS_H
#include <functional>
#include <stdexcept>
#include <exception>
template <typename T> class Shared_Ptr;
class Delete
{
	public:
		template <typename T> void operator()(T *p)
		{
			delete p;
		}
};
template <typename T> bool operator==(const Shared_Ptr<T> &,const Shared_Ptr<T> &);
template <typename T> bool operator!=(const Shared_Ptr<T> &,const Shared_Ptr<T> &);
template <typename T> class Shared_Ptr
{
	friend bool operator==<T>(const Shared_Ptr<T> &,const Shared_Ptr<T> &);
	friend bool operator!=<T>(const Shared_Ptr<T> &,const Shared_Ptr<T> &);
	public:
		Shared_Ptr():del(nullptr),ptr(nullptr),count(new std::size_t(0)) {}
		Shared_Ptr(T *p,std::function<void(T *)> DEL=nullptr):del(DEL),ptr(p),count(new std::size_t(1)) {}
		Shared_Ptr(const Shared_Ptr &lhs,std::function<void(T *)> DEL=nullptr):del(DEL),ptr(lhs.ptr),count(lhs.count) {++*count;}
		Shared_Ptr & operator=(const Shared_Ptr &rhs)
		{
			++*rhs.count;
			if(*count==0||--*count==0)
			{
				del?del(ptr):delete ptr;
				delete count;
			}
			ptr=rhs.ptr;
			count=rhs.count;
			del=rhs.del;
			return *this;
		}
		T & operator*() const
		{
			if(ptr)
				return *ptr;
			else
				throw std::runtime_error("dereference nullptr");
		}
		T * operator->() const
		{
			return & this->operator*();
		}
		explicit operator bool() const
		{
			return ptr?true:false;
		}
		T * get() const {return ptr;}
		void reset(T *p=nullptr,std::function<void(T *)> DEL=nullptr)
		{
			if(*count==0||--*count==0)
			{
				del?del(ptr):delete ptr;
				delete count;
			}
			if(!p)
			{
				del=nullptr;
				ptr=nullptr;
				count=new std::size_t(0);
			}
			else
			{
				ptr=p;
				count=new std::size_t(1);
				if(DEL)
					del=DEL;
			}
		}
		~Shared_Ptr()
		{
			if(*count==0||--*count==0)
			{
				del?del(ptr):delete ptr;
				delete count;
			}
		}
	private:
		std::function<void(T *)> del;
		T *ptr;
		std::size_t *count;
};
template <typename T,typename F=Delete> class Unique_Ptr
{
	public:
		Unique_Ptr(T *p=nullptr,F DEL=Delete()):ptr(p),del(DEL) {}
		Unique_Ptr(F DEL):ptr(nullptr),del(DEL) {}
		Unique_Ptr(const Unique_Ptr &)=delete;
		Unique_Ptr & operator=(const Unique_Ptr &)=delete;
		T *release()
		{
			T *ret=ptr;
			ptr=nullptr;
			return ret;
		}
		void reset(T *p=nullptr)
		{
			del(ptr);
			ptr=p;
		}
		~Unique_Ptr() {del(ptr);}
	private:
		T *ptr;
		F del;
};
template <typename T> bool operator==(const Shared_Ptr<T> &lhs,const Shared_Ptr<T> &rhs)
{
	return lhs.ptr==rhs.ptr;
}
template <typename T> bool operator!=(const Shared_Ptr<T> &lhs,const Shared_Ptr<T> &rhs)
{
	return !(lhs==rhs);
}
#endif
```
### 16.29
待完善
### 16.30
同上
### 16.31
unique_ptr有两个模版参数，一个是所管理的对象类型，另一个是删除器类型。因此，删除器类型是unique_ptr的一部分，在编译时就可知道，删除器可直接保存在unique_ptr 对象中。通过这种方式，unique_ptr避免了间接调用删除器的运行时开销，而编译时还可以将自定义的删除器，如DebugDelete编译为内联形式,可参考16.28的Delete。
### 16.32
用函数实参来确定模板实参的过程被称为模板实参推断，在模板实参推断的过程中，编译器使用函数调用中的实参类型来寻找模板实参，从而生成对应的模板实例。
### 16.33
在模板实参推断的过程中，编译器通常不是对实参进行类型转换，而是生成一个新的模板实例。并且只有很有限的几种类型转换会发生，其中有：
- 顶层const无论是在形参还是在实参中都会被忽略。
- 可以将一个非const对象的引用（或指针）传递给一个const的引用（或指针）形参。
- 如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。
### 16.34
1. 不合法，因为形参类型是引用，所以数组实参无法转换为指针，同时这两个数组大小不同，因此是不同类型。
2. 合法，原因与上面相同，不同点在于，数组大小相同，因此是相同类型。
### 16.35
1. 合法，T的类型是char
2. 合法，T的类型double
3. 合法，T的类型是char
4. 不合法，实参类型不同，模板实参推断失败。
### 16.36
1. T推断为int *
2. T1和T2都推断为int *
3. T推断为const int *
4. T1和T2都推断为const int *
5. 不合法，一个是int *，一个是const int *，T类型推断失败
6. T1推断为int *，T2推断为const int *
### 16.37
可以，利用显式模板实参将max实例化为`int max<int>(int,int)`或者`double max<double(double,double)>`，这样之后就可以应用正常的类型转换了。
### 16.38
因为函数返回类型与参数列表中任何类型都不相同时，编译器无法推断出模板实参的类型，这时候就需要指定显式模板实参。这个显式模板实参用来控制函数的返回类型。
### 16.39
`int compare<const char *>(const char * const &v1,const char * const &v2)`这是实例化的示例
### 16.40
合法，实参的迭代器所指的元素需要支持加号操作，由于`decltype(*beg+0)`是右值，所以推断出的返回类型应该是所指元素的常量引用。
### 16.41
`template <typename T1,typename T2> sum(T1 a,T2 b)->decltype(a+b) {return a+b;}`尾置返回类型中，a+b会自动进行类型提升，向较大的类型转换，返回类型就是其中较大的类型。
### 16.42
1. T是int &,int &val
2. T是const int &,const int &val
3. T是int,int &&val
### 16.43
i=ci表达式会返回左值i,故T将是int &
### 16.44
如果g的函数参数声明为T
1. T是int,int val
2. T是int,int val
3. T是int,int val
如果g的函数参数声明为const T&
1. T是int,const int &val
2. T是int,const int &val
3. T是int,const int &val
### 16.45
如果对字面常量调用g，那么T会推断为int，函数参数为int &&val，函数内定义vector<int> v。
如果对int类型的变量调用g，那么T会推断为int &，函数参数为int &val，而因为引用不是对象，所以无法定义元素为引用的vector，所以函数调用会失败。
### 16.46
此循环依次将elem所指的对象，移动到dest所指的内存中。循环体中调用construct成员，该成员在第二个参数是左值的情况下执行拷贝，是右值的情况下执行移动操作。
### 16.47
```
#include <utility>
#include <iostream>
template <typename F,typename T1,typename T2> void flip(F f,T1 &&t1,T2 &&t2)
{
	f(std::forward<T2>(t2),std::forward<T1>(t1));
}
void print(int &i,int &j)
{
	std::cout<<"接受左值引用"<<std::endl;
}
void print(int &&i,int &&j)
{
	std::cout<<"接受右值引用"<<std::endl;
}
int main()
{
	int j=42;
	int &i=j;
	print(i,i);
	print(42,42);
	return 0;
}
```
### 16.48
```
#include <string>
#include <sstream>
using std::string;
using std::ostringstream;
template <typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret<<t;
	return ret.str();
}
template <typename T> string debug_rep(T *p)
{
	ostringstream ret;
	ret<<"pointer: "<<p;
	if(p)
		ret<<" "<<debug.rep(*p);
	else
		ret<<" null pointer";
	return ret.str();
}
string debug_rep(const string &s)
{
	return '"'+s+'"';
}
string debug_rep(char *p)
{
	return debug_rep(string(p));
}
string debug_rep(const char *)
{
	return debug_rep(string(p));
}
```
### 16.49
g(42)	g<int>(int)
g(p)	g<int>(int *)
g(ci)	g<int>(int)
g(p2)	g<const int>(const int *)
f(42)	f<int>(int)
f(p)	f<int *>(int*)
f(ci)	f<int>(int)
f(p2)	f<int>(const int *)
### 16.50
```
#include <iostream>
#include <typeinfo>
using namespace std;
template <typename T> void f(T t)
{
	cout<<"f(T t)"<<endl;
	cout<<"t: "<<typeid(t).name()<<endl;
}
template <typename T> void f(const T* p)
{
	cout<<"f(const T*)"<<endl;
	cout<<"p: "<<typeid(p).name()<<endl;
}
template <typename T> void g(T t)
{
	cout<<"g(T t)"<<endl;
	cout<<"t: "<<typeid(t).name()<<endl;
}
template <typename T> void g(T* p)
{
	cout<<"g(T*)"<<endl;
	cout<<"p: "<<typeid(p).name()<<endl;
}
int main(void)
{
	int i=42,*p=&i;
	const int ci=42,*p2=&ci;
	g(42);
	g(p);
	g(ci);
	g(p2);
	f(42);
	f(p);
	f(ci);
	f(p2);
	return 0;
}
```
### 16.51
<a id="1">见此处</a>
```
#include <iostream>
#include <string>
using namespace std;
template <typename T,typename... Args> void foo(const T &t,const Args &... rest)
{
	cout<<"Args: "<<sizeof...(Args)<<endl;
	cout<<"rest: "<<sizeof...(rest)<<endl;
}
int main(void)
{
	int i=0;
	double d=3.14;
	string s="how now brown cow";
	foo(i,s,42,d);
	foo(s,42,"hi");
	foo(d,s);
	foo("hi");
	foo(i,42,41,43);
	return 0;
}
```
### 16.52
[见16.51](#1)
### 16.53
```
#include <iostream>
#include <string>
using namespace std;
template <typename T> ostream &print(ostream &os,const T &t)
{
	return os<<t<<endl;
}
template <typename T,typename... Args> ostream &print(ostream &os,const T &t,const Args &... res)
{
	os<<t<<",";
	return print(os,res...);
}
int main(void)
{
	print(cout,1);
	print(cout,1,"hi");
	print(cout,1,3.14,"hi",string("hello"),7);
	return 0;
}
```
### 16.54
会产生编译错误。
### 16.55
如此一来，非可变参数版本就不在可变参数版本的作用域中，那么递归调用的将永远是可变参数版本的实例，即使res是空包，调用将依然进行下去，无法结束递归。
### 16.56
```
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template <typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret<<t;
	return ret.str();
}
template <typename T> string debug_rep(T *p)
{
	ostringstream ret;
	ret<<"pointer: "<<p;
	if(p)
		ret<<" "<<debug_rep(*p);
	else
		ret<<" null pointer";
	return ret.str();
}
string debug_rep(const string &s)
{
	return '"'+s+'"';
}
string debug_rep(char *p)
{
	return debug_rep(string(p));
}
string debug_rep(const char *p)
{
	return debug_rep(string(p));
}
template <typename T> ostream &print(ostream &os,const T &t)
{
	return os<<t<<endl;
}
template <typename T,typename... Args> ostream &print(ostream &os,const T &t,const Args &... res)
{
	os<<t<<",";
	return print(os,res...);
}
template <typename... Args> ostream & errorMsg(ostream &os,const Args &... rest)
{
	return print(os,debug_rep(rest)...);
}
int main(void)
{
	errorMsg(cerr,42,'h',"hello",1.34,string("hehe"));
	return 0;
}
```
### 16.57
上一题中的errorMsg版本不需要参数具有相同的数据类型，而6.2.6节中的error_Msg函数需要所有参数具有相同类型。
### 16.58
==StrVec.h==
```
#ifndef _STRVEC_H
#define _STRVEC_H
#include <string>
#include <cstddef>
#include <utility>
#include <memory>
#include <initializer_list>
class StrVec
{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(StrVec &&s) noexcept :elements(s.elements),first_free(s.first_free),cap(s.cap) {s.elements=s.first_free=s.cap=nullptr;}
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		StrVec & operator=(StrVec &&) noexcept;
		~StrVec() {free();}
		void push_back(const std::string &);
		void push_back(std::string &&);
		template <typename... Args> void emplace_back(Args&&... rest);
		size_t size() {return first_free-elements;}
		size_t capacity() {return cap-elements;}
		std::string *begin() const {return elements;}
		std::string *end() const {return first_free;}

		void resize(const size_t n,const std::string &orgv=std::string());
		void reserve(const size_t n);
	private:
		std::string *elements;
		std::string *first_free;
		std::string *cap;
		static std::allocator<std::string> alloc;
		void chk_n_alloc() {if(size()==capacity()) reallocate();}
		std::pair<std::string *,std::string *> alloc_n_copy(const std::string *,const std::string *);
		void free();
		void reallocate();
};
#endif
```
==StrVec.cpp==
```
#include "StrVec.h"
std::allocator<std::string> StrVec::alloc;
StrVec::StrVec(const StrVec &org)
{
	std::pair<std::string *,std::string *> data=alloc_n_copy(org.begin(),org.end());
	elements=data.first;
	first_free=cap=data.second;
}
StrVec::StrVec(std::initializer_list<std::string> ls)
{
	auto data=alloc_n_copy(ls.begin(),ls.end());
	elements=data.first;
	first_free=cap=data.second;
}
StrVec & StrVec::operator=(const StrVec &rhs)
{
	auto data=alloc_n_copy(rhs.begin(),rhs.end());
	free();
	elements=data.first;
	first_free=cap=data.second;
	return *this;
}
StrVec & StrVec::operator=(StrVec &&s) noexcept
{
	if(this!=&s)
	{
		free();
		elements=s.elements;
		first_free=s.first_free;
		cap=s.cap;
		s.elements=s.first_free=s.cap=nullptr;
	}
	return *this;
}
void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}
void StrVec::push_back(std::string &&s)
{
	chk_n_alloc();
	alloc.construct(first_free++,std::move(s));
}
template <typename... Args> inline void StrVec::emplace_back(Args&&... rest)
{
	chk_n_alloc();
	alloc.construct(first_free++,std::forward<Args>(rest)...);
}
std::pair<std::string *,std::string *> StrVec::alloc_n_copy(const std::string *b,const std::string *e)
{
	std::string *data=alloc.allocate(e-b);
	return {data,uninitialized_copy(b,e,data)};
}
void StrVec::free()
{
	if(elements)
	{
		for(auto p=first_free;p!=elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements,cap-elements);
	}
}
void StrVec::reallocate()
{
	size_t newcapacity=size()?2*size():1;
	std::string *newdata=alloc.allocate(newcapacity);
	std::string *dest=newdata;
	std::string *src=elements;
	for(size_t i=0;i!=size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	elements=newdata;
	first_free=dest;
	cap=elements+newcapacity;
}
void StrVec::reserve(const size_t n)
{
	if(n>capacity())
	{
		std::string *newdata=alloc.allocate(n);
		std::string *dest=newdata;
		std::string *src=elements;
		for(size_t i=0;i!=size();++i)
			alloc.construct(dest++,std::move(*src++));
		free();
		elements=newdata;
		first_free=dest;
		cap=elements+n;
	}
}
void StrVec::resize(const size_t n,const std::string &orgv)
{
	if(n<=size())
	{
		std::string *b=elements+n;
		std::string *e=first_free;
		while(b!=e)
			alloc.destroy(b++);
		first_free=elements+n;
	}
	else if(n<=capacity())
	{
		std::string *b=first_free;
		std::string *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
	else
	{
		reserve(n);
		std::string *b=first_free;
		std::string *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
}
```
==Vec.h==
```
#ifndef _VEC_H
#define _VEC_H
#include <memory>
#include <utility>
#include <algorithm>
template <typename> class Vec;
template <typename T> bool operator==(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator!=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator<(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator<=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator>(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> bool operator>=(const Vec<T> &lhs,const Vec<T> &rhs);
template <typename T> class Vec
{
	friend bool operator==<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator!=<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator< <T>(const Vec &lhs,const Vec &rhs);
	friend bool operator<=<T>(const Vec &lhs,const Vec &rhs);
	friend bool operator> <T>(const Vec &lhs,const Vec &rhs);
	friend bool operator>=<T>(const Vec &lhs,const Vec &rhs);
	public:
		Vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
		Vec(const Vec &org)
		{
			std::pair<T *,T *> data=alloc_n_copy(org.begin(),org.end());
			elements=data.first;
			first_free=cap=data.second;
		}
		Vec & operator=(const Vec &org)
		{
			auto data=alloc_n_copy(org.begin(),org.end());
			free();
			elements=data.first;
			first_free=cap=data.second;
			return *this;
		}
		T & operator[](std::size_t i) {return elements[i];}
		const T & operator[](std::size_t i) const {return elements[i];}
		~Vec() {free();}
		void push_back(const T &elem)
		{
			chk_n_alloc();
			alloc.construct(first_free++,elem);
		}
		template <typename... Args> void emplace_back(Args&&... args);
		std::size_t size() const {return first_free-elements;}
		std::size_t capacity() {return cap-elements;}
		T *begin() const {return elements;}
		T *end() const {return first_free;}
		void resize(const std::size_t n,const T &orgv);
		void reserve(const std::size_t n);
	private:
		T *elements;
		T *first_free;
		T *cap;
		static std::allocator<T> alloc;
		void chk_n_alloc() {if(size()==capacity()) reallocate();}
		std::pair<T *,T *> alloc_n_copy(const T *,const T *);
		void free();
		void reallocate();
};
//implementation
template <typename T> std::allocator<T> Vec<T>::alloc;
template <typename T> template <typename... Args> void Vec<T>::emplace_back(Args&&... args)
{
	chk_n_alloc();
	alloc.construct(first_free++,std::forward<Args>(args)...);
}
template <typename T> std::pair<T *,T *> Vec<T>::alloc_n_copy(const T *b,const T *e)
{
	T *data=alloc.allocate(e-b);
	return {data,uninitialized_copy(b,e,data)};
}
template <typename T> void Vec<T>::reallocate()
{
	std::size_t newcapacity=size()?size()*2:1;
	T *newdata=alloc.allocate(newcapacity);
	T *dest=newdata;
	T *src=elements;
	for(std::size_t i=0;i!=size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	elements=newdata;
	first_free=dest;
	cap=elements+newcapacity;
}
template <typename T> void Vec<T>::free()
{
	if(elements)
	{
		for(auto p=first_free;p!=elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements,cap-elements);
	}
}
template <typename T> void Vec<T>::reserve(const std::size_t n)
{
	if(n>capacity())
	{
		T *newdata=alloc.allocate(n);
		T *dest=newdata;
		T *src=elements;
		for(std::size_t i=0;i!=size();++i)
			alloc.construct(dest++,std::move(*src++));
		free();
		elements=newdata;
		first_free=dest;
		cap=elements+n;
	}
}
template <typename T> void Vec<T>::resize(const std::size_t n,const T &orgv)
{
	if(n<=size())
	{
		T *b=elements+n;
		T *e=first_free;
		while(b!=e)
			alloc.destroy(b++);
		first_free=elements+n;
	}
	else if(n<=capacity())
	{
		T *b=first_free;
		T *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
	else
	{
		reserve(n);
		T *b=first_free;
		T *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
}
template <typename T> bool operator==(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return (lhs.size()==rhs.size())&&std::equal(lhs.begin(),lhs.end(),rhs.begin());
}
template <typename T> bool operator!=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}
template <typename T> bool operator>=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs<rhs);
}
template <typename T> bool operator>(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator<=(const Vec<T> &lhs,const Vec<T> &rhs)
{
	return !(lhs>rhs);
}
#endif
```
==test.cpp==
```
#include "Vec.h"
#include <string>
#include <iostream>
using std::string;
using std::cin; using std::cout; using std::endl;
using std::istream;
void print(const Vec<string> &svec)
{
    for (string *it = svec.begin(); it != svec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}
Vec<string> getVec(istream &is)
{
    Vec<string> svec;
    string s;
    while (is >> s)
        svec.push_back(s);
    return svec;
}
int main()
{
    Vec<string> svec = getVec(cin);
    print(svec);
    cout << "copy " << svec.size() << endl;
    Vec<string> svec2 = svec;
    print(svec2);
    cout << "assign" << endl;
    Vec<string> svec3;
    svec3 = svec2;
	svec3.emplace_back(10,'c');
    print(svec3);
    cout << "----- end -----"<<endl;
    return 0;
}
```
### 16.59
假定s是一个string，那么经过包括展它会以`std::forward<string>(s)`的形式被传递给construct，因为s是左值，那么construct会得到一个左值实参，进而调用string的拷贝构造函数。
### 16.60
make_shared将传递给它的参数包转发给用来实例化make_shared的类型的对应的构造函数，然后返回该对象的shared_ptr。
### 16.61
```
#include <memory>
template <typename T,typename... Args> shared_ptr<T> Make_Shared(Args&&... rest)
{
	shared_ptr<T> res(new T(std::forward(rest)...));
	return res;
}
```
### 16.62
==Sales_data.h==
```
#include <iostream>
#include <string>
#include <functional>
class Sales_data
{
	friend class std::hash<Sales_data>;
	friend std::istream & operator>>(std::istream &,Sales_data &);
	friend std::ostream & operator<<(std::ostream &,const Sales_data &);
	friend Sales_data operator+(const Sales_data &,const Sales_data &);
	friend bool operator==(const Sales_data &,const Sales_data &);
	friend bool operator!=(const Sales_data &,const Sales_data &);
	public:
		std::string isbn() const {return bookNo;}
		Sales_data()=default;
		Sales_data(const std::string &s):bookNo(s) {}
		Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(n*p) {}
		Sales_data & operator+=(const Sales_data &);
		operator std::string() const {return bookNo;}
		operator double() const {return revenue;}
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
		double avg_price() const;
};
std::istream & operator>>(std::istream &,Sales_data &);
std::ostream & operator<<(std::ostream &,const Sales_data &);
Sales_data operator+(const Sales_data &,const Sales_data &);
bool operator==(const Sales_data &,const Sales_data &);
bool operator!=(const Sales_data &,const Sales_data &);
namespace std
{
	template <> class hash<Sales_data>
	{
		public:
			typedef size_t result_type;
			typedef Sales_data argument_type;
			size_t operator()(const Sales_data &s) const;
	};
}
```
==Sales_data.cpp==
```
#include "Sales_data.h"
inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
std::istream & operator>>(std::istream &is,Sales_data &src)
{
	double price=0.0;
	is>>src.bookNo>>src.units_sold>>price;
	if(is)
		src.revenue=src.units_sold*price;
	else
		src=Sales_data();
	return is;
}
std::ostream & operator<<(std::ostream &os,const Sales_data &src)
{
	os<<src.isbn()<<" "<<src.units_sold<<" "<<src.revenue<<" "<<src.avg_price();
	return os;
}
Sales_data & Sales_data::operator+=(const Sales_data & rhs)
{
	*this=*(this)+rhs;
	return *this;
}
Sales_data operator+(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data tmp;
	tmp.bookNo=lhs.bookNo;
	tmp.units_sold=lhs.units_sold+rhs.units_sold;
	tmp.revenue=lhs.revenue+rhs.revenue;
	return tmp;
}
bool operator==(const Sales_data &lhs,const Sales_data &rhs)
{
	return lhs.bookNo==rhs.bookNo&&lhs.units_sold==rhs.units_sold&&lhs.revenue==rhs.revenue;
}
bool operator!=(const Sales_data &lhs,const Sales_data &rhs)
{
	return !(lhs==rhs);
}
size_t std::hash<Sales_data>::operator()(const Sales_data &s) const
{
	return std::hash<std::string>()(s.bookNo)^std::hash<unsigned>()(s.units_sold)^std::hash<double>()(s.revenue);
}
```
==test.cpp==
```
#include <iostream>
#include <unordered_set>
#include "Sales_data.h"
int main(void)
{
	std::unordered_multiset<Sales_data> SDset;
	Sales_data a{"100",2,20},b{"101",3,25},c{"100",2,20};
	SDset.insert(a);
	SDset.insert(b);
	SDset.insert(c);
	for(const auto& setit:SDset)
		std::cout<<setit<<std::endl;
	return 0;
}
```
### 16.63
```
#include <iostream>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::endl;
template <typename T> size_t statistic(const std::vector<T> &vec,const T &target)
{
	size_t result=0;
	for(auto member:vec)
		if(target==member)
			++result;
	return result;
}
int main(void)
{
	vector<int> ivec={1,2,3,3,4,5,6};
	cout<<"ivec里有"<<statistic(ivec,3)<<"个3."<<endl;
	vector<double> dvec={1.0,1.1,1.1,1.1,1.3};
	cout<<"dvec里有"<<statistic(dvec,1.1)<<"个1.1"<<endl;
	vector<string> svec{"hi","hello","hi"};
	cout<<"svec里有"<<statistic(svec,string("hi"))<<"个hi"<<endl;
	return 0;
}
```
### 16.64
```
#include <iostream>
#include <vector>
#include <cstring>
using std::vector;
using std::string;
using std::cout;
using std::endl;
template <typename T> size_t statistic(const std::vector<T> &vec,const T &target)
{
	size_t result=0;
	for(auto member:vec)
		if(target==member)
			++result;
	return result;
}
template <> size_t statistic(const std::vector<const char *> &vec,const char * const &target)
{
	size_t result=0;
	for(auto member:vec)
		if(strcmp(member,target)==0)
			++result;
	return result;
}
int main(void)
{
	vector<const char *> svec{"ni","hi","hi","hello","hi"};
	const char *s="hi";
	cout<<"svec里有"<<statistic(svec,s)<<"个hi"<<endl;
	return 0;
}
```
### 16.65
```
#include <string>
#include <sstream>
using std::string;
using std::ostringstream;
template <typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret<<t;
	return ret.str();
}
template <typename T> string debug_rep(T *p)
{
	ostringstream ret;
	ret<<"pointer: "<<p;
	if(p)
		ret<<" "<<debug.rep(*p);
	else
		ret<<" null pointer";
	return ret.str();
}
string debug_rep(const string &s)
{
	return '"'+s+'"';
}
template <> string debug_rep(char *p)
{
	return debug_rep(string(p));
}
template <> string debug_rep(const char *)
{
	return debug_rep(string(p));
}
```
### 16.66
它们最主要的区别在于重载会影响函数匹配，所以在设计重载函数时需要注意避免函数调用和我们设计不一致的情况。而模板特例化本质上是创建一个模板的特殊实例，并不影响函数匹配。
### 16.67
特例化不影响函数匹配，它并不是为编译器进行函数匹配提供一个新的选择，而是为模版的一个特殊实例提供不同于原模版的特殊定义，本质上是接管了编译器在完成函数匹配后的部分实例化工作。即，当某个模版是最佳匹配时，且需要实例为这个特殊实例时，不再从原模版进行实例化，而是直接使用这个特殊化版本。
