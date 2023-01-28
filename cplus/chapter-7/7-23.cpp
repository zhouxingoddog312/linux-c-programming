#include <string>
class Screen
{
	pubilic:
		using pos=std::string::size_type pos;
		Screen()=default;
		Screen(pos ht,pos wd,char c):height{ht},width{wd},contents(ht*wd,c){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const;
		Screen &move(pos r,pos c);
	private:
		pos cursor=0,height=0,width=0;
		std::string contents;
};
inline char Screen::get(pos r,pos c) const
{
	pos row=r*width;
	return contents[row+c];
}
inline Screen &move(pos r,pos c)
{
	pos row=r*width;
	cursor=row+c;
	return *this;
}
