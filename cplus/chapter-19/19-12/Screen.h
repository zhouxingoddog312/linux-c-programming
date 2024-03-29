#include <string>
class Screen
{
	public:
		using pos=std::string::size_type;
		Screen()=default;
		Screen(pos ht,pos wd):height{ht},width{wd},contents(ht*wd,' '){}
		Screen(pos ht,pos wd,char c):height{ht},width{wd},contents(ht*wd,c){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const;
		Screen &move(pos r,pos c);
		Screen &set(char);
		Screen &set(pos,pos,char);
		Screen &display(std::ostream &os){do_display(os);return *this;}
		const Screen &display(std::ostream &os) const {do_display(os);return *this;}
		static pos Screen::* data()
		{
			return &Screen::cursor;
		}
	private:
		pos cursor=0,height=0,width=0;
		std::string contents;
		void  do_display(std::ostream &os) const {os<<contents;}
};
inline char Screen::get(pos r,pos c) const
{
	pos row=r*width;
	return contents[row+c];
}
inline Screen &Screen::move(pos r,pos c)
{
	pos row=r*width;
	cursor=row+c;
	return *this;
}
inline Screen &Screen::set(char ch)
{
	contents[cursor]=ch;
	return *this;
}
inline Screen &Screen::set(pos r,pos c,char ch)
{
	contents[r*width+c]=ch;
	return *this;
}
