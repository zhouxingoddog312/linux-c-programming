#ifndef STRBLOB_H
#define STRBLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
friend bool operator==(const StrBlob &,const StrBlob &);
friend bool operator!=(const StrBlob &,const StrBlob &);
friend bool operator<(const StrBlob &,const StrBlob &);
friend bool operator>=(const StrBlob &,const StrBlob &);
friend bool operator>(const StrBlob &,const StrBlob &);
friend bool operator<=(const StrBlob &,const StrBlob &);
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	
	StrBlob(const StrBlob &);
	StrBlob & operator=(const StrBlob &);
	std::string & operator[](std::size_t i) {return data->at(i);}
	const std::string & operator[](std::size_t i) const {return data->at(i);}

	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void push_back(std::string &&t){data->push_back(std::move(t));}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr begin() const;
	StrBlobPtr end();
	StrBlobPtr end() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
bool operator==(const StrBlob &,const StrBlob &);
bool operator!=(const StrBlob &,const StrBlob &);
bool operator<(const StrBlob &,const StrBlob &);
bool operator>=(const StrBlob &,const StrBlob &);
bool operator>(const StrBlob &,const StrBlob &);
bool operator<=(const StrBlob &,const StrBlob &);
class StrBlobPtr
{
friend bool operator==(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator!=(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator<(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator>=(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator>(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator<=(const StrBlobPtr &,const StrBlobPtr &);
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	StrBlobPtr(const StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string & operator[](std::size_t i) {auto p=check(i,"index is out of range");return p->at(i);}
	const std::string & operator[](std::size_t i) const {auto p=check(i,"index is out of range");return p->at(i);}
	StrBlobPtr & operator++();
	StrBlobPtr operator++(int);
	StrBlobPtr & operator--();
	StrBlobPtr operator--(int);
	StrBlobPtr operator+(std::size_t) const;
	StrBlobPtr operator-(std::size_t) const;
	StrBlobPtr & operator+=(std::size_t);
	StrBlobPtr & operator-=(std::size_t);
	std::string & operator*() const;
	std::string * operator->() const;

	std::string &deref() const;
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};
bool operator==(const StrBlobPtr &,const StrBlobPtr &);
bool operator!=(const StrBlobPtr &,const StrBlobPtr &);
bool operator<(const StrBlobPtr &,const StrBlobPtr &);
bool operator>=(const StrBlobPtr &,const StrBlobPtr &);
bool operator>(const StrBlobPtr &,const StrBlobPtr &);
bool operator<=(const StrBlobPtr &,const StrBlobPtr &);
#endif
