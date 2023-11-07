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
