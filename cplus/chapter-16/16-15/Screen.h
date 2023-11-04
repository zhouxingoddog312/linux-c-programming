#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <string>
using pos=std::string::size_type;
template <pos H,pos W> class Screen;
template <pos H,pos W> std::istream & operator>>(std::istream &is,Screen<H,W> &screen);
template <pos H,pos W> std::ostream & operator<<(std::ostream &os,Screen<H,W> &screen);
template <pos H,pos W> class Screen
{
	friend std::istream & operator>><H,W>(std::istream &is,Screen<H,W> &screen);
	friend std::ostream & operator<<<H,W>(std::ostream &os,Screen<H,W> &screen);
	public:
		Screen():contents(H*W,' '){}
		Screen(char c,pos s=0):contents(H*W,c),cursor(s){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const {pos row=(r-1)*W;return contents[row+c-1];}
		Screen &move(pos r,pos c){pos row=(r-1)*W;cursor=row+c-1;return *this;}
		Screen &set(char c){contents[cursor]=c;return *this;}
		Screen &set(pos r,pos c,char ch){contents[(r-1)*W+c-1]=ch;return *this;}
	private:
		pos cursor=0,height=H,width=W;
		std::string contents;
};
template <pos H,pos W> std::istream & operator>>(std::istream &is,Screen<H,W> &screen)
{
	std::string tmp;
	is>>tmp;
	for(auto b1=tmp.begin(),b2=screen.contents.begin();b1!=tmp.end()&&b2!=screen.contents.end();++b1,++b2)
		*b2=*b1;
	return is;
}
template <pos H,pos W> std::ostream & operator<<(std::ostream &os,Screen<H,W> &screen)
{
	os<<screen.contents;
	return os;
}
#endif
