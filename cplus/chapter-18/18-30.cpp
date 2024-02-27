这样定义的话，由于存在歧义，直接基类Class在Final中无法访问
class Class{};
class Base:public Class
{
	public:
		Base()=default;
		Base(const Base &b):i(b.i) {}
		Base(const int &ri):i(ri) {}
	private:
		int i;
};
class D1:public virtual Base
{
	public:
		D1()=default;
		D1(const D1 &d):Base(d) {}
		D1(const int &ri):Base(ri) {}
};
class D2:public virtual Base
{
	public:
		D2()=default;
		D2(const D2 &d):Base(d) {}
		D2(const int &ri):Base(ri) {}
};
class MI:public D1,public D2
{
	public:
		MI()=default;
		MI(const MI &mi):Base(mi),D1(mi),D2(mi) {}
		MI(const int &ri):Base(ri),D1(ri),D2(ri) {}
};
class Final:public MI,public Class
{
	public:
		Final()=default;
		Final(const Final &fi):Base(fi),MI(fi),Class() {}
		Final(const int &ri):Base(ri),MI(ri),Class() {}
};
