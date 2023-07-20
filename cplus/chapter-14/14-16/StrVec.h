#ifndef _STRVEC_H
#define _STRVEC_H
#include <string>
#include <cstddef>
#include <utility>
#include <memory>
#include <initializer_list>
class StrVec
{
	friend bool operator==(const StrVec &,const StrVec &);
	friend bool operator!=(const StrVec &,const StrVec &);
	friend bool operator<(const StrVec &,const StrVec &);
	friend bool operator>=(const StrVec &,const StrVec &);
	friend bool operator>(const StrVec &,const StrVec &);
	friend bool operator<=(const  StrVec &,const StrVec &);
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		StrVec & operator=(std::initializer_list<std::string>);
		std::string & operator[](std::size_t i) {return elements[i];}
		const std::string & operator[](std::size_t i) const {return elements[i];}
		~StrVec() {free();}
		void push_back(const std::string &);
		size_t size() const {return first_free-elements;}
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
bool operator==(const StrVec &,const StrVec &);
bool operator!=(const StrVec &,const StrVec &);
bool operator<(const StrVec &,const StrVec &);
bool operator>=(const StrVec &,const StrVec &);
bool operator>(const StrVec &,const StrVec &);
bool operator<=(const  StrVec &,const StrVec &);
#endif
