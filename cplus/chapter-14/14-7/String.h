#ifndef _sTRING_H
#define _sTRING_H
#include <iostream>
#include <utility>
class String
{
	friend std::istream & operator>>(std::istream &in,String &str);
	friend std::ostream & operator<<(std::ostream &out,const String &str);
	public:
		String():head(nullptr),tail(nullptr),cap(nullptr) {}
		String(const char *);
		String(const String &);
		String(String &&str) noexcept :head(str.head),tail(str.tail),cap(str.cap) {str.head=str.tail=str.cap=nullptr;std::cout<<"This is move constructor."<<std::endl;}
		String & operator=(const String &);
		String & operator=(String &&);
		String operator+(const String &);
		~String() {free();}

		size_t size() const {return tail-head;}
		size_t capacity() const {return cap-head;}
		bool empty() const {return (head==tail)?true:false;}
		char * begin() const {return head;}
		char * end() const {return tail;}
	private:
		char *head;
		char *tail;
		char *cap;
		static std::allocator<char> alloc;
		void free();

		std::pair<char *,char *> alloc_n_copy(const char *,const char *);
		void chk_n_alloc(size_t n) {if(n+size()>capacity()) reallocate(n);}
		void reallocate(size_t n);
};
std::istream & operator>>(std::istream &in,String &str);
std::ostream & operator<<(std::ostream &out,const String &str);
#endif
