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