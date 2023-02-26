class NoDefault
{
public:
	val v;
	NoDefault(int i):val(i){}
};
class C
{
public:
	NoDefault no;
	C(int i=0):no(i){}
};
