#include <string>
class Window_mgr
{
	public:
		using ScreenIndex=std::vector<Screen>::size_type;
		void clear(ScreenIndex i);
		ScreenIndex addScreen(const Screen &);
	private:
		std::vector<Screen> screens{Screen(24,80,' ')};
}
inline Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size()-1;
}
class Screen
{
	friend void Window_mgr::clear(ScreenIndex i);
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
inline void Window_mgr::clear(ScreenIndex i)
{
	Screen &s=screens[i];
	s.contents=string(s.height*s.width,' ');
}
