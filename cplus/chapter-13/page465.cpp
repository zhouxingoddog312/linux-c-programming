class StrVec
{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec & operator=(const StrVec &);
		~StrVec() {free();}
		void push_back(const std::string &);
		size_t size() {return first_free-elements;}
		size_t capacity() {return cap-elements;}
		std::string *begin() const {return elements;}
		std::string *end() const {return first_free;}
	private:
		std::string *elements;
		std::string *first_free;
		std::string *cap;
		static std::allocator<std::string> alloc;
		void chk_n_alloc() {if(size()==capacity()) reallocate();}
		std::pair<std::string *,std::string *> alloc_n_copy(const std::string *,const std::string *);
		void free();
		void reallocate();
}
StrVec::StrVec(const StrVec &org)
{
	std::pair<std::string *,std::string *> data=alloc_n_copy(org.begin(),org.end());
	elements=data.first;
	first_free=cap=data.second;
}
StrVec & operator=(const StrVec &rhs)
{
	auto data=alloc_n_copy(rhs.begin(),rhs.end());
	free();
	elements=data.first;
	first_free=cap=data.second;
	return *this;
}
void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
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
			alloc.destory(--p);
		alloc.deallocate(elements,cap-elements);
	}
}
void StrVec::reallocate()
{
	size_t newcapacity=size()?2*size():1;
	std::string *newdata=alloc.allocate(newcapacity);
	std::string *dest=newdata;
	std::string *src=elements;
	for(size_t i=0;i!size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	elements=newdata;
	first_free=dest;
	cap=elements+newcapacity;
}
