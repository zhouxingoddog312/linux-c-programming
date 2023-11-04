#ifndef SCREEN_H
#define SCREEN_H
#include <string>
using pos=std::string::size_type;
template <pos H,pos W> class Screen
{
	public:
		Screen():contents(H*W,' '){}
		Screen(char c,pos s=0):contents(H*W,c),cursor(s){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const {pos row=(r-1)*W;return contents[row+c-1];}
		Screen &move(pos r,pos c){pos row=(r-1)*W;cursor=row+c-1;return *this;}
		Screen &set(char c){contents[cursor]=c;return *this;}
		Screen &set(pos r,pos c,char ch){contents[(r-1)*W+c-1]=ch;return *this;}
		Screen &display(std::ostream &os){do_display(os);return *this;}
		const Screen &display(std::ostream &os) const {do_display(os);return *this;}
	private:
		pos cursor=0,height=H,width=W;
		std::string contents;
		void do_display(std::ostream &os) const {os<<contents;}
};
#endif
