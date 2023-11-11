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
