#ifndef _STRING_H
#define _STRING_H
class String
{
	public:
		String();
		String(const char *);
	private:
		char *head;
		char *tail;
		char *cap;
		static std::allocator<char> alloc;
		void chk_n_alloc(size_t n) {if(n>capacity()) reallocate();}
};
#endif
