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
