#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
class X
{
public:
	X() {std::cout<<"X()"<<std::endl;}
	X(const X &) {std::cout<<"X(const X &)"<<std::endl;}
	X & operator=(const X &) {std::cout<<"X=X"<<std::endl;return *this;}
	~X() {std::cout<<"~X()"<<std::endl;}
private:
};
void f1(X x) {}
void f2(X &x) {}
int main(void)
{
    cout << "局部变量：" << endl;
    X x;
    cout << endl;

    cout << "非引用参数传递：" << endl;
    f1(x);
    cout << endl;

    cout << "引用参数传递：" << endl;
    f2(x);
    cout << endl;

    cout << "动态分配：" << endl;
    X *px = new X;
    cout << endl;

    cout << "添加到容器中：" << endl;
    vector<X> vx;
    vx.push_back(x);
    cout << endl;

    cout << "释放动态分配对象：" << endl;
    delete px;
    cout << endl;

    cout << "拷贝初始化和赋值：" << endl;
    X y = x;
    y = x;
    cout << endl;

    cout << "程序结束！" << endl;
    return 0;
}
