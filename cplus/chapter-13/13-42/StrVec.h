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
