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
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	
	StrBlob(const StrBlob &);
	StrBlob & operator=(const StrBlob &);

	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
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
class StrBlobPtr
{
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	StrBlobPtr(const StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string &deref() const;
	StrBlobPtr &incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};
#endif
